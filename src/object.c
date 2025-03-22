#include "common.h"

#include "common.h"
#include "variables.h"
#include "sys/gfx/model.h"
#include "sys/linked_list.h"
#include "sys/objects.h"

extern void **gDeferredObjDefFreeList;
extern s32 gDeferredObjDefFreeListCount;
extern void *D_800B1918;
extern void *D_800B18E4;
extern int gObjIndexCount; //count of OBJINDEX.BIN entries
extern int gNumObjectsTabEntries;
extern ObjDef **gLoadedObjDefs;
extern u8 *gObjDefRefCount;
extern int gNumTablesTabEntries;
extern Object **gObjList; //global object list
extern LinkedList gObjUpdateList;

enum FILE_ID {
    FILE_TABLES_BIN   = 0x16,
    FILE_TABLES_TAB   = 0x17,
    FILE_BITTABLE     = 0x37,
    FILE_OBJECTS_TAB  = 0x41,
    FILE_OBJINDEX_BIN = 0x43
};

extern void *gFile_TABLES_BIN;
extern s32  *gFile_TABLES_TAB;
extern s32  *gFile_OBJECTS_TAB;
extern s16  *gFile_OBJINDEX;

int get_file_size(int file);
void queue_alloc_load_file(void **dest, s32 fileId);
void queue_load_file_to_ptr(void **dest, s32 fileId);
void alloc_some_object_arrays(void); //related to objects
void obj_clear_all(void);

void copy_obj_position_mirrors(Object *obj, ObjCreateInfo *param2, s32 param3);

void func_80046320(s16 param1, Object *object);

extern char D_80099600[]; // "objects/objects.c"
extern s32 gNumObjs;

extern void func_80058FE8();
extern void update_obj_hitboxes(s32);
extern s32 func_80004258(Object *object);
extern void func_80025E58();
extern void obj_do_hit_detection(s32);
extern void func_8002B6EC();

extern char D_800994E0[]; // "objects/objects.c"

void update_obj_models();
void update_object(Object *obj);
void func_8002272C(Object *obj);

extern s32 D_80091660;
extern s32 D_800B191C;

extern s16 D_800B18E0;
extern s32 D_800B1988;

extern void func_80025DF0();

ModLine *obj_load_objdef_modlines(s32 modLineNo, s16 *modLineCount);

extern void func_800596BC(ObjDef*);

ObjDef *obj_load_objdef(s32 tabIdx);
u32 func_80022828(Object *obj);
u32 obj_calc_mem_size(Object *obj, ObjDef *def, u32 flags);
void obj_free_objdef(s32 tabIdx);

void func_80021E74(f32, ModelInstance*);
void func_80022200(Object *obj, s32 param2, s32 param3);
u32 obj_alloc_object_state(Object *obj, u32 addr);
u32 func_80022868(s32 param1, Object *obj, u32 addr);
u32 func_8002298C(s32 param1, ModelInstance *param2, Object *obj, u32 addr);

f32 func_80022150(Object *obj);

void init_objects(void) {
    int i;

    //allocate some buffers
    gDeferredObjDefFreeList = malloc(0x2D0, ALLOC_TAG_OBJECTS_COL, NULL);
    D_800B1918     = malloc(0x60, ALLOC_TAG_OBJECTS_COL,  NULL);
    D_800B18E4     = malloc(0x10, ALLOC_TAG_OBJECTS_COL,  NULL);

    //load OBJINDEX.BIN and count number of entries
    queue_alloc_load_file((void **) (&gFile_OBJINDEX), FILE_OBJINDEX_BIN);
    gObjIndexCount = (get_file_size(FILE_OBJINDEX_BIN) >> 1) - 1;
    while(!gFile_OBJINDEX[gObjIndexCount]) gObjIndexCount--;

    //load OBJECTS.TAB and count number of entries
    queue_alloc_load_file((void **)&gFile_OBJECTS_TAB, FILE_OBJECTS_TAB);
    gNumObjectsTabEntries = 0;
    while(gFile_OBJECTS_TAB[gNumObjectsTabEntries] != -1) gNumObjectsTabEntries++;
    gNumObjectsTabEntries--;

    //init ref count and pointers
    gLoadedObjDefs = malloc(gNumObjectsTabEntries * 4, ALLOC_TAG_OBJECTS_COL, NULL);
    gObjDefRefCount   = malloc(gNumObjectsTabEntries,     ALLOC_TAG_OBJECTS_COL, NULL);
    for(i = 0; i < gNumObjectsTabEntries; i++) gObjDefRefCount[i] = 0; //why not memset?

    //load TABLES.BIN and TABLES.TAB and count number of entries
    queue_alloc_load_file((void **) (&gFile_TABLES_BIN), FILE_TABLES_BIN);
    queue_alloc_load_file((void **) (&gFile_TABLES_TAB), FILE_TABLES_TAB);
    gNumTablesTabEntries = 0;
    while(gFile_TABLES_TAB[gNumTablesTabEntries] != -1) gNumTablesTabEntries++;

    //allocate global object list and some other buffers
    gObjList = malloc(0x2D0, ALLOC_TAG_OBJECTS_COL, NULL);
    alloc_some_object_arrays();
    obj_clear_all();
}

void update_objects() {
    void *node;
    Object *obj;
    Object *player;
    s32 nextFieldOffset;

    nextFieldOffset = gObjUpdateList.nextFieldOffset; // == 0x38, &obj->next

    func_80058FE8();

    update_obj_models();
    update_obj_hitboxes(gNumObjs);

    node = gObjUpdateList.head;

    for (obj = (Object*)node; node != NULL && obj->updatePriority == 100; obj = (Object*)node) {
        update_object(obj);
        node = *((void**)(nextFieldOffset + (u32)node));

        if (obj->objhitInfo->unk_0x58){} // fake match
    }

    for (obj = (Object*)node; node != NULL && obj->def->flags & 0x40; obj = (Object*)node) {
        update_object(obj);
        obj->matrixIdx = func_80004258(obj);
        node = *((void**)(nextFieldOffset + (u32)node));
    }

    func_80025E58();

    while (node != NULL) {
        obj = (Object*)node;

        if (obj->objhitInfo != NULL) {
            if (obj->objhitInfo->unk_0x5a != 8 || (obj->objhitInfo->unk_0x58 & 1) == 0) {
                update_object(obj);
            }
        } else {
            update_object(obj);
        }

        node = *((void**)(nextFieldOffset + (u32)node));
    }

    player = get_player();
    if (player != NULL && player->linkedObject != NULL) {
        player->linkedObject->parent = player->parent;
        update_object(player->linkedObject);
    }

    obj_do_hit_detection(gNumObjs);

    node = gObjUpdateList.head;
    while (node != NULL) {
        obj = (Object*)node;
        func_8002272C(obj);
        node = *((void**)(nextFieldOffset + (u32)node));
    }

    player = get_player();
    if (player != NULL && player->linkedObject != NULL) {
        player->linkedObject->parent = player->parent;
        func_8002272C(player->linkedObject);
    }

    gDLL_waterfx->exports->func[0].withOneArg(delayByte);
    gDLL_projgfx->exports->func[2].withTwoArgs(delayByte, 0);
    gDLL_modgfx->exports->func[2].withThreeArgs(0, 0, 0);
    gDLL_expgfx->exports->func[2].withFourArgs(0, delayByte, 0, 0);

    func_8002B6EC();

    gDLL_ANIM->exports->func[9].asVoid();
    gDLL_ANIM->exports->func[5].asVoid();
    gDLL_Camera->exports->func[1].withOneArg(delayByte);

    write_c_file_label_pointers(D_800994E0, 0x169);
}

void doNothing_80020A40(void) {}

void update_obj_models() {
    int i;
    int j;
    int k;
    Object *object;
    ModelInstance *modelInst;
    ObjectStructC0_B8 *unk1;

    for (i = 0; i < gNumObjs; i++) {
        object = gObjList[i];

        for (j = 0; j < 2; j++) {
            if (j != 0) {
                object = object->linkedObject;
            }

            if (object == NULL) {
                continue;
            }

            for (k = 0; k < object->def->numModels; k++) {
                modelInst = object->modelInsts[k];

                if (modelInst != NULL) {
                    modelInst->unk_0x34 &= ~0x8;

                    if (modelInst->model->unk_0x1c != NULL) {
                        unk1 = object->unk0xc0 != NULL ? object->unk0xc0->unk_0xb8 : NULL;

                        if (object->unk0xc0 == NULL || (unk1 != NULL && unk1->unk_0x62 == 0)) {
                            func_8001B084(modelInst, delayFloat);
                        }
                    }
                }
            }
        }
    }
}

void obj_do_deferred_free() {
    int i;
    for(i = 0; i < gDeferredObjDefFreeListCount; i++) {
        obj_free_object(gDeferredObjDefFreeList[i], 0);
        gDeferredObjDefFreeList[i] = 0;
    }
    gDeferredObjDefFreeListCount = 0;
}

void obj_free_all() {
    s32 i;
    
    obj_do_deferred_free();
    D_80091660 = 0;

    i = 0;
    while (gNumObjs != 0) {
        obj_destroy_object(gObjList[i]);
        i++;
        if (i >= gNumObjs) {
            i = 0;
        }
    }

    obj_do_deferred_free();
    D_80091660 = 2;

    gDeferredObjDefFreeListCount = 0;
    D_800B191C = 0;
    gNumObjs = 0;

    linked_list_init(&gObjUpdateList, OFFSETOF(Object, next));

    obj_clear_all();

    gDLL_Camera->exports->func[9].withTwoArgs(0, 0);
}

void obj_clear_all() {
    gDeferredObjDefFreeListCount = 0;
    D_800B191C = 0;
    D_800B1988 = 0;
    gNumObjs = 0;

    linked_list_init(&gObjUpdateList, OFFSETOF(Object, next));

    D_800B18E0 = 0;
    func_80030EC0();
    func_80025DF0();
}

void func_80020D90(void) {
    D_800B18E0 = 0;
}

s32 func_80020DA0(s32 *numObjs) {
    s32 objsEnd;
    s32 idx1;
    s32 idx2;
    s32 endLoop;

    *numObjs = gNumObjs;

    if (0) {}

    if (D_800B18E0 != 0) {
        return D_800B18E0;
    }

    idx1 = 0;
    idx2 = gNumObjs - 1;
    objsEnd = idx2;

    // some kind of sort?
    while (idx1 <= idx2) {
        endLoop = 0;
        while (idx1 <= objsEnd && !endLoop) {
            if ((gObjList[idx1]->def->flags & 1) != 0) {
                idx1++;
            } else {
                endLoop = -1;
            }
        }

        endLoop = 0;
        while (idx2 >= 0 && !endLoop) {
            if ((gObjList[idx2]->def->flags & 1) == 0) {
                idx2--;
            } else {
                endLoop = -1;
            }
        }

        if (idx1 < idx2) {
            Object *temp;

            temp = gObjList[idx1];
            gObjList[idx1] = gObjList[idx2];
            gObjList[idx2] = temp;

            idx1++;
            idx2--;
        }
    }

    D_800B18E0 = idx1;
    return idx1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80020EE4.s")

void func_800210DC() {
    s32 i;
    Object *obj;
    ObjectStructC0 *var;

    for (i = 0; i < gNumObjs; i++) {
        obj = gObjList[i];

        if (obj->unk0xc0 != NULL) {
            var = obj->unk0xc0;

            if (obj->parent == NULL) {
                if (var->unk_0x30 != NULL) {
                    obj->parent = var->unk_0x30;
                }
            }
            
            obj->unk0xc0 = NULL;
        }
    }
}

Object **get_world_objects(s32 *param1, s32 *numObjs) {
    if (param1 != NULL) {
        *param1 = 0;
    }
    if (numObjs != NULL) {
        *numObjs = gNumObjs;
    }

    return gObjList;
}

Object *get_world_object(s32 idx) {
    if (idx < 0 || idx >= gNumObjs) {
        return NULL;
    }

    return gObjList[idx];
}

Object *func_800211B4(s32 param1) {
    s32 i;
    s32 len;
    Object *obj;

    i = 0;
    len = gNumObjs;

    while (i < len) {
        obj = gObjList[i];
        if (obj->createInfo != NULL && obj->createInfo->unk14 == param1) {
            return obj;
        }

        i++;
    }

    return NULL;
}

s32 get_num_objects(void) {
    return gNumObjs;
}

s32 ret0_800212E8(void) { return 0; }

#pragma GLOBAL_ASM("asm/nonmatchings/object/obj_get_seq.s")

void *func_800213A0(s32 idx) {
    if (idx < 0 || idx >= gNumTablesTabEntries) {
        return gFile_TABLES_BIN;
    }

    return (void*)((u32)gFile_TABLES_BIN + gFile_TABLES_TAB[idx] * 4);
}

Object *obj_create(ObjCreateInfo *createInfo, u32 createFlags, s32 mapID, s32 param4, Object *parent) {
    Object *obj;

    obj = NULL;
    queue_load_map_object((void**)&obj, createInfo, createFlags, mapID, param4, parent, 0);
    obj_add_object(obj, createFlags);

    return obj;
}

Object *obj_setup_object(ObjCreateInfo *createInfo, u32 param2, s32 mapID, s32 param4, Object *parent) {
    ObjDef *def;
    s32 modelCount;
    s32 var;
    s32 flags;
    ModelInstance *tempModel;
    Object *obj;
    s32 tabIdx;
    s32 objId;
    s32 j;
    Object objHeader;
    s32 addr;
    s8 modelLoadFailed;

    objId = createInfo->unk0;

    update_pi_manager_array(0, objId);

    if (param2 & 2) {
        tabIdx = objId;
    } else {
        if (objId > gObjIndexCount) {
            update_pi_manager_array(0, -1);
            return NULL;
        }

        tabIdx = gFile_OBJINDEX[objId];
    }

    bzero(&objHeader, sizeof(Object));

    objHeader.def = obj_load_objdef(tabIdx);
    def = objHeader.def;

    if (def == NULL || (u32)def == 0xFFFFFFFF) {
        return NULL;
    } 
    
    objHeader.srt.flags = 2;

    if (def->flags & 0x80) {
        objHeader.srt.flags = 0x82;
    }

    if (def->flags & 0x40000) {
        objHeader.unk0xb0 |= 0x80;
    }

    if (param2 & 4) {
        objHeader.srt.flags |= 0x2000;
    }

    objHeader.srt.transl.x = createInfo->x;
    objHeader.srt.transl.y = createInfo->y;
    objHeader.srt.transl.z = createInfo->z;
    objHeader.createInfo = createInfo;
    objHeader.tabIdx = tabIdx;
    objHeader.id = objId;
    objHeader.unk0xb2 = param4;
    objHeader.mapID = mapID;
    objHeader.unk_0xa2 = -1;
    objHeader.unk0xb4 = -1;
    objHeader.srt.scale = def->scale;
    objHeader.unk_0x36 = 0xFF;
    objHeader.ptr0xcc = NULL;
    objHeader.unk0x3c = createInfo->unk6 << 3;
    objHeader.unk0x40 = createInfo->unk7 << 3;
    objHeader.dll = NULL;

    if (def->dllID != 0) {
        objHeader.dll = (DLLInst_Object*)dll_load(def->dllID, 6, 1);
    }

    flags = func_80022828(&objHeader);

    if (def->flags & 0x20) {
        flags &= ~1;
    } else {
        flags |= 1;
    }

    if (def->shadowType != 0) {
        flags |= 2;
    } else {
        flags &= ~2;
    }

    if (def->flags & 1) {
        flags |= 0x200;
    }

    var = obj_calc_mem_size(&objHeader, def, flags);

    obj = (Object*)malloc(var, ALLOC_TAG_OBJECTS_COL, NULL);

    if (obj == NULL) {
        obj_free_objdef(tabIdx);
        return NULL;
    }

    bcopy(&objHeader, obj, sizeof(Object));
    bzero((void*)((u32)obj + sizeof(Object)), var - sizeof(Object));

    modelCount = def->numModels;

    obj->modelInsts = (ModelInstance**)((u32)obj + sizeof(Object));

    modelLoadFailed = FALSE;
    var = 0;
    
    if (!(flags & 0x200)) {
        if (flags & 0x400) {
            var = (flags >> 11) & 0xf;

            if (var < modelCount) {
                obj->modelInsts[var] = model_load_create_instance(-def->pModelList[var], flags);

                if (obj->modelInsts[var] == NULL) {
                    modelLoadFailed = TRUE;
                    goto modelLoadFailedLabel;
                } else {
                    tempModel = obj->modelInsts[var];
                    func_80021E74(obj->srt.scale, tempModel);
                }
            }
        } else {
            for (; var < modelCount; var++) {
                obj->modelInsts[var] = model_load_create_instance(-def->pModelList[var], flags);
                if (obj->modelInsts[var] == NULL) {
                    modelLoadFailed = TRUE;
                } else {
                    tempModel = obj->modelInsts[var];
                    func_80021E74(obj->srt.scale, tempModel);
                }
            }
        }
    }

    modelLoadFailedLabel:
    if (modelLoadFailed) {
        func_80022200(obj, modelCount, objId);
        obj_free_objdef(tabIdx);
        return NULL;
    }
     
    addr = obj_alloc_object_state(obj, (u32)&obj->modelInsts[def->numModels]);

    if (flags & 0x40) {
        addr = func_80022868(obj->id, obj, addr);
    }

    if (flags & 0x100) {
        addr = func_8002298C(obj->id, obj->modelInsts[0], obj, addr);
    }

    if ((flags & 0x2) && (def->shadowType != 0)) {
        addr = func_8004D8A4(obj, addr, 0);
    }

    obj->unk_0xa8 = func_80022150(obj) * obj->srt.scale;

    if (def->unk8F != 0) {
        addr = func_8002667C(obj, addr);

        if (def->unk93 & 0x8) {
            addr = func_80026BD8(obj, addr);
        }
    }

    if (def->unk72 != 0) {
        obj->ptr0x6c = (u16*)align_4(addr);
        addr = (u32)obj->ptr0x6c + (def->unk72 * 0x12);
    }

    if (def->numTextures != 0) {
        obj->ptr0x70 = (void*)align_4(addr);
        addr = (u32)obj->ptr0x70 + (def->numTextures * 0x10);
    }

    if (def->unk9b != 0) {
        obj->unk0x74 = align_4(addr);
        addr = (u32)obj->unk0x74 + (def->unk9b * 0x18);
    }

    if (def->unk8F != 0 && def->unk74 != 0) {
        addr = align_4(addr);
        addr = func_80026A20(obj->id, obj->modelInsts[0], obj->objhitInfo, addr, obj);
    }

    if (def->unk9b != 0) {
        obj->unk_0x78 = (ObjectStruct78*)align_4(addr);

        for (j = 0; j < def->unk9b; j++) {
            obj->unk_0x78[j].unk4 = def->unk40[j].unk10;
            obj->unk_0x78[j].unk0 = def->unk40[j].unk0c;
            obj->unk_0x78[j].unk3 = def->unk40[j].unk0f;
            obj->unk_0x78[j].unk1 = def->unk40[j].unk0d;
            obj->unk_0x78[j].unk2 = def->unk40[j].unk0e;
        }
    }

    obj->parent = parent;
    
    return obj;
}

void obj_add_object(Object *obj, u32 someFlags) {
    if (obj->parent != NULL) {
        transform_point_by_object(
            obj->srt.transl.x, obj->srt.transl.y, obj->srt.transl.z,
            &obj->positionMirror.x, &obj->positionMirror.y, &obj->positionMirror.z,
            obj->parent
        );
    } else {
        obj->positionMirror.x = obj->srt.transl.x;
        obj->positionMirror.y = obj->srt.transl.y;
        obj->positionMirror.z = obj->srt.transl.z;
    }

    obj->positionMirror2.x = obj->srt.transl.x;
    obj->positionMirror2.y = obj->srt.transl.y;
    obj->positionMirror2.z = obj->srt.transl.z;

    obj->positionMirror3.x = obj->positionMirror.x;
    obj->positionMirror3.y = obj->positionMirror.y;
    obj->positionMirror3.z = obj->positionMirror.z;

    copy_obj_position_mirrors(obj, obj->createInfo, 0);

    if (obj->objhitInfo != NULL) {
        obj->objhitInfo->unk_0x10.x = obj->srt.transl.x;
        obj->objhitInfo->unk_0x10.y = obj->srt.transl.y;
        obj->objhitInfo->unk_0x10.z = obj->srt.transl.z;

        obj->objhitInfo->unk_0x20.x = obj->srt.transl.x;
        obj->objhitInfo->unk_0x20.y = obj->srt.transl.y;
        obj->objhitInfo->unk_0x20.z = obj->srt.transl.z;
    }

    if (obj->def->unka0 > -1) {
        func_80046320(obj->def->unka0, obj);
    }

    update_pi_manager_array(0, -1);

    if (obj->def->flags & OBJDATA_FLAG44_HasChildren) {
        add_object_to_array(obj, 7);

        if (obj->updatePriority != 90) {
            obj_set_update_priority(obj, 90);
        }
    } else {
        if (obj->updatePriority == 0) {
            obj_set_update_priority(obj, 80);
        }
    }

    if (someFlags & 1) {
        obj->unk0xb0 |= 0x10;
        gObjList[gNumObjs] = obj;
        gNumObjs += 1;

        obj_add_tick(obj);
    }

    if (obj->def->unk5e >= 1) {
        add_object_to_array(obj, 9);
    }

    if (obj->def->flags & OBJDATA_FLAG44_HaveModels) {
        func_80020D90();
    }

    if (obj->def->flags & OBJDATA_FLAG44_DifferentLightColor) {
        add_object_to_array(obj, 56);
    }

    write_c_file_label_pointers(D_80099600, 0x477);
}

u32 obj_calc_mem_size(Object *obj, ObjDef *def, u32 flags) {
    u32 size;

    size = sizeof(Object);

    size += def->numModels * sizeof(u32);

    if (obj->dll != NULL) {
        size += obj->dll->exports->get_state_size(obj, size);
    }

    if (flags & 0x40) {
        size = align_4(size);
        size = align_8(size + 8);
        size += 0x50;
    }

    if (flags & 0x100) {
        size = align_4(size);
        size = align_8(size + 8);
        size += 0x400;
    }

    if ((flags & 2) && (def->shadowType != 0)) {
        size = align_4(size);
        size += 0x44;
    }

    if (def->unk8F != 0) {
        size = align_4(size);
        size += 0xa4;

        if (def->unk93 & 8) {
            size += 0x110;
        }
    }

    if (def->unk72 != 0) {
        size = align_4(size);
        size += def->unk72 * 0x12;
    }

    if (def->numTextures != 0) {
        size = align_4(size);
        size += def->numTextures * 0x10;
    }

    if (def->unk9b != 0) {
        size = align_4(size);
        size += def->unk9b * 0x18;
    }

    if (def->unk8F != 0 && def->unk74 != 0) {
        size = align_8(size);
        size += 300;
    }

    if (def->unk9b != 0) {
        size = align_4(size);
        size += def->unk9b * 5;
    }

    return size;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80021E74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022150.s")

void func_80022200(Object *obj, s32 param2, s32 param3) {
    s32 i;

    for (i = 0; i < param2; i++) {
        if (obj->modelInsts[i] != NULL) {
            ModelInstance *modelInst = obj->modelInsts[i];
            destroy_model_instance(modelInst);
        }
    }
}

// name guessed from leftover strings
void obj_free_tick(Object *obj) {
    if (obj->unk0xb0 & 0x10) {
        linked_list_remove(&gObjUpdateList, obj);
    }
}

void obj_add_tick(Object *obj) {
    void *insertAfter;
    void *node;
    Object *objNode;
    s32 nextFieldOffset;
    
    if (obj->unk0xb0 & 0x10) {
        nextFieldOffset = gObjUpdateList.nextFieldOffset;
        insertAfter = NULL;

        node = gObjUpdateList.head;

        // Insert maintaining sort by update priority
        for (objNode = (Object*)node; node != NULL && obj->updatePriority < ((Object*)node)->updatePriority; objNode = (Object*)node) {
            insertAfter = objNode;
            node = *((void**)(nextFieldOffset + (u32)node));
        }

        linked_list_insert(&gObjUpdateList, insertAfter, (void*)obj);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/obj_destroy_object.s")

void copy_obj_position_mirrors(Object *obj, ObjCreateInfo *param2, s32 param3) {
    DLLInst_Object *dll;
    obj->group = obj->def->group;
    dll = obj->dll;
    if(1) {
        if(dll != NULL) {
            obj->dll->exports->func1(obj, param2, param3);
        }
    }

    obj->positionMirror2.x = obj->srt.transl.x;
    obj->positionMirror3.x = obj->srt.transl.x;
    obj->positionMirror2.y = obj->srt.transl.y;
    obj->positionMirror3.y = obj->srt.transl.y;
    obj->positionMirror2.z = obj->srt.transl.z;
    obj->positionMirror3.z = obj->srt.transl.z;
}

void update_object(Object *obj) {
    if (obj->unk0xb0 & 0x40) {
        return;
    }

    if (obj->unk0xc0 != NULL) {
        if (obj->linkedObject != NULL) {
            obj->linkedObject->objhitInfo->unk_0x48 = 0;
            obj->linkedObject->objhitInfo->unk_0x62 = 0;
        }

        if (obj->objhitInfo != NULL) {
            obj->objhitInfo->unk_0x48 = 0;
            obj->objhitInfo->unk_0x62 = 0;
        }
    } else {
        update_pi_manager_array(1, obj->id);

        if (!(obj->srt.flags & 8)) {
            obj->positionMirror2.x = obj->srt.transl.x;
            obj->positionMirror2.y = obj->srt.transl.y;
            obj->positionMirror2.z = obj->srt.transl.z;

            obj->positionMirror3.x = obj->positionMirror.x;
            obj->positionMirror3.y = obj->positionMirror.y;
            obj->positionMirror3.z = obj->positionMirror.z;
        }

        if (obj->dll != NULL && !(obj->unk0xb0 & 0x8000)) {
            obj->dll->exports->update(obj);

            get_object_child_position(obj,
                &obj->positionMirror.x, &obj->positionMirror.y, &obj->positionMirror.z);
        }

        if (obj->objhitInfo != NULL) {
            if (obj->linkedObject != NULL) {
                obj->linkedObject->objhitInfo->unk_0x48 = 0;
                obj->linkedObject->objhitInfo->unk_0x62 = 0;
            }

            obj->objhitInfo->unk_0x4c = 0;
            obj->objhitInfo->unk_0x48 = 0;
            obj->objhitInfo->unk_0x62 = 0;
        }

        if (obj->unk0x58 != NULL) {
            obj->unk0x58->unk10f = 0;
        }

        obj->unk0xaf &= 0xFFF8;

        update_pi_manager_array(1, -1);
    }
}

void func_8002272C(Object *obj) {
    update_pi_manager_array(3, obj->id);

    if (obj->dll != NULL && !(obj->unk0xb0 & 0x2000)) {
        obj->dll->exports->func3(obj);

        get_object_child_position(obj,
            &obj->positionMirror.x, &obj->positionMirror.y, &obj->positionMirror.z);
    }

    update_pi_manager_array(3, -1);
}

u32 obj_alloc_object_state(Object *obj, u32 addr) {
    u32 stateSize = 0;
    
    addr = align_4(addr);

    if (obj->dll != NULL) {
        stateSize = obj->dll->exports->get_state_size(obj, addr);
    }

    if (stateSize != 0) {
        obj->state = (void*)addr;
        addr += stateSize;
    } else {
        obj->state = NULL;
    }

    return addr;
}

u32 func_80022828(Object *obj) {
    if (obj->dll != NULL) {
        return obj->dll->exports->func6(obj);
    } else {
        return 0;
    }
}

u32 func_80022868(s32 objId, Object *obj, u32 addr) {
    obj->ptr0x60 = (ObjectStruct60*)align_4(addr);

    addr = align_8((u32)obj->ptr0x60 + sizeof(ObjectStruct60));
    obj->ptr0x60->unk4 = (UNK_PTR*)addr;

    addr += 80;

    obj_load_event(obj, objId, obj->ptr0x60, 0, 1);

    return addr;
}

void obj_load_event(Object *obj, s32 objId, ObjectStruct60 *outParam, s32 id, u8 dontQueueLoad) {
    ObjDefEvent *eventList;
    ObjDefEvent *event;
    
    eventList = obj->def->pEvent;

    outParam->unk0 = 0;
    
    if (eventList == NULL) {
        return;
    }

    for (event = eventList; event->id != -1; event++) {
        if (event->id == id) {
            s32 offset;

            offset = event->fileOffsetInBytes;

            outParam->unk0 = event->fileSizeInBytes;

            if (outParam->unk0 > 80) {
                outParam->unk0 = 80;
            }

            if (eventList) {}

            if (!dontQueueLoad) {
                queue_load_file_region_to_ptr((void**)outParam->unk4, OBJEVENT_BIN, offset, outParam->unk0);
            } else {
                read_file_region(OBJEVENT_BIN, outParam->unk4, offset, outParam->unk0);
            }

            break;
        }
    }
}

u32 func_8002298C(s32 objId, ModelInstance *param2, Object *obj, u32 addr) {
    if (param2 == 0) {
        return addr;
    } else {
        obj->ptr0x5c = (ObjectStruct5C*)align_4(addr);

        addr = align_8((u32)obj->ptr0x5c + sizeof(ObjectStruct5C));
        obj->ptr0x5c->unk4 = (UNK_PTR*)addr;

        return addr + 1024;
    }
}

void obj_load_weapondata(Object *obj, s32 param2, WeaponDataPtr *outParam, s32 id, u8 queueLoad) {
    ObjDefWeaponData *weaponDataList;
    ObjDefWeaponData *weaponData;
    
    weaponDataList = obj->def->pWeaponData;

    outParam->sizeInBytes = 0;
    
    if (weaponDataList == NULL) {
        return;
    }

    for (weaponData = weaponDataList; weaponData->id != -1; weaponData++) {
        if (weaponData->id == id) {
            s32 offset;

            offset = weaponData->fileOffsetInBytes;

            outParam->sizeInBytes = weaponData->fileSizeInBytes;

            if (outParam->sizeInBytes > 1024) {
                outParam->sizeInBytes = 1024;
            }

            if (weaponDataList) {}

            if (queueLoad) {
                queue_load_file_region_to_ptr((void**)outParam->ptr, WEAPONDATA_BIN, offset, outParam->sizeInBytes);
            } else {
                read_file_region(WEAPONDATA_BIN, outParam->ptr, offset, outParam->sizeInBytes);
            }

            break;
        }
    }
}

ObjDef *obj_load_objdef(s32 tabIdx) {
    ObjDef *def;
    s32 fileOffset;
    s32 fileSize;

    if (tabIdx >= gNumObjectsTabEntries) {
        return NULL;
    }
    
    if (gObjDefRefCount[tabIdx] != 0) {
        gObjDefRefCount[tabIdx]++;
        def = gLoadedObjDefs[tabIdx];
        return def;
    }
    
    fileOffset = gFile_OBJECTS_TAB[tabIdx];
    fileSize = gFile_OBJECTS_TAB[tabIdx + 1] - fileOffset;

    def = (ObjDef*)malloc(fileSize, ALLOC_TAG_OBJECTS_COL, NULL);
    if (def != NULL) {
        read_file_region(OBJECTS_BIN, (void*)def, fileOffset, fileSize);

        if (def->pEvent != 0) {
            def->pEvent = (ObjDefEvent*)((u32)def + (u32)def->pEvent);
        }

        if (def->pHits != 0) {
            def->pHits = (ObjDefHit*)((u32)def + (u32)def->pHits);
        }

        if (def->pWeaponData != 0) {
            def->pWeaponData = (ObjDefWeaponData*)((u32)def + (u32)def->pWeaponData);
        }

        def->pModelList = (u32*)((u32)def + (u32)def->pModelList);
        def->pTextures = (UNK_PTR*)((u32)def + (u32)def->pTextures);
        def->unk10 = (UNK_PTR*)((u32)def + (u32)def->unk10);

        if (def->unk18 != 0) {
            def->unk18 = (u32*)((u32)def + (u32)def->unk18);
        }

        if (def->unk40 != 0) {
            def->unk40 = (ObjDefStruct40*)((u32)def + (u32)def->unk40);
        }

        if (def->pSeq != 0) {
            def->pSeq = (u16*)((u32)def + (u32)def->pSeq);
        }

        def->pModLines = NULL;

        def->pAttachPoints = (AttachPoint*)((u32)def + (u32)def->pAttachPoints);

        def->pIntersectPoints = NULL;

        if (def->modLineNo > -1) {
            def->pModLines = obj_load_objdef_modlines(def->modLineNo, &def->modLineCount);
            func_800596BC(def);
        }

        gLoadedObjDefs[tabIdx] = def;
        gObjDefRefCount[tabIdx] = 1;

    } else {
        return NULL;
    }

    return def;
}

void obj_free_objdef(s32 tabIdx) {
    if (gObjDefRefCount[tabIdx] != 0) {
        gObjDefRefCount[tabIdx]--;

        if (gObjDefRefCount[tabIdx] == 0) {
            ObjDef *def;

            def = gLoadedObjDefs[tabIdx];
            
            if (def->pModLines != NULL) {
                free(def->pModLines);
            }

            if (def->pIntersectPoints != NULL) {
                free(def->pIntersectPoints);
            }

            free(def);
        }
    }
}

ModLine *obj_load_objdef_modlines(s32 modLineNo, s16 *modLineCount) {
    ModLine *modLines;
    s32 fileSize;
    s32 totalEntries;
    s32 *tabEntry;
    s32 size;
    s32 offset;

    modLines = NULL;

    fileSize = get_file_size(MODLINES_TAB);
    totalEntries = (fileSize - 4) >> 2;

    if (modLineNo > totalEntries) {
        return NULL;
    }

    tabEntry = (s32*)malloc(16, ALLOC_TAG_TEST_COL, NULL);
    read_file_region(MODLINES_TAB, (void*)tabEntry, modLineNo << 2, 8);

    offset = tabEntry[0];
    size = tabEntry[1] - tabEntry[0];

    if (size > 0) {
        modLines = (ModLine*)malloc(size, ALLOC_TAG_TRACK_COL, NULL);
        read_file_region(MODLINES_BIN, (void*)modLines, offset, size);
    }

    free(tabEntry);

    *modLineCount = (size / sizeof(ModLine));

    return modLines;
}

void doNothing_80022DD8(s32 a0, s32 a1, s32 a2) { }

s32 func_80022DEC(void) {
    return gObjIndexCount;
}

s32 func_80022DFC(s32 idx) {
    if (idx > gObjIndexCount) {
        return FALSE;
    }

    return gFile_OBJINDEX[idx] != -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022E3C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80022EC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/obj_free_object.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/obj_alloc_create_info.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023628.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023894.s")

Object *get_player(void) {
    Object **obj;
    s32 idx;
    obj = object_getter(0, &idx);
    if(idx) {} else {}; //wat
    if(idx) return *obj;
    else return NULL;
}

Object *get_sidekick() {
    Object **objectList;
    s32 count;

    objectList = object_getter(1, &count);

    if (count) {}

    if (count != 0) {
        return objectList[0];
    } else {
        return NULL;
    }
}

void obj_clear_map_id(Object *obj) {
    obj->mapID = -1;
}

void obj_infer_map_id(Object *obj) {
    obj->mapID = map_get_map_id_from_xz_ws(obj->srt.transl.x, obj->srt.transl.z);
}

s32 obj_integrate_speed(Object *obj, f32 dx, f32 dy, f32 dz) {
    obj->srt.transl.x += dx;
    obj->srt.transl.y += dy;
    obj->srt.transl.z += dz;

    return 0;
}

void obj_set_update_priority(Object *obj, s8 priority) {
    obj->updatePriority = priority;
}

void func_80023A18(Object *obj, s32 param2) {
    obj->unk0xb0 &= 0xF0FF;

    if (param2 == obj->modelInstIdx) {
        return;
    }

    if (param2 < 0) {
        param2 = 0;
    } else if (param2 >= obj->def->numModels) {
        param2 = obj->def->numModels - 1;
    }

    obj->unk0xb0 |= 0x800;
    obj->unk0xb0 |= (param2 << 8) & 0x700;
}

void func_80023A78(Object *obj, ModelInstance *modelInst, Model *model) {
    s32 modelInstIdx;
    ModelInstance *modelInst2;
    s32 prevAnimId;

    modelInstIdx = (obj->unk0xb0 & 0x700) >> 8;
    modelInst2 = obj->modelInsts[modelInstIdx];

    modelInst2->unk_0x34 &= 0xFFF0;
    modelInst2->unk_0x34 |= modelInst->unk_0x34 & 7;

    prevAnimId = obj->curAnimId;

    obj->modelInstIdx = modelInstIdx;
    obj->curAnimId = -1;
    obj->unk_0xa2 = -1;

    func_80023D30(obj, prevAnimId, obj->animTimer, 0);

    if (obj->objhitInfo != NULL) {
        if ((obj->objhitInfo->unk_0x5a & 0x10)) {
            obj->objhitInfo->unk_0x9f = 2;
        }

        obj->objhitInfo->unk_0x9e = 1;
    }

    obj->unk0xb0 &= 0xF0FF;
}

extern s8 gEffectBoxCount;
extern Object *gEffectBoxes[20];

void obj_add_effect_box(Object *obj) {
    gEffectBoxes[gEffectBoxCount] = obj;
    gEffectBoxCount += 1;
}

void obj_free_effect_box(Object *obj) {
    s32 i;
    s32 newCount;

    i = 0;

    while (i < gEffectBoxCount && obj != gEffectBoxes[i]) {
        i++;
    }

    newCount = gEffectBoxCount - 1;
    
    if (i != gEffectBoxCount) {
        while (i < newCount) {
            gEffectBoxes[i] = gEffectBoxes[i + 1];
            i++;
        }

        gEffectBoxCount = newCount;
    }
}

void func_80023BF8(Object *obj, s32 param2, s32 param3, s32 param4, u8 param5, u8 param6) {
    ObjectStruct78 *dst;

    if (obj != NULL) {
        dst = obj->unk_0x78;

        if (dst != NULL) {
            dst += obj->unk_0xd4;

            if (param2 != 0) {
                dst->unk0 = param2 >> 2;
            }

            if (param4 != 0) {
                dst->unk1 = param4 >> 2;
            }

            if (param3 != 0) {
                dst->unk2 = param3 >> 2;
            }

            if (param5 != 0) {
                dst->unk3 = param5;
            }

            if (param6 != 0) {
                dst->unk4 = param6;
            }
        }
    }
}

void func_80023C6C(Object *obj) {
    ObjDefStruct40 *src;
    ObjectStruct78 *dst;

    if (obj != NULL) {
        dst = obj->unk_0x78;

        if (dst != NULL) {
            src = &obj->def->unk40[obj->unk_0xd4];
            dst += obj->unk_0xd4;

            dst->unk0 = src->unk0c;
            dst->unk1 = src->unk0d;
            dst->unk2 = src->unk0e;
            dst->unk3 = src->unk0f;
            dst->unk4 = src->unk10;
        }
    }
}

void func_80023CD8(Object *obj, u16 param2) {
    if (param2 > obj->def->unk9b) {
        param2 = 0;
    }

    obj->unk_0xd4 = param2;
}

void func_80023D08(Object *obj, u16 param2) {
    if (param2 > 4) {
        param2 = 0;
    }

    obj->unk_0xd8 = param2;
}

// start of objanim.c or something like that?
#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80023D30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800240BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024108.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002493C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024D74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024DD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024E2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80024E50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800250F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025140.s")

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025540.s")
#else
//in retail SFA 1.0 I believe this is at 8002ed18
//but it's different because SFA doesn't use Model Instances
//or, this might be a completely different function...
void func_80025540(Object *obj, s32 a1, s32 a2)
{
    Model *model = obj->models[obj->curModel];
    void **anims; //this is a struct of some sort.
    if(model->unk66) {
        anims = model->animations;
        if (!anims) { }
        func_800255F8(obj, model, anims, a1, (short) a2); //probably ObjSetBlendMove
        //not certain about the order/count of params here.
    }
}
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_8002559C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_800255F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/object/func_80025CD4.s")