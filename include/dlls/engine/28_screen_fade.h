#ifndef _DLLS_28_H
#define _DLLS_28_H

#include "PR/ultratypes.h"
#include "PR/gbi.h"
#include "dll_def.h"

enum ScreenFadeType {
    SCREEN_FADE_BLACK = 1,
    SCREEN_FADE_WHITE = 2,
    SCREEN_FADE_WHITE_RADIAL = 3,
    SCREEN_FADE_RED = 4
};

DLL_INTERFACE_BEGIN(28_screen_fade)
    /*0*/ void (*draw)(Gfx **gdl, s32 *mtxs, s32 *vtxs);
    /*1*/ void (*fade)(s32 duration, s32 type);
    /*2*/ void (*fade_reversed)(s32 duration, s32 type);
    /*3*/ void (*func3)(s32 param1, s32 type, f32 param3);
    /*4*/ f32 (*get_progress)();
    /*5*/ s32 (*is_complete)();
DLL_INTERFACE_END()

#endif //_DLLS_28_H
