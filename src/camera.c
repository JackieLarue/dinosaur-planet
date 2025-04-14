#include "common.h"
#include "libultra/io/piint.h"

#define CAMERA_COUNT 12

typedef struct
{
/*0000*/    SRT srt;
/*0018*/    f32 unk_0x18;
/*001C*/    u32 unk_0x1c;
/*0020*/    f32 unk_0x20;
/*0024*/    f32 unk_0x24;
/*0028*/    f32 unk_0x28;
/*002C*/    f32 dty;
/*0030*/    f32 unk_0x30;
/*0034*/    f32 unk_0x34;
/*0038*/    f32 unk_0x38;
/*003C*/    f32 unk_0x3c;
/*0040*/    Object *object;
/*0044*/    f32 tx;
/*0048*/    f32 ty;
/*004C*/    f32 tz;
/*0050*/    s16 yaw;
/*0052*/    s16 pitch;
/*0054*/    s16 roll;
/*0056*/    u16 unk_0x56;
/*0058*/    u16 unk_0x58;
/*005A*/    s16 dpitch;
/*005C*/    s8 unk_0x5c;
/*005D*/    s8 unk_0x5d;
} Camera;

typedef union
{
    Mtx m;
    MtxF mf;
} Mtx_MtxF;

typedef struct
{
/*0000*/    Mtx_MtxF *mtx;
/*0004*/    s16 count;
} MatrixSlot;

typedef struct
{
/*0000*/    s32 x1;
/*0004*/    s32 y1;
/*0008*/    s32 x2;
/*000C*/    s32 y2;
/*0010*/    s32 posX;
/*0014*/    s32 posY;
/*0018*/    s32 width;
/*001C*/    s32 height;
/*0020*/    s32 ulx;
/*0024*/    s32 uly;
/*0028*/    s32 lrx;
/*002C*/    s32 lry;
/*0030*/    u32 flags;
} Viewport;

extern SRT gCameraSRT;
extern MtxF gViewMtx;
extern MtxF gViewProjMtx;
extern Mtx *gRSPMtxList;
extern f32 gWorldX;
extern f32 gWorldZ;
extern Mtx *gRSPMatrices[2];
extern MtxF gViewMtx2;
extern Mtx gRSPViewMtx2;
extern Viewport gViewports[2]; // FIXME: how many?
extern Vp gRSPViewports[2]; // FIXME: how many?
extern u32 gCameraGroupSelector;
extern MatrixSlot gMatrixPool[2]; // FIXME: how many?
extern u32 gMatrixCount;
extern Camera gCameras[CAMERA_COUNT];
extern s8 gTriggerUseAlternateCamera;
extern s8 gUseAlternateCamera;
extern s32 gCameraSelector;
extern MtxF gObjectMatrices[2]; // FIXME: how many items are there?
extern MtxF gInverseObjectMatrices[2]; // FIXME: how many items are there?
extern f32 FLOAT_8008c52c;
extern f32 gFovY;
extern f32 gAspect;
extern f32 gNearPlane;
extern f32 gFarPlane;
extern MtxF gProjectionMtx;
extern Mtx gRSPProjectionMtx;
extern u16 gPerspNorm;
extern u32 UINT_800a66f8;
extern u32 UINT_800a6a54;
extern s8 gMatrixIndex;
extern s16 D_8008C518;
extern s16 D_8008C51C;
extern s8 D_8008C520; // gAntiPiracyViewport?
extern u32 D_B0000578;
extern s16 SHORT_8008c524;
extern s16 FB_BGCOLOR;
extern f32 D_800A6270;
extern f32 D_800A6274;
extern MtxF gAuxMtx2;
extern s32 D_800A6700;
extern MtxF D_8008C788;

// .rodata
extern f32 D_8009837C; // 10000.0
extern f32 D_80098380; // 1.3333334
extern f32 D_80098384; // 10000.0

void func_80001914(s32 tx, s32 ty, s32 tz, s32 roll, s32 pitch, s32 yaw);
s32 func_80001A5C(s32);
void set_camera_selector(s32 selector);
void func_800021A0(Gfx **gdl, Mtx **rspMtxs);
Camera *get_camera();

// camera_init
void func_80001220() {
    s32 i;
    u32 stat;

    for (i = 0; i < 12; i++) {
        gCameraSelector = i;
        func_80001914(200, 200, 200, 0, 0, 180);
    }

    gTriggerUseAlternateCamera = 0;
    gUseAlternateCamera = 0;
    gCameraSelector = 0;
    UINT_800a66f8 = 0;
    UINT_800a6a54 = 0;
    gMatrixCount = 0;
    gMatrixIndex = 0;
    gFarPlane = D_8009837C;
    D_8008C518 = 0;
    D_8008C520 = 0;

    WAIT_ON_IOBUSY(stat);

    // 0xB0000578 is a direct read from the ROM as opposed to RAM
    if (((D_B0000578 & 0xFFFF) & 0xFFFF) != 0x8965) {
        D_8008C520 = TRUE;
    }

    gAspect = D_80098380;
    gFovY = 60.0f;

    guPerspectiveF(&gProjectionMtx.m, &gPerspNorm, gFovY, gAspect, gNearPlane, gFarPlane, 1.0f);
    matrix_f2l(&gProjectionMtx.m, &gRSPProjectionMtx);

    FLOAT_8008c52c = gProjectionMtx.m[0][0];
    SHORT_8008c524 = 0;
    FB_BGCOLOR = 0;
}

void func_800013BC() {
    UINT_800a6a54 = 1;
}

void func_800013D0() {
    UINT_800a6a54 = 0;
}

u32 MusPtrBankGetCurrent() {
    return UINT_800a6a54;
}

// camera_get_fov
f32 get_fov_y()
{
    return gFovY;
}

// camera_set_fov
void set_fov_y(f32 fovY)
{
    if (fovY > 90.0f) {
        fovY = 90.0f;
    } else if (fovY < 40.0f) {
        fovY = 40.0f;
    }

    gFovY = fovY;

    guPerspectiveF(&gProjectionMtx, &gPerspNorm, gFovY, gAspect, gNearPlane, gFarPlane, 1.0f);
    matrix_f2l(&gProjectionMtx, &gRSPProjectionMtx);
    FLOAT_8008c52c = gProjectionMtx.m[0][0];
}

void set_ortho_projection_matrix(f32 l, f32 r, f32 b, f32 t)
{
    guOrthoF(&gProjectionMtx, l, r, b, t, 0.0f, 400.0f, 20.0f);
}

void set_aspect(f32 aspect)
{
    gAspect = aspect;
    guPerspectiveF(&gProjectionMtx, &gPerspNorm, gFovY, gAspect, gNearPlane, gFarPlane, 1.0f);
    matrix_f2l(&gProjectionMtx, &gRSPProjectionMtx);
    FLOAT_8008c52c = gProjectionMtx.m[0][0];
    gProjectionMtx.m[0][3] *= 0.5f;
}

void set_near_plane(f32 near)
{
    gNearPlane = near;
    guPerspectiveF(&gProjectionMtx, &gPerspNorm, gFovY, gAspect, gNearPlane, gFarPlane, 1.0f);
    matrix_f2l(&gProjectionMtx, &gRSPProjectionMtx);
    FLOAT_8008c52c = gProjectionMtx.m[0][0];
    gProjectionMtx.m[0][3] *= 0.5f;
}

void func_80001660(f32 farPlane, s32 param2) {
    if (param2 != 0) {
        D_8008C51C = param2;
        D_8008C518 = D_8008C51C;
        D_800A6270 = gFarPlane;
        D_800A6274 = farPlane;
    } else {
        gFarPlane = farPlane;
    }
}

f32 get_far_plane()
{
    return gFarPlane;
}

void func_800016B8()
{
    set_near_plane(4.0f);
}

void func_800016E0() {
    func_80001660(D_80098384, 60);
}

void func_80001708()
{
    guPerspectiveF(&gProjectionMtx, &gPerspNorm, 60.0f, 4.0f / 3.0f, gNearPlane, gFarPlane, 1.0f);
    matrix_f2l(&gProjectionMtx, &gRSPProjectionMtx);
}

MtxF *camera_get_aux_mtx() {
    return &gAuxMtx2;
}

u32 func_80001788() {
    return UINT_800a66f8;
}

u32 get_camera_selector()
{
    return gCameraSelector;
}

void func_800017A8(Gfx **gdl, Mtx **rspMtxs) {
    Camera *camera;
    s16 yaw;
    s16 pitch;
    s16 roll;
    s16 dpitch;
    f32 posX;
    f32 posY;
    f32 posZ;

    func_80001A5C(0);
    set_camera_selector(0);

    camera = get_camera();
    yaw = camera->srt.yaw;
    pitch = camera->srt.pitch;
    roll = camera->srt.roll;
    posX = camera->srt.transl.x;
    posY = camera->srt.transl.y;
    posZ = camera->srt.transl.z;
    dpitch = camera->dpitch;

    camera->srt.roll = 0;
    camera->srt.pitch = 0;
    camera->srt.yaw = -0x8000;
    camera->dpitch = 0;
    camera->srt.transl.x = 0.0f;
    camera->srt.transl.y = 0.0f;
    camera->srt.transl.z = 0.0f;

    func_800021A0(gdl, rspMtxs);

    camera->dpitch = dpitch;
    camera->srt.yaw = yaw;
    camera->srt.pitch = pitch;
    camera->srt.roll = roll;
    camera->srt.transl.x = posX;
    camera->srt.transl.y = posY;
    camera->srt.transl.z = posZ;
}

f32 func_80001884(f32 x, f32 y, f32 z)
{
    s32 cameraSel;
    f32 dz;
    f32 dx;
    f32 dy;

    cameraSel = gCameraSelector;

    if (gUseAlternateCamera) {
        cameraSel += 4;
    }

    dz = (z - gCameras[cameraSel].srt.transl.z);\
    dy = (x - gCameras[cameraSel].srt.transl.x);\
    dx = (y - gCameras[cameraSel].srt.transl.y);
    
    return sqrtf((dz * dz) + ((dy * dy) + (dx * dx)));
}

// camera_reset
void func_80001914(s32 tx, s32 ty, s32 tz, s32 roll, s32 pitch, s32 yaw)
{
    gCameras[gCameraSelector].srt.transl.x = tx;
    gCameras[gCameraSelector].srt.transl.y = ty;
    gCameras[gCameraSelector].srt.transl.z = tz;
    gCameras[gCameraSelector].unk_0x18 = 60.0f;
    gCameras[gCameraSelector].srt.roll = roll * 0xb6;
    gCameras[gCameraSelector].srt.pitch = pitch * 0xb6;
    gCameras[gCameraSelector].srt.yaw = yaw * 0xb6;
    gCameras[gCameraSelector].unk_0x20 = 0.0f;
    gCameras[gCameraSelector].unk_0x24 = 0.0f;
    gCameras[gCameraSelector].unk_0x28 = 0.0f;
    gCameras[gCameraSelector].dty = 0.0f;
    gCameras[gCameraSelector].object = NULL;
    gCameras[gCameraSelector].dpitch = 0;
}

void func_800019BC(s32 selector, f32 x, f32 y, f32 z, s16 yaw, s16 pitch, s16 roll)
{
    selector += 4;

    gCameras[selector].dpitch = 0;
    gCameras[selector].srt.transl.x = x;
    gCameras[selector].srt.transl.y = y;
    gCameras[selector].srt.transl.z = z;
    gCameras[selector].srt.yaw = yaw;
    gCameras[selector].srt.pitch = pitch;
    gCameras[selector].srt.roll = roll;

    if (selector < 8) {
        gTriggerUseAlternateCamera = TRUE;
    }
}

s8 func_80001A2C()
{
    return gUseAlternateCamera;
}

void func_80001A3C()
{
    gUseAlternateCamera = gTriggerUseAlternateCamera;
    gTriggerUseAlternateCamera = 0;
}

// set_active_viewports_and_max?
s32 func_80001A5C(s32 num) {
    if (num >= 0 && num < 4) {
        UINT_800a66f8 = num;
    } else {
        UINT_800a66f8 = 0;
    }

    switch (UINT_800a66f8) {
        case 0:
            D_800A6700 = 1;
            break;
        case 1:
            D_800A6700 = 2;
            break;
        case 2:
            D_800A6700 = 3;
            break;
        case 3:
            D_800A6700 = 4;
            break;
    }

    if (D_800A6700 <= gCameraSelector) {
        gCameraSelector = 0;
    }

    return D_800A6700;
}

void set_camera_selector(s32 selector)
{
    if (selector >= 0 && selector < 4) {
        gCameraSelector = selector;
    } else {
        gCameraSelector = 0;
    }
}

void func_80001B40() {
    s32 width;
    s32 height;
    s32 port;
    s32 yPos;
    s32 xPos;
    s32 i;
    
    gCameraGroupSelector = 1 - gCameraGroupSelector;

    for (i = 0; i < 4; i++) {
        if (gViewports[i].flags & 0x4) {
            gViewports[i].flags &= ~1;
        } else if (gViewports[i].flags & 0x2) {
            gViewports[i].flags |= 1;
        }

        gViewports[i].flags &= ~(2 | 4);

        if (gViewports[i].flags & 1) {
            if (!(gViewports[i].flags & 8)) {
                xPos = (((gViewports[i].x2 - gViewports[i].x1) + 1) << 1) + (gViewports[i].x1 * 4);
            } else {
                xPos = gViewports[i].posX;
                xPos *= 4;
            }

            if (!(gViewports[i].flags & 16)) {
                yPos = (((gViewports[i].y2 - gViewports[i].y1) + 1) << 1) + (gViewports[i].y1 * 4);
            } else {
                yPos = gViewports[i].posY;
                yPos *= 4;
            }

            if (!(gViewports[i].flags & 32)) {
                width = gViewports[i].x2 - gViewports[i].x1;
                width += 1;
                width *= 2;
            } else {
                width = gViewports[i].width;
                width *= 2;
            }

            if (!(gViewports[i].flags & 64)) {
                height = gViewports[i].y2 - gViewports[i].y1;
                height += 1;
                height *= 2;
            } else {
                height = gViewports[i].height;
                height *= 2;
            }

            port = i + (gCameraGroupSelector * 5) + 10;

            gRSPViewports[port].vp.vtrans[0] = xPos;
            gRSPViewports[port].vp.vtrans[1] = yPos;
            gRSPViewports[port].vp.vscale[0] = width;
            gRSPViewports[port].vp.vscale[1] = height;
        }
    }
}

void func_80001CE0(s32 selector, u32 param_2)
{
    if (param_2 != 0) {
        gViewports[selector].flags |= 0x1;
    } else {
        gViewports[selector].flags |= 0x2;
    }
    gViewports[selector].flags &= ~0x4;
}

void func_80001D58(s32 selector, u32 param_2)
{
    if (param_2 != 0) {
        gViewports[selector].flags &= ~0x1;
    } else {
        gViewports[selector].flags |= 0x4;
    }
    gViewports[selector].flags &= ~0x2;
}

u32 func_80001DD4(s32 selector)
{
    return gViewports[selector].flags & 0x1;
}

void func_80001E04(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2) {
    s32 resolution;
    s32 width;
    s32 height;
    s32 temp;

    resolution = get_some_resolution_encoded();
    height = RESOLUTION_HEIGHT(resolution) & 0xFFFF;
    width = RESOLUTION_WIDTH(resolution);

    if (x2 < x1) {
        temp = x1;
        x1 = x2;
        x2 = temp;
    }

    if (y2 < y1) {
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    if (x1 >= width || x2 < 0 || y1 >= height || y2 < 0) {
        gViewports[viewPortIndex].ulx = 0;
        gViewports[viewPortIndex].uly = 0;
        gViewports[viewPortIndex].lrx = 0;
        gViewports[viewPortIndex].lry = 0;
    } else {
        if (x1 < 0) {
            gViewports[viewPortIndex].ulx = 0;
        } else {
            gViewports[viewPortIndex].ulx = x1;
        }

        if (y1 < 0) {
            gViewports[viewPortIndex].uly = 0;
        } else {
            gViewports[viewPortIndex].uly = y1;
        }

        if (x2 >= width) {
            gViewports[viewPortIndex].lrx = width - 1;
        } else {
            gViewports[viewPortIndex].lrx = x2;
        }

        if (y2 >= height) {
            gViewports[viewPortIndex].lry = height - 1;
        } else {
            gViewports[viewPortIndex].lry = y2;
        }
    }

    gViewports[viewPortIndex].x1 = x1;
    gViewports[viewPortIndex].x2 = x2;
    gViewports[viewPortIndex].y1 = y1;
    gViewports[viewPortIndex].y2 = y2;
}

void func_80001F70(s32 viewPortIndex, s32 posX, s32 posY, s32 width, s32 height) {
    if (posX != 0x8000) {
        gViewports[viewPortIndex].posX = posX;
        gViewports[viewPortIndex].flags |= 8;
    } else {
        gViewports[viewPortIndex].flags &= ~8;
    }

    if (posY != 0x8000) {
        //!@bug Viewport Y writes to the X value. Luckily, this function is unused.
        gViewports[viewPortIndex].posX = posY;
        gViewports[viewPortIndex].flags |= 16;
    } else {
        gViewports[viewPortIndex].flags &= ~16;
    }

    if (width != 0x8000) {
        gViewports[viewPortIndex].width = width;
        gViewports[viewPortIndex].flags |= 32;
    } else {
        gViewports[viewPortIndex].flags &= ~32;
    }

    if (height != 0x8000) {
        gViewports[viewPortIndex].height = height;
        gViewports[viewPortIndex].flags |= 64;
    } else {
        gViewports[viewPortIndex].flags &= ~64;
    }
}

u32 func_8000206C(s32 selector, s32 *ulx, s32 *uly, s32 *lrx, s32 *lry)
{
    *ulx = gViewports[selector].ulx;
    *lrx = gViewports[selector].lrx;
    *uly = gViewports[selector].uly;
    *lry = gViewports[selector].lry;

    if ((*ulx | *lrx | *uly | *lry) == 0) {
        return 0;
    }

    return 1;
}

void func_800020E4(s32 selector, s32 *x1, s32 *y1, s32 *x2, s32 *y2) {
    *x1 = gViewports[selector].x1;
    *y1 = gViewports[selector].y1;
    *x2 = gViewports[selector].x2;
    *y2 = gViewports[selector].y2;
}

void func_80002130(s32 *ulx, s32 *uly, s32 *lrx, s32 *lry)
{
    u32 wh = get_some_resolution_encoded();
    u32 width = wh & 0xffff;
    u32 height = wh >> 16;

    *ulx = 0;
    *lrx = width;
    *uly = SHORT_8008c524 + 6;
    *lry = height - SHORT_8008c524 - 6;
}

#ifdef NON_EQUIVALENT
void func_80002C0C(Gfx **gdl, s32 scaleX, s32 scaleY, s32 transX, s32 transY);
void func_800021A0(Gfx **gdl, Mtx **rspMtxs)
{
    s32 cameraSelPre;
    u32 wh;
    s32 cameraSelPost;
    u32 width;
    u32 height;
    s32 scaleX;
    s32 scaleY;
    s32 transX;
    s32 transY;
    u32 mode;

    cameraSelPre = gCameraSelector;
    wh = get_some_resolution_encoded();
    cameraSelPost = gCameraSelector;
    width = wh & 0xffff;
    height = wh >> 16;

    if (gViewports[cameraSelPre].flags & 0x1)
    {
        gCameraSelector = cameraSelPre;
        gDPSetScissor((*gdl)++, 0, gViewports[gCameraSelector].ulx, gViewports[gCameraSelector].uly, gViewports[gCameraSelector].lrx, gViewports[gCameraSelector].lry);
        func_80002C0C(gdl, 0, 0, 0, 0);
        if (rspMtxs != NULL) {
            gCameraSelector = cameraSelPost;
            setup_rsp_camera_matrices(gdl, rspMtxs);
        }
        gCameraSelector = cameraSelPost;
        return;
    }

    mode = UINT_800a66f8;
    if (mode == 2) {
        mode = 3;
    }

    scaleY = height / 2;
    if (osTvType == OS_TV_PAL) {
        scaleY = 145;
    }

    switch (mode)
    {
    case 0:
        transX = scaleX;
        transY = scaleY;
        if (osTvType == OS_TV_PAL) {
            transY = scaleY - 18;
        }
        break;
    case 1:
        if (gCameraSelector == 0) {
            transY = height / 4;
            transX = scaleX;
            if (osTvType == OS_TV_PAL) {
                transY -= 12;
            }
        } else {
            transY = height / 2 + height / 4;
            transX = scaleX;
        }
        break;
    case 2:
        transX = scaleX + width / 4;
        transY = scaleY;
        if (gCameraSelector == 0) {
            transX = width / 4;
        }
        break;
    case 3:
        scaleX = width / 4;
        transX = scaleX;
        scaleY = scaleY / 2;
        transY = height / 2;
        if (osTvType == OS_TV_PAL) {
            transY = scaleY - 6;
            if (gCameraSelector < 2) {
                transY = scaleY - 20;
            }
        }
        break;
    }

    if (osTvType == OS_TV_PAL) {
        transX -= 4;
    }

    func_80002C0C(gdl, scaleX, scaleY, transX, transY);
    if (rspMtxs != NULL) {
        setup_rsp_camera_matrices(gdl, rspMtxs);
    }
    func_80002490(gdl);

    gCameraSelector = cameraSelPre;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_800021A0.s")
#endif

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80002490.s")
#else
extern u32 UINT_800a66f8;
extern s16 SHORT_8008c524;
void _func_80002490(Gfx **gdl)
{
    s32 ulx, uly, lrx, lry;
    s32 wh = get_some_resolution_encoded();
    s32 width = wh & 0xffff;
    s32 height = wh >> 16;

    if (UINT_800a66f8 != 0)
    {
        s32 centerX;
        s32 centerY;
        s32 padX;
        s32 padY;

        u32 mode = UINT_800a66f8;
        if (mode == 2) {
            mode = 3;
        }

        ulx = 0;
        uly = 0;
        lrx = width;
        lry = height;
        centerX = width >> 1;
        centerY = height >> 1;
        padX = width >> 8;
        padY = height >> 7;

        switch (mode)
        {
        case 1:
            lry -= padY;
            if (gCameraSelector == 0) {
                lry = centerY - padY;
            } else {
                uly = centerY + padY;
            }
            break;
        case 2:
            lrx -= padX;
            if (gCameraSelector == 0) {
                lrx = centerX - padX;
            } else {
                lrx = centerX + padX;
            }
            break;
        case 3:
            switch (gCameraSelector)
            {
            case 0:
                lry = centerY - padY;
                lrx = centerX - padX;
                break;
            case 1:
                ulx = centerX + padX;
                lrx -= padX;
                lry = centerY - padY;
                break;
            case 2:
                uly = centerY + padY;
                lrx = centerX - padX;
                lry -= padY;
                break;
            case 3:
                uly = centerY + padY;
                ulx = centerX + padX;
                lry -= padY;
                lrx -= padX;
                break;
            }
            break;
        }
    }
    else
    {
        ulx = 0;
        lrx = width;
        lry = height - SHORT_8008c524 - 6;
        uly = SHORT_8008c524 + 6;
    }

    gDPSetScissor((*gdl)++, 0, ulx, uly, lrx, lry);
}
#endif

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/setup_rsp_camera_matrices.s")
#else
extern u32 UINT_ARRAY_800a7bb0[28];
extern f32 FLOAT_80098388;
extern f32 FLOAT_8009838c;
void func_80046B58(f32 x, f32 y, f32 z);
void _setup_rsp_camera_matrices(Gfx **gdl, Mtx **rspMtxs)
{
    s32 cameraSel;
    Camera *camera;
    Vec3f v;
    s32 i;

    cameraSel = gCameraSelector;

    gSPPerspNormalize((*gdl)++, gPerspNorm);

    if (gUseAlternateCamera) {
        gCameraSelector += 4;
        cameraSel = gCameraSelector;
    }
    camera = &gCameras[cameraSel];

    update_camera_for_object(camera);

    if (gCameraSelector == 4) {
        func_80046B58(camera->tx, camera->ty, camera->tz);
    }

    v.x = camera->tx - gWorldX;
    v.y = camera->ty;
    v.z = camera->tz - gWorldZ;

    if (v.x > FLOAT_80098388 /*32767.0f */ || FLOAT_8009838c /* -32767.0f */ > v.x || v.z > FLOAT_80098388 /* 32767.0f */ || FLOAT_8009838c > v.z /* -32767.0f */) {
        return;
    }
    
    gCameraSRT.yaw = camera->yaw - 0x8000;
    gCameraSRT.pitch = camera->pitch + camera->dpitch;
    gCameraSRT.roll = camera->roll;
    gCameraSRT.transl.x = -v.x;
    gCameraSRT.transl.y = -v.y;
    gCameraSRT.transl.z = -v.z;
    if (UINT_800a6a54 != 0) {
        gCameraSRT.transl.y -= camera->dty;
    }

    matrix_from_srt_reversed(&gViewMtx, &gCameraSRT);
    matrix_concat(&gViewMtx, &gProjectionMtx, &gViewProjMtx);
    matrix_f2l(&gViewProjMtx, *rspMtxs);

    gRSPMtxList = *rspMtxs;

    gSPMatrix((*gdl)++, OS_K0_TO_PHYSICAL((*rspMtxs)++), G_MTX_PROJECTION | G_MTX_LOAD);

    gCameraSRT.yaw = -0x8000 - camera->yaw;
    gCameraSRT.pitch = -(camera->pitch + camera->dpitch);
    gCameraSRT.roll = -camera->roll;
    gCameraSRT.scale = 1.0f;
    gCameraSRT.transl.y = v.y;
    if (UINT_800a6a54 != 0) {
        gCameraSRT.transl.y += camera->dty;
    }
    gCameraSRT.transl.x = v.x;
    gCameraSRT.transl.z = v.z;
    matrix_from_srt(&gViewMtx2, &gCameraSRT);
    matrix_f2l(&gViewMtx2, &gRSPViewMtx2);

    gRSPMatrices[0] = NULL;
    gRSPMatrices[1] = NULL;

    for (i = 0; i < 28; i++) {
        UINT_ARRAY_800a7bb0[i] = 0;
    }
}
#endif

void func_800029C4(f32 param1) {
    D_8008C788.m[1][1] = param1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_800029D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80002B2C.s")

void func_80002C0C(Gfx **gdl, s32 scaleX, s32 scaleY, s32 transX, s32 transY)
{
    if (0) {} // fakematch

    if (!(gViewports[gCameraSelector].flags & 0x1))
    {
        gRSPViewports[gCameraSelector].vp.vtrans[0] = transX << 2;
        gRSPViewports[gCameraSelector].vp.vtrans[1] = transY << 2;
        gRSPViewports[gCameraSelector].vp.vscale[0] = scaleX << 2;
        gRSPViewports[gCameraSelector].vp.vscale[1] = scaleY << 2;
        gSPViewport((*gdl)++, OS_K0_TO_PHYSICAL(&gRSPViewports[gCameraSelector]));
    }
    else
    {
        gSPViewport((*gdl)++, OS_K0_TO_PHYSICAL(&gRSPViewports[gCameraSelector + 5 * gCameraGroupSelector + 10]));
    }
}

void func_80002D14(f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz)
{
    f32 nrm = x * gViewProjMtx.m[0][3] + y * gViewProjMtx.m[1][3] + z * gViewProjMtx.m[2][3] + gViewProjMtx.m[3][3];
    vec3_transform(&gViewProjMtx, x, y, z, ox, oy, oz);
    if (nrm != 0.0f)
    {
        nrm = 1.0f / nrm;
        *ox *= nrm;
        *oy *= nrm;
        *oz *= nrm;
    }
}

void func_80002DE4(f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz)
{
    f32 dot = x * gViewProjMtx.m[0][3] + y * gViewProjMtx.m[1][3] + z * gViewProjMtx.m[2][3] + gViewProjMtx.m[3][3];
    if (dot != 0.0f)
    {
        x *= dot;
        y *= dot;
        z *= dot;
    }
    vec3_transform(&gViewMtx2, x, y, z, ox, oy, oz);
}

void func_80002E94(f32 x, f32 y, f32 z, s32 *ox, s32 *oy, s32 *oz)
{
    if (ox != NULL) {
        x *= (gRSPViewports[0].vp.vscale[0] >> 2);
        x += (gRSPViewports[0].vp.vtrans[0] >> 2);
        *ox = x;
    }
    if (oy != NULL) {
        y *= (gRSPViewports[0].vp.vscale[1] >> 2);
        y += (gRSPViewports[0].vp.vtrans[1] >> 2);
        *oy = 240 - (s32)(y);
    }
    if (oz != NULL) {
        z *= (gRSPViewports[0].vp.vscale[2] << 5);
        z += (gRSPViewports[0].vp.vtrans[2] << 5);
        *oz = z;
    }
}

void func_80002F88(s32 x, s32 y, s32 z, f32 *ox, f32 *oy, f32 *oz)
{
    x -= (gRSPViewports[0].vp.vtrans[0] >> 2);
    *ox = (f32)(x) / (gRSPViewports[0].vp.vscale[0] >> 2);

    y = 240 - y;
    y -= (gRSPViewports[0].vp.vtrans[1] >> 2);
    *oy = (f32)(y) / (gRSPViewports[0].vp.vscale[1] >> 2);

    z -= (gRSPViewports[0].vp.vtrans[2] << 5);
    *oz = (f32)(z) / (gRSPViewports[0].vp.vscale[2] << 5);
}

void func_8000302C(Gfx **gdl)
{
    u32 wh;
    u32 width;
    u32 height;

    gCameraSelector = 4;

    wh = get_some_resolution_encoded();
    height = wh >> 16;
    width = wh & 0xffff;

    if (!(gViewports[gCameraSelector].flags & 0x1))
    {
        gDPSetScissor((*gdl)++, 0, 0, 0, width - 1, height - 1);
        func_80002C0C(gdl, width / 2, height / 2, width / 2, height / 2);
    }
    else
    {
        func_80002490(gdl);
        func_80002C0C(gdl, 0, 0, 0, 0);
    }

    gCameraSelector = 0;
}

extern MtxF MtxF_800a6a60;
void func_80003168(Gfx **gdl, Mtx **rspMtxs, s32 x, s32 y, s32 z, f32 scale)
{
    MtxF mf;

    matrix_translation(&MtxF_800a6a60, x * 640.0f, y, z * 640.0f);
    if (scale != 1.0f) {
        matrix_scaling(&mf, scale, scale, scale);
        matrix_concat(&mf, &MtxF_800a6a60, &MtxF_800a6a60);
    }
    matrix_f2l_4x3(&MtxF_800a6a60, *rspMtxs);

    gSPMatrix((*gdl)++, OS_K0_TO_PHYSICAL((*rspMtxs)++), G_MTX_LOAD);
}

u32 func_80003278(u32 a0, u32 a1, u32 a2, u32 a3)
{
    return 1;
}

void func_80003294(u32 a0, u32 a1, u32 a2, u32 a4)
{
}

void func_800032AC(u32 a0, u32 a1, u32 a2, u32 a4)
{
}

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_800032C4.s")

s32 func_8004454C(f32 x, f32 y, f32 z);
void func_800034CC(f32 x, f32 y, f32 z)
{
    gCameras[gCameraSelector].srt.transl.x += x;
    gCameras[gCameraSelector].srt.transl.y += y;
    gCameras[gCameraSelector].srt.transl.z += z;
    gCameras[gCameraSelector].unk_0x56 = func_8004454C(
        gCameras[gCameraSelector].srt.transl.x, 
        gCameras[gCameraSelector].srt.transl.y, 
        gCameras[gCameraSelector].srt.transl.z);
}

void func_8000356C(f32 a, f32 b, f32 c)
{
    gCameras[gCameraSelector].srt.transl.x -= a * fcos16_precise(gCameras[gCameraSelector].srt.yaw);
    gCameras[gCameraSelector].srt.transl.z -= a * fsin16_precise(gCameras[gCameraSelector].srt.yaw);
    gCameras[gCameraSelector].srt.transl.x -= c * fsin16_precise(gCameras[gCameraSelector].srt.yaw);
    gCameras[gCameraSelector].srt.transl.z += c * fcos16_precise(gCameras[gCameraSelector].srt.yaw);
    gCameras[gCameraSelector].unk_0x56 = func_8004454C(
        gCameras[gCameraSelector].srt.transl.x, 
        gCameras[gCameraSelector].srt.transl.y, 
        gCameras[gCameraSelector].srt.transl.z);
}

void get_vec3_to_camera_normalized(f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz)
{
    f32 nrm;
    Camera *camera = &gCameras[gCameraSelector];

    *ox = camera->srt.transl.x - x;
    *oy = camera->srt.transl.y - y;
    *oz = camera->srt.transl.z - z;

    nrm = sqrtf(*ox * *ox + *oy * *oy + *oz * *oz);
    if (nrm != 0.0f)
    {
        nrm = 1.0f / nrm;
        *ox *= nrm;
        *oy *= nrm;
        *oz *= nrm;
    }
}

// Unused
void rotate_camera(s32 yaw, s32 pitch, s32 roll)
{
    gCameras[gCameraSelector].srt.yaw += yaw;
    gCameras[gCameraSelector].srt.pitch += pitch;
    gCameras[gCameraSelector].srt.roll += roll;
}

Camera *get_main_camera()
{
    return &gCameras[gCameraSelector];
}

Camera *get_camera()
{
    if (gUseAlternateCamera) {
        return &gCameras[gCameraSelector + 4];
    }

    return &gCameras[gCameraSelector];
}

Camera *get_camera_array()
{
    if (gUseAlternateCamera) {
        return &gCameras[4];
    }

    return gCameras;
}

MtxF *func_8000388c()
{
    return &gViewMtx2;
}

MtxF *func_8000389c()
{
    return &gViewProjMtx;
}

MtxF *func_800038AC()
{
    return &gProjectionMtx;
}

Mtx *func_800038BC()
{
    return &gRSPProjectionMtx;
}

MtxF *func_800038CC()
{
    return &gViewMtx;
}

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_800038DC.s")
#else
u32 _func_800038DC(f32 x, f32 y, f32 z, f32 *ox, f32 *oy, u8 param_6)
{
    f32 vx;
    f32 vy;
    f32 vz;

    if (param_6) {
        vec3_transform(gViewMtx, x, y, z, &vx, &vy, &vz);
    }

    vx = gProjectionMtx.m[0][0] * vx;
    vy = gProjectionMtx.m[1][1] * vy;
    vz = -gProjectionMtx.m[2][3] * vz;

    if (vz < -2.0f)
    {
        Vp *rspvp;

        rspvp = &gRSPViewports[gCameraSelector];
        if (gViewports[gCameraSelector].flags & 0x1) {
            rspvp += gCameraGroupSelector * 5 + 10;
        }

        *ox = (rspvp->vp.vtrans[0] >> 2) - (vx * (rspvp->vp.vscale[0] >> 2)) / vz;
        *oy = (rspvp->vp.vtrans[1] >> 2) + (vy * (rspvp->vp.vscale[1] >> 2)) / vz;

        return 1;
    }

    return 0;
}
#endif

// get_distance_to_camera?
// https://github.com/DavidSM64/Diddy-Kong-Racing/blob/master/src/camera.c#L1564
#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80003A60.s")

void func_80003AA0(f32 x, f32 y, f32 z, f32 distance, f32 param_5)
{
    s32 i;

    for (i = 0; i < 8; i++)
    {
        f32 dx = x - gCameras[i].srt.transl.x;
        f32 dy = y - gCameras[i].srt.transl.y;
        f32 dz = z - gCameras[i].srt.transl.z;
        f32 d = sqrtf(dx * dx + dy * dy + dz * dz);
        if (d < distance) {
            gCameras[i].unk_0x5d = 0;
            gCameras[i].dty = (distance - d) * param_5 / distance;
        }
    }
}

void func_80003B70(f32 dty)
{
    s32 i;

    for (i = 0; i < CAMERA_COUNT; i++)
    {
        gCameras[i].dty = dty;
        gCameras[i].unk_0x5d = 0;
    }
}

void func_80003bb0(f32 param_1, f32 param_2, f32 param_3)
{
    s32 i;

    for (i = 0; i < CAMERA_COUNT; i++)
    {
        gCameras[i].dty = param_1;
        gCameras[i].unk_0x30 = param_1;
        gCameras[i].unk_0x34 = param_2;
        gCameras[i].unk_0x38 = 0.0f;
        gCameras[i].unk_0x3c = param_3;
        gCameras[i].unk_0x5d = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80003C48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80003C68.s")

void add_matrix_to_pool(MtxF *mf, s32 count)
{
    gMatrixPool[gMatrixCount].mtx = (Mtx_MtxF*)mf;
    gMatrixPool[gMatrixCount++].count = count;
}

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/tick_cameras.s")
#else
extern f32 gFarPlane;
f32 fexp(f32 x, u32 iterations);
void _tick_cameras()
{
    *(s16*)0x8008c524 = *(s16*)0x8008c528;
    if (*(s16*)0x8008c518 != 0)
    {
        *(s16*)0x8008c518 -= *(u8*)0x8008c950;
        if (*(s16*)0x8008c518 < 0) {
            *(s16*)0x8008c518 = 0;
        }

        gFarPlane = (*(f32*)0x800a6270 - *(f32*)0x800a6274) * ((f32)*(s16*)0x8008c518 / *(s16*)0x8008c51c) + *(f32*)0x800a6274;
    }

    gMatrixPool[gMatrixCount].count = -1;
    convert_mtxf_to_mtx_in_pool(gMatrixPool);
    gMatrixCount = 0;
    gMatrixIndex = 0;

    if (gUseAlternateCamera) {
        gCameraSelector += 4;
    }

    if (gCameras[gCameraSelector].unk_0x5d == 0)
    {
        gCameras[gCameraSelector].unk_0x5c--;
        while (gCameras[gCameraSelector].unk_0x5c < 0) {
            gCameras[gCameraSelector].unk_0x5c++;
            gCameras[gCameraSelector].dty = -gCameras[gCameraSelector].dty * *(f32*)0x80098398 /* 0.09f */;
        }
    }
    else
    {
        if (gCameras[gCameraSelector].unk_0x5d == 1)
        {
            f32 exp = fexp(-gCameras[gCameraSelector].unk_0x3c * gCameras[gCameraSelector].unk_0x38, 20);
            f32 c = fcos16_precise(gCameras[gCameraSelector].unk_0x34 * *(f32*)0x8009839c /* 65535.0f */ * gCameras[gCameraSelector].unk_0x38)
                    * gCameras[gCameraSelector].unk_0x30 * exp;
            gCameras[gCameraSelector].dty = c;
            if (c < *(f32*)0x800983a0 /* 0.1f */ && c > *(f32*)0x800983a4 /* -0.1f */) {
                gCameras[gCameraSelector].unk_0x5d = -1;
                gCameras[gCameraSelector].dty = 0.0f;
            }
            gCameras[gCameraSelector].unk_0x38 += *(f32*)0x8008c958 /* 1.0f */ / 60.0f;
        }
    }
}
#endif

// Computes e to the power of x
f32 fexp(f32 x, u32 iterations)
{
    f32 y = 1.0f;
    f32 n = 1.0f;
    f32 xp = x;
    f32 yp = 1.0f;

    for (; iterations != 0; iterations--)
    {
        y += xp / yp;
        n += 1.0f;
        xp *= x;
        yp *= n;
    }

    return y;
}

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/setup_rsp_matrices_for_object.s")
#else
extern Mtx *gRSPMatrices[2]; // TODO: how many matrices are there?
extern f32 gWorldX;
extern f32 gWorldZ;
extern MtxF MtxF_800a6a60;
void _setup_rsp_matrices_for_object(Gfx **gdl, Mtx **rspMtxs, Object *object)
{
    Object *link = object;
    MtxF mtxf;
    u8 isChild;
    f32 oldScale;

    if (gRSPMatrices[link->matrixIdx] == NULL)
    {
        isChild = FALSE;

        while (link != NULL)
        {
            if (link->parent == NULL) {
                link->srt.transl.x -= gWorldX;
                link->srt.transl.z -= gWorldZ;
            }

            oldScale = link->srt.scale;
            if (!(link->unk0xb0 & 0x8)) {
                link->srt.scale = 1.0f;
            }

            if (!isChild) {
                matrix_from_srt(&MtxF_800a6a60, &link->srt);
            } else {
                matrix_from_srt(&mtxf, &link->srt);
                matrix_concat_4x3(&MtxF_800a6a60, &mtxf, &MtxF_800a6a60);
            }

            link->srt.scale = oldScale;

            if (link->parent == NULL) {
                link->srt.transl.x += gWorldX;
                link->srt.transl.z += gWorldZ;
            }

            link = link->parent;
            isChild = TRUE;
        }

        matrix_concat(&MtxF_800a6a60, &gViewProjMtx, &gAuxMtx2);
        matrix_f2l(&gAuxMtx2, *rspMtxs);
        gRSPMatrices[object->matrixIdx] = *rspMtxs;
        (*rspMtxs)++;
    }

    gSPMatrix((*gdl)++, OS_K0_TO_PHYSICAL(gRSPMatrices[object->matrixIdx]), G_MTX_PROJECTION | G_MTX_LOAD);
}
#endif

void func_80004224(Gfx **gdl)
{
    gSPMatrix((*gdl)++, OS_K0_TO_PHYSICAL(gRSPMtxList), G_MTX_PROJECTION | G_MTX_LOAD);
}

// regalloc
#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_80004258.s")
#else
void func_800042C8(Object *object, s32 matrixIdx);
s32 _func_80004258(Object *object)
{
    func_800042C8(object, gMatrixIndex);
    gRSPMatrices[gMatrixIndex] = NULL;
    gMatrixIndex++;
    return gMatrixIndex - 1;
}
#endif

void func_800042A8(Object *object)
{
    func_800042C8(object, object->matrixIdx);
}

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/func_800042C8.s")
#else
extern MtxF gAuxMtx2;
void _func_800042C8(Object *object, int matrixIdx)
{
    u8 isChild = FALSE;
    f32 oldScale;
    Object* objectList[2]; // FIXME: really? only two?
    s32 objectCount = 0;
    s32 i;
    MtxF* pmtx;

    while (object != NULL)
    {
        objectList[objectCount++] = object;
        objectCount = (s8)objectCount;

        pmtx = &gObjectMatrices[matrixIdx];

        oldScale = object->srt.scale;
        object->srt.scale = 1.0f;

        if (!isChild) {
            matrix_from_srt(pmtx, &object->srt);
        } else {
            matrix_from_srt(&gAuxMtx2, &object->srt);
            matrix_concat(pmtx, &gAuxMtx2, pmtx);
        }

        object->srt.scale = oldScale;

        object = object->parent;

        isChild = TRUE;
    }

    while (objectCount > 0)
    {
        Object *pObj = objectList[(s8)--objectCount];
        SRT invsrt;

        invsrt.tx = -pObj->srt.tx;
        invsrt.ty = -pObj->srt.ty;
        invsrt.tz = -pObj->srt.tz;
        invsrt.scale = 1.0f;
        invsrt.yaw = -pObj->srt.yaw;
        invsrt.pitch = -pObj->srt.pitch;
        invsrt.roll = -pObj->srt.roll;
        matrix_from_srt_reversed(&gInverseObjectMatrices[matrixIdx], &invsrt);
    }
}
#endif

// regalloc
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/camera/get_object_child_position.s")
#else
void get_object_child_position(Object *object, float *ox, float *oy, float *oz)
{
    if (object->parent == NULL)
    {
        *ox = object->srt.transl.x;
        *oy = object->srt.transl.y;
        *oz = object->srt.transl.z;
    }
    else
    {
        vec3_transform(&gObjectMatrices[object->parent->matrixIdx],
            object->srt.transl.x, object->srt.transl.y, object->srt.transl.z, 
            ox, oy, oz);
    }
}
#endif

// regalloc
#ifndef NON_MATCHING
#pragma GLOBAL_ASM("asm/nonmatchings/camera/transform_point_by_object.s")
#else
void transform_point_by_object(float x, float y, float z, float *ox, float *oy, float *oz, Object *object)
{
    if (object != NULL)
    {
        vec3_transform(&gObjectMatrices[object->matrixIdx], x, y, z, ox, oy, oz);
    }
    else
    {
        *ox = x;
        *oy = y;
        *oz = z;
    }
}
#endif

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/inverse_transform_point_by_object.s")
#else
void _inverse_transform_point_by_object(float x, float y, float z, float *ox, float *oy, float *oz, Object *object)
{
    if (object != NULL)
    {
        vec3_transform(&gInverseObjectMatrices[object->matrixIdx], x, y, z, ox, oy, oz);
    }
    else
    {
        *ox = x;
        *oy = y;
        *oz = z;
    }
}
#endif

#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/inverse_rotate_point_by_object.s")
#else
void _inverse_rotate_point_by_object(float x, float y, float z, float *ox, float *oy, float * oz, Object *object)
{
    Vec3f v;

    v.x = x;
    v.y = y;
    v.z = z;
    vec3_transform_no_translate(&gInverseObjectMatrices[object->matrixIdx], &v, &v);
    *ox = v.x;
    *oy = v.y;
    *oz = v.y;
}
#endif

// regalloc
#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/rotate_point_by_object.s")
#else
void _rotate_point_by_object(float x, float y, float z, float *ox, float *oy, float *oz, Object *object)
{
    Vec3f v;

    v.x = x;
    v.y = y;
    v.z = z;
    vec3_transform_no_translate(&gObjectMatrices[object->matrixIdx], &v, &v);
    *ox = v.x;
    *oy = v.y;
    *oz = v.z;
}
#endif

// regalloc
#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/transform_srt_by_object.s")
#else
void _transform_srt_by_object(SRT *srt, SRT *out, Object *object)
{
    if (object == NULL)
    {
        out->tx = srt->tx;
        out->ty = srt->ty;
        out->tz = srt->tz;
        out->yaw = srt->yaw;
        out->pitch = srt->pitch;
        out->roll = srt->roll;
    }
    else
    {
        vec3_transform(&gObjectMatrices[object->matrixIdx], srt->tx, srt->ty, srt->tz, &out->tx, &out->ty, &out->tz);
        out->yaw = object->srt.yaw + srt->yaw;
        out->pitch = srt->pitch;
        out->roll = srt->roll;
    }
}
#endif

void func_800047C8(SRT *a, SRT *b, SRT *out)
{
    MtxF mf;
    SRT tempsrt;
    s32 yaw;

    tempsrt.transl.x = -b->transl.x;
    tempsrt.transl.y = -b->transl.y;
    tempsrt.transl.z = -b->transl.z;
    tempsrt.scale = 1.0f;
    tempsrt.yaw = -b->yaw;
    tempsrt.pitch = -b->pitch;
    tempsrt.roll = -b->roll;

    matrix_from_srt_reversed(&mf, &tempsrt);

    vec3_transform(&mf, a->transl.x, a->transl.y, a->transl.z, &out->transl.x, &out->transl.y, &out->transl.z);

    yaw = a->yaw - b->yaw;
    if (yaw > 0x8000) {
        yaw -= 0xffff;
    }
    if (yaw < -0x8000) {
        yaw += 0xffff;
    }

    out->yaw = yaw;
    out->pitch = a->pitch;
    out->roll = a->roll;
}

#pragma GLOBAL_ASM("asm/nonmatchings/camera/update_camera_for_object.s")

// regalloc
#if 1
#pragma GLOBAL_ASM("asm/nonmatchings/camera/transform_point_by_object_matrix.s")
#else
void _transform_point_by_object_matrix(Vec3f *v, Vec3f *ov, s8 matrixIdx)
{
    if (matrixIdx < 0)
    {
        ov->x = v->x;
        ov->y = v->y;
        ov->z = v->z;
    }
    else
    {
        vec3_transform(gObjectMatrices[matrixIdx], v->x, v->y, v->z, &ov->x, &ov->y, &ov->z);
    }
}
#endif

void func_80004A30(s16 param1) {
    FB_BGCOLOR = param1;
}

s16 func_80004A4C() {
    return FB_BGCOLOR;
}
