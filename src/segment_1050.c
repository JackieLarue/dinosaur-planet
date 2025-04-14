#include "common.h"

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/segment_1050/func_80000450.s")
#else
typedef struct {
    u8 r, g, b;
} RGB24;

typedef struct LActionLine {
    u16 unk1;
    u16 unk2;//(Sometimes has same value as unk1, and seems to relate to it?)
    s16 unk3;//(This series of s16 parameters could be vector components for the light direction/position?)
    s16 unk4;
    s16 unk5;
    s16 unk6;
    s16 unk7;//(may be Y component of the light’s direction/origin)
    u16 actionIndex;//(the index of the action within LACTIONS.bin)
    u16 lightLayer;//(lights can be combined when they’re each placed on different layers)
    u8 unk8;//(Seems to be related to the flickering/cycling animation that can be applied to lights?)
    u8 unk9;//(Seems to affect how the light’s colours cycle when flickering?)
    u8 unk10;//(Also related to light animation?)
    RGB24 colour1;//(the “unlit” light colour - used when far from light sources with falloff, or when a character polygon faces away from light)
    RGB24 colour2;//(the main “bright” light colour -  note that the light shading is applied by multiplying a vertex colour with the character model’s base colour, so you can’t go brighter than that base colour)
    u8 unk11;//(Possible values seem to be 0, 2, 5)
    u8 unk12;//(Possible values seem to be 0, 1. Unsure, but might provide lighting for BLOCKS when set to 1?)
    s8 unk13;//(Possible values seem to be 0, 0xff, 0xdc, 0xf5, 0x9b – maybe involved in deciding whether the light affects characters vs. BLOCKS?)
    s8 unk14;//(Possible values seem to be 0, 0x1b, 0xff, 0x18, 0x12 – might be another setting bitfield?)
    u8 radius1;//(The fall-off distance for colour1)
    u8 radius2;//(The fall-off distance for colour2)
    u8 padding1;//(Always 0)
    u8 unk15;//(Possible values: 0, 1, 2, 3, 0xa)
    u8 unk16;//(Usually 0, but other possible values: 0x7f, 0x50, 0x34, 0xd3)
    u32 padding2;//(Always 0)
} LActionLine;

//so this function loads in light actions which are defined as 40 bytes commands or smth
//need to figure out struct for a light action
s32 func_80000450(s32 arg0, s32 arg1, u16 amnt, s8 arg3, s32 arg4, s32 arg5) {
    s16 some_flag0;
    u8 some_flag1;
    LActionLine *laction_ptr;
    laction_ptr = malloc(sizeof(LActionLine), -1, 0);
    queue_load_file_region_to_ptr(
        (void **) laction_ptr, 
        LACTIONS_BIN, 
        amnt * (sizeof(LActionLine)), 
        sizeof(LActionLine));

    if (laction_ptr != NULL) {
        if (arg5 != 0) {
            some_flag0 = laction_ptr->unk11;
            laction_ptr->unk8 = (u8) (laction_ptr->unk8 | 0x40);
            if (some_flag0 == 2) {
                gDLL_57->exports->func[1].withOneArg(laction_ptr);
            } else if (some_flag0 == 5) {
                gDLL_58->exports->func[1].withOneArg(laction_ptr);
            } else {
                gDLL_newlfx->exports->func[0].withSixArgs(0, arg1, laction_ptr, arg3, arg4, arg5);
            }
        } else {
            some_flag1 = laction_ptr->unk11;
            do { 
                if (some_flag1 == 2) { 
                    gDLL_57->exports->func[1].withOneArg(laction_ptr); 
                } else if (laction_ptr->unk11 == 5) { 
                    gDLL_58->exports->func[1].withOneArg(laction_ptr); 
                } else { 
                    gDLL_newlfx->exports->func[0].withSixArgs(arg0, arg1, laction_ptr, arg3, arg4, 0); 
                } 
            } while (0);
        }
    }
    free(laction_ptr);
    return 0;
}
#endif

#if 0
#pragma GLOBAL_ASM("asm/nonmatchings/segment_1050/func_80000608.s")
#else
s32 func_80000608(s32 arg0, s32 arg1, u16 amnt, s8 arg3, s32 check) {
    s16 some_flag0;
    u8 some_flag1;
    LActionLine* laction_ptr;
    laction_ptr = malloc(sizeof(LActionLine), -1, NULL);
    queue_load_file_region_to_ptr(
        (void **) laction_ptr, 
        LACTIONS_BIN, 
        amnt * (sizeof(LActionLine)), 
        sizeof(LActionLine));
    
    if (laction_ptr != NULL) {
        laction_ptr->unk1 = 0xC;
        if (check != 0) {
            some_flag0 = laction_ptr->unk11;
            laction_ptr->unk8 = (u8) (laction_ptr->unk8 | 0x40);
            if (some_flag0 == 2) {
                gDLL_57->exports->func[1].withOneArg(laction_ptr);
            } else if (some_flag0 == 5) {
                gDLL_58->exports->func[1].withOneArg(laction_ptr);
            } else {
                //asVoid
                //gDLL_newlfx->exports->func[0].withTwoArgs(/* extra? */ arg4, /* extra? */ check);
                gDLL_newlfx->exports->func[0].withFourArgs(0, arg1, laction_ptr, arg3);
            }
        } else {
            //do {
            some_flag1 = laction_ptr->unk11;
            if (some_flag1 == 2) {
                gDLL_57->exports->func[1].withOneArg(laction_ptr);
            } else if (some_flag1 == 5) {
                gDLL_58->exports->func[1].withOneArg(laction_ptr);
            } else {
                //gDLL_newlfx->exports->func[0].withTwoArgs(/* extra? */ arg4, /* extra? */ 0);
                gDLL_newlfx->exports->func[0].withFourArgs(arg0, arg1, laction_ptr, arg3);
            }
            //} while (0);
        }
    }
    free(laction_ptr);
    return 0;
}
#endif
