#ifndef _SYS_GAME_ACTOR_ACTOR_H
#define _SYS_GAME_ACTOR_ACTOR_H

#include <PR/gbi.h>
#include "sys/gfx/model.h"
#include "sys/math.h"
#include "dll.h"
#include "dll_def.h"
#include "objdata.h"
#include "hitbox.h"
#include "unktypes.h"

/** Actor/Game Object system
 */

//used for PlayerPosBuffer and something else
struct Vec3_Int{
	Vec3f f;
	u32 i; //seems to be a 32-bit bool. (for player pos buffer it's a frame count)
};

typedef struct {
	s16 unk0;
	u8 _unk2[4];
	u8 unk6;
	u8 unk7;
	f32 x;
	f32 y;
	f32 z;
	s32 unk14;
	u8 _un18[2];
	s16 unk1a;
} ObjCreateInfo;

typedef struct {
/*0000*/    u8 unk_0x0[0x10 - 0x0];
/*0010*/	u8 *unk_0x10;
/*0014*/	u8 unk_0x14[0x44 - 0x14];
/*0044*/    s32 unk_0x44;
/*0048*/	u8 unk_0x48[0x5d - 0x48];
/*005D*/	s8 unk_0x5d;
/*005E*/    u8 unk_0x5e[0x71 - 0x5e];
/*0071*/    u8 unk_0x71;
/*0072*/	u8 unk_0x72;
} ActorUnk0x50;

typedef struct {
/*0000*/    u8 unk_0x0[0xc - 0x0];
/*000C*/    Gfx *gdl;
/*0010*/    u8 unk_0x10[0x20 - 0x10];
/*0020*/    Vec3f tr;
/*002C*/    u32 unk_0x2c;
/*0030*/    u32 flags;
} ActorUnk0x64;

typedef struct {
/*0000*/    u8 unk_0x0[0x62 - 0x0];
/*0062*/    s8 unk_0x62;
} ActorUnk0xc0_0xb8;

struct TActor;

typedef struct {
/*0000*/    u8 unk_0x0[0x30 - 0x0];
/*0030*/    struct TActor *unk_0x30;
/*0034*/    u8 unk_0x34[0xb8 - 0x34];
/*00b8*/    ActorUnk0xc0_0xb8 *unk_0xb8;
} ActorUnk0xc0;

typedef struct {
	s32 unk0;
	UNK_PTR *unk4;
} Actor5c;

typedef struct {
	s32 unk0; // size of thing at unk4
	UNK_PTR *unk4;
} Actor60;

typedef struct {
	s32 sizeInBytes;
	UNK_PTR *ptr;
} WeaponDataPtr;

typedef struct {
/*0000*/    u8 unk0[0x80 - 0x00];
/*0080*/    MtxF unk80[2]; 				// probably length of 2
/*0100*/    UNK_PTR *unk100;
/*0104*/    u8 unk104[0x10c - 0x104];
/*010c*/    u8 unk10c; 					// index into field 0x80?
/*010d*/    UNK_TYPE_8 unk10d;
/*010e*/    UNK_TYPE_8 unk10e;
/*010f*/    UNK_TYPE_8 unk10f;
/*0110*/    u8 unk110[0x146 - 0x110];
/*0146*/    s16 unk146;
} Actor58;

typedef struct {
/*0000*/    u8 unk0;
/*0001*/    u8 unk1;
/*0002*/    u8 unk2;
/*0003*/    u8 unk3;
/*0004*/    u8 unk4;
} Actor78;

// Base interface for object DLLs
DLL_INTERFACE_BEGIN(Object)
    /*0*/ void (*func1)(struct TActor *obj, ObjCreateInfo *createInfo, s32);
    /*1*/ void (*update)(struct TActor *obj);
    /*2*/ void (*func3)(struct TActor *obj); // unknown args
    /*3*/ void (*func4)(); // unknown args
    /*4*/ void (*func5)(); // unknown args
    /*5*/ u32 (*func6)(struct TActor *obj);
    /*6*/ u32 (*get_state_size)(struct TActor *obj, u32);
DLL_INTERFACE_END()

// arg3 and arg4 are unknown types
// always called by DLL 3 "ANIM" during cutscenes?
typedef s32 (*TActorCallback)(struct TActor *, struct TActor *, void *, void *);

//prelimnary, lots of unknowns
//contains pointer-to-own-type fields, so `typedef struct _TActor {`
//must be used instead of `typedef struct {`
typedef struct TActor {
/*0000*/    SRT srt;
/*0018*/    Vec3f positionMirror; //local vs global?
/*0024*/    Vec3f speed;
/*0030*/    struct TActor *linkedActor; //only used by update_objects?
/*0034*/    u8 unk_0x34;
/*0035*/    s8 matrixIdx;
/*0036*/    u8 unk_0x36; // transparency
/*0037*/    u8 unk_0x37; // also transparency? (set to unk_0x36)
/*0038*/    struct TActor *next;
/*003C*/    f32 unk0x3c;
/*0040*/    f32 unk0x40;
/*0044*/    s16 objGroup; // complete guess at a name, needs more investigation
/*0046*/    s16 unk0x46;
/*0048*/    s16 unk0x48;
/*004A*/    u8 unk0x4a[0x4c - 0x4a];
/*004C*/    ObjCreateInfo *createInfo;
/*0050*/    ObjData* data;
/*0054*/    ActorObjhitInfo* objhitInfo;
/*0058*/    Actor58 *unk0x58;
/*005C*/    Actor5c *ptr0x5c;
/*0060*/    Actor60 *ptr0x60;
/*0064*/    ActorUnk0x64* ptr0x64;
/*0068*/    DLLInst_Object *dll; //same in SFA
/*006C*/    u16 *ptr0x6c;
/*0070*/    void* ptr0x70;
/*0074*/    u32 unk0x74;
/*0078*/    Actor78 *unk_0x78;
/*007C*/    ModelInstance **modelInsts;
/*0080*/    Vec3f positionMirror2; //gets copied twice.
/*008C*/    Vec3f positionMirror3; //not sure why.
/*0098*/    float animTimer; //guessed from SFA
/*009C*/    f32 unk0x9c;
/*00A0*/    s16 curAnimId;
/*00A2*/	s16 unk_0xa2;
/*00A4*/	f32 unk_0xa4;
/*00A8*/	f32 unk_0xa8;
/*00AC*/    s8 mapID;
/*00AD*/    s8 modelInstIdx;
/*00AE*/    s8 updatePriority;
/*00AF*/    u8 unk0xaf;
/*00B0*/    u16 unk0xb0;
/*00B2*/    UNK_TYPE_16 unk0xb2;
/*00B4*/    s16 unk0xb4;
/*00B6*/	u8 unk0xb6[2];
/*00B8*/	void* state; //type depends on object
/*00BC*/	TActorCallback unk0xbc; // some kind of cutscene anim callback?
/*00C0*/	ActorUnk0xc0 *unk0xc0;
/*00C4*/	UNK_TYPE_32 unk0xc4;
/*00C8*/    struct TActor *linkedActor2;
/*00CC*/    void* ptr0xcc;
/*00D0*/    u8 unk_0xd0[0xd4 - 0xd0];
/*00D4*/    u8 unk_0xd4;
/*00D5*/    u8 unk_0xd5[0xd8 - 0xd5];
/*00D8*/    u8 unk_0xd8;
/*00D9*/    u8 unk_0xd9[0xda - 0xd9];
/*00DA*/    u8 unk_0xda;
/*00DB*/    u8 unk_0xdb[0xdc - 0xdb];
/*00DC*/    s32 unk0xdc;
/*00E0*/    u8 unk_0xe0[4];
} TActor; // size is 0xe4; other actor-related data is placed in the following memory

typedef struct ObjListItem {
	s16 count;
	s16 size;
	TActor *obj;
} ObjListItem;


extern u8 delayByte; //60/int(x) FPS x<=6
extern u8 delayByteMirror;
extern float delayFloat;
extern float delayFloatMirror;
extern float inverseDelay; // 1/delayByte
extern float inverseDelayMirror; // why the mirrors, if they aren't used?

extern struct TActor * object_pointer_array[]; //first is always player character.
extern u16 objectCount;
extern struct Vec3_Int Vec3_Int_array[];

#endif //_SYS_GAME_ACTOR_ACTOR_H
