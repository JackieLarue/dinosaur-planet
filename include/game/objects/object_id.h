#ifndef _OBJECT_IDS_H
#define _OBJECT_IDS_H

/**
 * Object definition IDs.
 * 
 * Indexes into OBJINDEX.BIN
 * WARN: These names were extracted from OBJECTS.BIN but the names there are cutoff after
 *       15 characters. Not all of these names are 100% accurate and will need adjusting.
 */
enum ObjID {
    OBJ_Sabre = 0,
    OBJ_DFlog = 1,
    OBJ_SHboulder = 2,
    OBJ_EarthQuakSpell = 3,
    OBJ_checkpoint4 = 5,
    OBJ_Override = 6,
    OBJ_SphereTest = 7,
    OBJ_XYZAnimator = 8,
    OBJ_EnergyGem1 = 9,
    OBJ_Spellstone = 10,
    OBJ_meatPickup = 11,
    OBJ_setuppoint = 13,
    OBJ_animator = 14,
    OBJ_texscroll = 15,
    OBJ_ClubSharpClaw = 17,
    OBJ_generalscales = 18,
    OBJ_steggy = 19,
    OBJ_texscroll2 = 20,
    OBJ_InfoPoint = 21,
    OBJ_Nutter = 22,
    OBJ_NWtree = 23,
    OBJ_DFsequences = 24,
    OBJ_DFanimhightop = 25,
    OBJ_PadlockKey = 26,
    OBJ_Dynamite = 27,
    OBJ_fishingnetColle = 28,
    OBJ_fishingnet = 29,
    OBJ_AnimCamera = 30,
    OBJ_Krystal = 31,
    OBJ_fruitBranchMoss = 32,
    OBJ_fruitBranchSnow = 33,
    OBJ_BWLog = 34,
    OBJ_sword = 35,
    OBJ_Tricky = 36,
    OBJ_Kyte = 37,
    OBJ_DFdockpoint = 38,
    OBJ_PadLock = 39,
    OBJ_ExplodingWall = 40,
    OBJ_Cannon = 42,
    OBJ_CannonBall = 43,
    OBJ_N64logo = 44,
    OBJ_EnergyGem2 = 45,
    OBJ_Rarelogo = 47,
    OBJ_SHkillermushroo = 49,
    OBJ_club = 51,
    OBJ_WCSunStone = 52,
    OBJ_WCMoonStone = 53,
    OBJ_WCTemplePressur = 54,
    OBJ_EffectBox = 55,
    OBJ_Tentacle = 56,
    OBJ_SpaceShip = 58,
    OBJ_foodbagRedApple = 59,
    OBJ_WCApertureSymbo = 61,
    OBJ_rgbalight = 62,
    OBJ_sidesetup = 63,
    OBJ_EnergyGem3 = 64,
    OBJ_EnergyGem4 = 65,
    OBJ_WCSunTempleLase = 66,
    OBJ_WCAperture = 67,
    OBJ_StaticCamera = 68,
    OBJ_EWTrobotpatrol = 69,
    OBJ_WalkCamera = 70,
    OBJ_EnergyGem5 = 71,
    OBJ_EnergyGem6 = 72,
    OBJ_BoneDust = 73,
    OBJ_ProjectileSpell = 74,
    OBJ_TriggerPoint = 75,
    OBJ_TriggerPlane = 76,
    OBJ_TriggerArea = 77,
    OBJ_TriggerTime = 78,
    OBJ_TriggerButton = 79,
    OBJ_TriggerSetup = 80,
    OBJ_WCFloorTile = 81,
    OBJ_WCMoonInsideDoo = 82,
    OBJ_DigHole = 83,
    OBJ_TriggerBits = 84,
    OBJ_SandSnakes = 85,
    OBJ_NWboulder = 86,
    OBJ_NWgeyser = 87,
    OBJ_WarpPoint = 88,
    OBJ_WeaponUp = 89,
    OBJ_Duster = 90,
    OBJ_Mammoth = 91,
    OBJ_IceBerg1 = 92,
    OBJ_NWtreebridge = 93,
    OBJ_CFBigDoorSwitch = 95,
    OBJ_RestartPoint = 96,
    OBJ_SnowWormLarge = 99,
    OBJ_IceBall = 100,
    OBJ_NWmammothsquirt = 101,
    OBJ_InvHit = 102,
    OBJ_IMIcicle = 103,
    OBJ_Trex1 = 104,
    OBJ_staff = 105,
    OBJ_SHbluemushroom = 106,
    OBJ_CFColumnKnocker = 108,
    OBJ_CFbarrel = 109,
    OBJ_curve = 110,
    OBJ_GroundQuake = 111,
    OBJ_xyzpoint = 112,
    OBJ_WallTorch = 113,
    OBJ_IMSnowBike = 114,
    OBJ_SecretPoint = 115,
    OBJ_CFProjectileFra = 116,
    OBJ_sideload = 117,
    OBJ_fire = 118,
    OBJ_CFBlastedRoof = 119,
    OBJ_CampFire = 120,
    OBJ_DFriverflow = 123,
    OBJ_CFExplodeFloor = 124,
    OBJ_PineCone = 125,
    OBJ_SandEels = 126,
    OBJ_DummyObject = 128,
    OBJ_NWbigrock = 129,
    OBJ_CFForceField = 131,
    OBJ_CFForceFieldCon = 136,
    OBJ_CFGoldenPerch = 137,
    OBJ_FirePole = 138,
    OBJ_DFSH_Door1Speci = 139,
    OBJ_SB_Cloudrunner = 140,
    OBJ_Krazoa = 141,
    OBJ_SB_Galleon = 142,
    OBJ_DFmoondoor = 143,
    OBJ_DFpodium = 144,
    OBJ_DFpodiumswitch = 145,
    OBJ_DFdebris2 = 147,
    OBJ_DFbarrel = 148,
    OBJ_DFcradle = 149,
    OBJ_DFpulley = 150,
    OBJ_DFcavedoor = 151,
    OBJ_DFcavehatch1 = 152,
    OBJ_RobotPatrol = 153,
    OBJ_SB_Propeller = 154,
    OBJ_CFMainDoorA = 155,
    OBJ_CFMainDoorB = 156,
    OBJ_DFcavehatch2 = 157,
    OBJ_GuardPass = 158,
    OBJ_WCSunTempleMain = 159,
    OBJ_CF_ObjCreator = 160,
    OBJ_WCSunTempleSwit = 161,
    OBJ_WCTempleDial = 162,
    OBJ_DFropenode = 163,
    OBJ_WCTempleBridge = 164,
    OBJ_WCSunInsideDoor = 165,
    OBJ_DFbarrelcreator = 167,
    OBJ_RobotAnimPatro2 = 169,
    OBJ_DFbarrelanim = 170,
    OBJ_DFdebris1 = 171,
    OBJ_RobotBeam = 172,
    OBJ_DFturbine = 173,
    OBJ_DFturbinelever = 174,
    OBJ_FireFly = 175,
    OBJ_DFdebris3 = 176,
    OBJ_DFdebris3xxxx = 178,
    OBJ_CFDungeonBlock = 179,
    OBJ_RobotAnimPatrol = 180,
    OBJ_CFAnimBaby = 181,
    OBJ_CFMainSlideDoor = 183,
    OBJ_CloudPrisonCont = 184,
    OBJ_CFPrisonGuard = 185,
    OBJ_CFTreasWindLift = 186,
    OBJ_Beacon = 187,
    OBJ_KytesMum = 188,
    OBJ_CFseqobject = 189,
    OBJ_DIM2Crystal2 = 190,
    OBJ_AnimSharpy = 191,
    OBJ_CFPrisonKey = 192,
    OBJ_CFPrisonDoor = 193,
    OBJ_CFPrisonUncle = 194,
    OBJ_CFGuardian = 195,
    OBJ_CFCageDoor = 196,
    OBJ_CFWindLift = 197,
    OBJ_RobotLaserFire = 198,
    OBJ_CFWindSwitch = 199,
    OBJ_CFPowerDoor1 = 200,
    OBJ_CFPowerDoor2 = 201,
    OBJ_CFPowerDoor3 = 202,
    OBJ_CFPowerDoor4 = 203,
    OBJ_CFTreasureChest = 204, // name may be incorrect
    OBJ_CFCrate = 205,
    OBJ_CFScalesGalleon = 206,
    OBJ_CF_AnimSpaceCra = 207,
    OBJ_CF_GangPlank = 208,
    OBJ_DIM2Crystal = 209,
    OBJ_CloudShipContro = 210,
    OBJ_FireNut = 211,
    OBJ_FXEmit = 212,
    OBJ_CFSlideDoor1 = 213,
    OBJ_DIM2LavaControl = 214,
    OBJ_Krazcol = 215,
    OBJ_GuardClaw = 216,
    OBJ_CFPowerCrystal1 = 217,
    OBJ_CFPowerBase = 218,
    OBJ_CFPowerCrystal_Anim1 = 219, // name may be incorrect
    OBJ_CFMainCrystal = 220,
    OBJ_EnvEmitter = 221,
    OBJ_CFSeqRobotPatro = 222,
    OBJ_CFPowerCrystal2 = 223,
    OBJ_CFPowerCrystal3 = 224,
    OBJ_CFPowerCrystal_Anim2 = 225, // name may be incorrect
    OBJ_CFPowerCrystal_Anim3 = 226, // name may be incorrect
    OBJ_DIM2TrapDoorRig = 227,
    OBJ_CFCloudBaby = 228,
    OBJ_RobotBeam2 = 229,
    OBJ_CFTreasureDoor = 230,
    OBJ_CFTrPuzzleDoor = 231,
    OBJ_CFPuzzleSwitch = 232,
    OBJ_LaserBeam = 233,
    OBJ_CFColumn = 234,
    OBJ_CFledge = 235,
    OBJ_Transporter = 236,
    OBJ_AnimTest = 237,
    OBJ_IMSeqObject = 238,
    OBJ_IMIceMountain = 239,
    OBJ_IMFence = 241,
    OBJ_DIM2StonePillar = 242,
    OBJ_DIM2IceGrateDoo = 243,
    OBJ_TriggerCurve = 244,
    OBJ_FElevControl = 245,
    OBJ_FEseqobject = 246,
    OBJ_SB_ShipHead = 247,
    OBJ_SB_ShipMast = 248,
    OBJ_SB_ShipGun = 249,
    OBJ_DIM2Icicle = 250,
    OBJ_WM_ObjCreator = 251,
    OBJ_DIM2IceBlock = 264,
    OBJ_DIM2IceFloe1 = 265,
    OBJ_DIM2IceFloe2 = 269,
    OBJ_DIM2TrapDoorLef = 272,
    OBJ_DIM2IceFloe5 = 273,
    OBJ_SidekickBall = 274,
    OBJ_SB_CannonBall = 275,
    OBJ_SB_FireBall = 276,
    OBJ_NWalpineroot = 278,
    OBJ_NWmammothhelp = 279,
    OBJ_DIM2UseObject = 280,
    OBJ_SB_CloudBall = 281,
    OBJ_CFIllusionClaw = 285,
    OBJ_CFPowerRoomKey = 286,
    OBJ_CFPerch = 287,
    OBJ_SB_KyteCage = 288,
    OBJ_SB_CageKyte = 289,
    OBJ_SB_SeqDoor = 290,
    OBJ_CFPowerRoomKeyA = 291,
    OBJ_CFPrisonDoor2 = 292,
    OBJ_SB_Lamp = 293,
    OBJ_DIM2LiftSwitch = 294,
    OBJ_CFPrisonCage = 295,
    OBJ_CFCageSwitch = 296,
    OBJ_SB_SeqDoor2 = 297,
    OBJ_DIM2FlameHole = 298,
    OBJ_DIM2PuzzleDoor = 299,
    OBJ_DIM2PuzzleRock = 300,
    OBJ_DIM2PuzzleKey = 301,
    OBJ_DIM2PuzzleLift = 302,
    OBJ_SB_Debris = 303,
    OBJ_Area = 304,
    OBJ_DIM2PuzzlePad = 305,
    OBJ_DIM2ExplodeWall = 306,
    OBJ_ExplodeAnimator = 307,
    OBJ_Crate2 = 308,
    OBJ_DIM2GoldKey = 309,
    OBJ_DIM2CellLever = 310,
    OBJ_DIM2SilverKey = 311,
    OBJ_SB_MiniFire = 312,
    OBJ_WL_Galleon = 313,
    OBJ_SnowClaw = 314,
    OBJ_WLseqobject = 315,
    OBJ_DIM2CellLock = 316,
    OBJ_WL_deaddino = 317,
    OBJ_WL_Door1 = 318,
    OBJ_WL_Door2 = 319,
    OBJ_WL_Door3 = 320,
    OBJ_WL_Door4 = 321,
    OBJ_WL_LaserBeam = 322,
    OBJ_WL_PressureSwit = 324,
    OBJ_WL_Column = 325,
    OBJ_WL_Column_Top = 326,
    OBJ_NWmammothwalk = 327,
    OBJ_NWguardiandaugh = 328, // name may be incorrect
    OBJ_NWsfx = 329,
    OBJ_DigTunnel = 330,
    OBJ_projball = 331,
    OBJ_DIM2CellDoorLef = 332, // name may be incorrect
    OBJ_WL_LaserTarget = 333,
    OBJ_DIM2CellDoorRig = 334, // name may be incorrect
    OBJ_WL_spiritplace = 336,
    OBJ_WL_WarpDoor = 337,
    OBJ_DIMTruthHornPli = 338,
    OBJ_Crate = 339,
    OBJ_KrazoaText = 340,
    OBJ_DIM_BossGut = 341,
    OBJ_DIMTruthHorn = 342,
    OBJ_LevelName = 343,
    OBJ_SHqueenearthwal = 344,
    OBJ_SHthorntail = 345,
    OBJ_WM_Wizard = 346,
    OBJ_SHseqobject = 347,
    OBJ_WL_colrise = 349,
    OBJ_DIM2CellDoorRig_ = 350, // name may be incorrect
    OBJ_KrystalArms = 351,
    OBJ_WallAnimator = 352,
    OBJ_WL_podium = 353,
    OBJ_WL_podiumgem = 354,
    OBJ_WL_AnimPodiumge = 355,
    OBJ_AnimTricky = 356,
    OBJ_AnimSnowClaw = 357,
    OBJ_IMPrisonGate = 358,
    OBJ_DIM2CellDoorLef_ = 359, // name may be incorrect
    OBJ_IMAnimSpaceCraf = 360,
    OBJ_SHmushroomanim = 361,
    OBJ_IMMagicLight = 363,
    OBJ_IMSnowClawBike = 364,
    OBJ_IMSnowClaw = 365,
    OBJ_IMSnowClawBike2 = 367,
    OBJ_IMSnowClaw2 = 368,
    OBJ_SB_AnimCR = 369,
    OBJ_IMMagicLightHol = 370,
    OBJ_SB_DeckDoor3 = 371,
    OBJ_WL_Torch = 372,
    OBJ_WL_Vein = 375,
    OBJ_WL_WallTorch = 376,
    OBJ_WL_Worm = 377,
    OBJ_WL_Wallpower = 378,
    OBJ_EnergyPlant1 = 380,
    OBJ_EnergyPlant2 = 381,
    OBJ_WL_LevelControl = 382,
    OBJ_DIM2SeqObject = 383,
    OBJ_DIM2Conveyor = 384,
    OBJ_DIM2FlameBurst = 385,
    OBJ_DIM2MammothWhee = 386,
    OBJ_DIM2Mammoth = 387,
    OBJ_DIM2CellKey = 388,
    OBJ_DIM2SnowBall = 389,
    OBJ_DIM2PathGenerat = 390,
    OBJ_SB_ShipFlag = 391,
    OBJ_SB_ShipShadow = 392,
    OBJ_WM_GeneralScale = 393,
    OBJ_DIM2PrisonMammo = 394,
    OBJ_NWalpinerootani = 395,
    OBJ_DIMLavaBall = 397,
    OBJ_DIMLavaBallGene = 398,
    OBJ_DIMSnowHorn1 = 399,
    OBJ_DIMSnowHornShac = 400,
    OBJ_DIMLogFire = 401,
    OBJ_DIMSeqObject = 402,
    OBJ_SHvines = 404,
    OBJ_NWmammothguardi = 405,
    OBJ_DIMSnowBall = 406,
    OBJ_DIMSnowBallGene = 407,
    OBJ_SHspore = 408,
    OBJ_SHVineDoor = 409,
    OBJ_SHBirchTree = 410,
    OBJ_WaveAnimator = 411,
    OBJ_DFSH_Shrine = 412,
    OBJ_DFSH_Spirit = 413,
    OBJ_DFSH_ObjCreator = 414,
    OBJ_DFSH_SpiritGift = 416,
    OBJ_DFSH_Door1 = 418,
    OBJ_DFSH_Door2 = 419,
    OBJ_DFSH_Door3 = 420,
    OBJ_DFSH_Door4 = 421,
    OBJ_DIMShackleKey = 423,
    OBJ_FireSpell = 424,
    OBJ_DIMGate = 425,
    OBJ_DIMDismountPoin = 426,
    OBJ_DIMAlpineRoot = 427,
    OBJ_MMSH_Shrine = 428,
    OBJ_MMSH_Door1 = 429,
    OBJ_MMSH_Door2 = 430,
    OBJ_MMSH_Door3 = 431,
    OBJ_MMSH_Door4 = 432,
    OBJ_MMSH_Spirit = 433,
    OBJ_MMSH_Scales = 434,
    OBJ_AlphaAnimator = 435,
    OBJ_FlameThrowerSpe = 437,
    OBJ_FlameBall = 439,
    OBJ_scalessword = 440,
    OBJ_ECSH_Shrine = 441,
    OBJ_ECSH_Door1 = 443,
    OBJ_ECSH_Door2 = 444,
    OBJ_ECSH_Door3 = 445,
    OBJ_ECSH_Door4 = 446,
    OBJ_ECSH_Cup = 447,
    OBJ_NWminedoor = 450,
    OBJ_DIMFlag = 456,
    OBJ_DIMIceWall = 457,
    OBJ_GroundAnimator = 458,
    OBJ_DIMPushBlock = 459,
    OBJ_SHswapstone = 460,
    OBJ_NWguardiandaugh_ = 461, // name may be incorrect
    OBJ_DFSH_SpiritPriz = 462,
    OBJ_DIMLogFireRefle = 463,
    OBJ_DFSHcol = 464,
    OBJ_MMSHcol = 465,
    OBJ_ProjectileSwitc = 467,
    OBJ_DIMBoulder = 468,
    OBJ_DIMCannon = 469,
    OBJ_DIMCannonBall = 470,
    OBJ_ECSHcol = 471,
    OBJ_MMSH_SpiritPriz = 473,
    OBJ_SnowWormMed = 474,
    OBJ_NWtreebridge2 = 475,
    OBJ_DIMTorch = 476,
    OBJ_ECSH_SpiritPriz = 479,
    OBJ_ECSH_SpiritCup = 480,
    OBJ_DIMCannonCover1 = 481,
    OBJ_DIMCannonCover2 = 482,
    OBJ_DIMCannonCover3 = 483,
    OBJ_DIMCannonCover4 = 484,
    OBJ_GPSHcol = 486,
    OBJ_GPSH_Shrine = 487,
    OBJ_GPSH_SpiritPriz = 488,
    OBJ_GPSH_Spirit = 489,
    OBJ_GPSH_Door1 = 490,
    OBJ_GPSH_Door2 = 491,
    OBJ_GPSH_Door3 = 492,
    OBJ_GPSH_Door4 = 493,
    OBJ_DIMLavaSmash = 494,
    OBJ_GPSH_ObjCreator = 497,
    OBJ_GPSH_Scene = 499,
    OBJ_GPSHpickobjroot = 500,
    OBJ_GPSHpickobjnugg = 501,
    OBJ_GPSHpickobjegg = 502,
    OBJ_GPSHpickobjgem = 503,
    OBJ_GPSHpickobjbarr = 504,
    OBJ_GPSHpickobjplan = 505,
    OBJ_DIMLavaDebris = 506,
    OBJ_ECSH_Spirit = 507,
    OBJ_DIMCannonBase = 508,
    OBJ_BigCrate = 509,
    OBJ_LockIcon = 510,
    OBJ_SHthorntailanim = 511,
    OBJ_DIM_Boss = 512,
    OBJ_DBSHcol = 513,
    OBJ_DBSH_Shrine = 514,
    OBJ_DBSH_SpiritPriz = 515,
    OBJ_DBSH_Spirit = 516,
    OBJ_DBSH_Door1 = 517,
    OBJ_DBSH_Door2 = 518,
    OBJ_DBSH_Door3 = 519,
    OBJ_DBSH_Door4 = 520,
    OBJ_foodbagSmall = 522,
    OBJ_foodbagMedium = 523,
    OBJ_foodbagLarge = 524,
    OBJ_DBSH_Symbol = 525,
    OBJ_DBSH_Force = 526,
    OBJ_DBSH_Krystal = 527,
    OBJ_fruit = 528,
    OBJ_fruitBranch = 529,
    OBJ_foodbagGeneral = 530,
    OBJ_DIMBridgeCogAni = 531,
    OBJ_NWSH_col = 534,
    OBJ_NWSH_Shrine = 535,
    OBJ_NWSH_SpiritPriz = 536,
    OBJ_NWSH_Spirit = 537,
    OBJ_NWSH_Door1 = 538,
    OBJ_NWSH_Door2 = 539,
    OBJ_NWSH_Door3 = 540,
    OBJ_NWSH_Door4 = 541,
    OBJ_NWSH_colpush = 542,
    OBJ_DIMBridgeCog1 = 543,
    OBJ_DIMBridgeCogMai = 544,
    OBJ_NWSH_rock = 545,
    OBJ_NWSH_creator = 546,
    OBJ_DIMBridge = 547,
    OBJ_DIMBridgeCog2 = 548,
    OBJ_DIMBridgeCog3 = 549,
    OBJ_DIMBridgeCog4 = 550,
    OBJ_DIMBridgeCog5 = 551,
    OBJ_DIMLever = 552,
    OBJ_NWSH_Tricky = 553,
    OBJ_NWSH_Fire = 554,
    OBJ_DIMUseObject = 555,
    OBJ_CrackAnimator = 556,
    OBJ_WL_Column_lump = 557,
    OBJ_fish = 558,
    OBJ_SHriver = 559,
    OBJ_TriggerCylinder = 560,
    OBJ_NWSH_Sacrifice = 561,
    OBJ_CCSHcol = 562,
    OBJ_CCSH_Shrine = 563,
    OBJ_CCSH_Spirit = 564,
    OBJ_CCSH_SpiritPriz = 565,
    OBJ_CCSH_ObjCreator = 566,
    OBJ_CCSH_Door1 = 568,
    OBJ_CCSH_Door2 = 569,
    OBJ_CCSH_Door3 = 570,
    OBJ_WGSHcol = 571,
    OBJ_WGSH_Shrine = 572,
    OBJ_WGSH_Spirit = 573,
    OBJ_WGSH_SpiritPriz = 574,
    OBJ_WGSH_Door1 = 575,
    OBJ_WGSH_Door2 = 576,
    OBJ_WGSH_Door3 = 577,
    OBJ_WGSH_Door4 = 578,
    OBJ_WGSH_ObjCreator = 579,
    OBJ_CCSH_Door4 = 581,
    OBJ_DIMBridgeCogCol = 582,
    OBJ_ProjectileTarge = 583,
    OBJ_WGSH_flybaddie = 584,
    OBJ_DIMMetalDoor = 586,
    OBJ_DIMWoodDoor = 587,
    OBJ_DIM_BossGutSpik = 588,
    OBJ_DIM_BossTonsil = 589,
    OBJ_HitAnimator = 591,
    OBJ_DIMAlpineRootAn = 592,
    OBJ_WaterBaddie = 593,
    OBJ_DIMExplosion = 595,
    OBJ_DIMMagicBridge = 599,
    OBJ_WLFireFly = 601,
    OBJ_AnimKyte = 602,
    OBJ_EWTrobotpatrolB = 604,
    OBJ_WallCrawler = 605,
    OBJ_WL_seqpoint = 607,
    OBJ_WL_Crystal = 610,
    OBJ_LFXEmitter = 611,
    OBJ_WL_SpiritSet = 612,
    OBJ_WM_WarpPoint = 613,
    OBJ_WL_Planet = 616,
    OBJ_IllusionSpell = 617,
    OBJ_CFPrisonLock = 618,
    OBJ_WM_MoonSeedMoun = 625,
    OBJ_WM_PureMagic = 626,
    OBJ_WM_NoPassVine = 627,
    OBJ_WM_WallCrawler = 629,
    OBJ_WL_PlanetMoon = 630,
    OBJ_WL_VConsole = 631,
    OBJ_SC_sequences = 632,
    OBJ_SC_animbabyligh = 634,
    OBJ_SC_lightfoot = 635,
    OBJ_SC_babylightfoo = 636,
    OBJ_SC_animlightfoo = 637,
    OBJ_SC_warppoint = 638,
    OBJ_SC_golden_nugge = 639,
    OBJ_DF_Lantern = 640,
    OBJ_SCguardclaw = 641,
    OBJ_SC_levelcontrol = 642,
    OBJ_WM_AnimWizard = 643,
    OBJ_WL_Animcolrise = 644,
    OBJ_sfxPlayer = 645,
    OBJ_WM5pushcrate = 646,
    OBJ_WMconsolestone = 647,
    OBJ_SC_mounddoor = 648,
    OBJ_SC_settelmentdo = 649,
    OBJ_SC_beacon = 650,
    OBJ_SC_animchieflig = 651,
    OBJ_WM_NoPassHorzVi = 652,
    OBJ_TumbleWeedBush1 = 653,
    OBJ_SC_statue = 655,
    OBJ_DIM_BossSpit = 656,
    OBJ_SC_chieflightfo = 658,
    OBJ_WM_Walkway1 = 659,
    OBJ_WM_Walkway2 = 660,
    OBJ_WM_Platform = 661,
    OBJ_MAGICMaker = 667,
    OBJ_CFBigTreasureCh = 668,
    OBJ_WM_MovePlatform = 670,
    OBJ_SabreArms = 671,
    OBJ_CFAttractor = 673,
    OBJ_CFTreasRobo = 674,
    OBJ_CFSupTreasureCh = 675,
    OBJ_CFMagicWall = 676,
    OBJ_CFExplodeTunnel = 677,
    OBJ_CFBlastedTunnel = 678,
    OBJ_CFTreasureChest_ = 680, // name may be incorrect
    OBJ_BossDrakor = 683,
    OBJ_DIM2Torch = 684,
    OBJ_CFLevelControl = 688,
    OBJ_CFAnimSnowBike = 690,
    OBJ_CFRemovalSharpy = 692,
    OBJ_CFChuckObj1 = 693,
    OBJ_CFChuckObj2 = 694,
    OBJ_WMlargerock = 695,
    OBJ_RopeBaddie = 697,
    OBJ_CFTearDrop = 698,
    OBJ_WMfallencol = 699,
    OBJ_WMrock = 700,
    OBJ_WMsun = 701,
    OBJ_CFseqobjectlev = 703,
    OBJ_MagicPlant = 704,
    OBJ_IMIcePillar = 705,
    OBJ_WMinroom = 706,
    OBJ_VFP_ObjCreator = 707,
    OBJ_MagicDustSmall = 708,
    OBJ_MMP_barrel = 709,
    OBJ_CFliftplat = 710,
    OBJ_DB_WaterGate = 711,
    OBJ_DB_RockFall = 712,
    OBJ_DB_RockFallgen = 713,
    OBJ_Chuka = 714,
    OBJ_ChukaChuck = 715,
    OBJ_MMP_seqobject = 716,
    OBJ_MagicDustMid = 717,
    OBJ_MagicDustLarge = 718,
    OBJ_MagicDustHuge = 719,
    OBJ_SabreBaddie = 720,
    OBJ_DBseqobject = 721,
    OBJ_DBsplashy = 722,
    OBJ_MMP_defenDoorL = 723,
    OBJ_MMP_defenDoorR = 724,
    OBJ_MMP_padlock = 725,
    OBJ_kyteFireFlys = 726,
    OBJ_curveFish = 727,
    OBJ_FlameObject = 728,
    OBJ_colourfullfish = 729,
    OBJ_beanPickup = 730,
    OBJ_foodbagGreenBea = 731,
    OBJ_treebean = 732,
    OBJ_RollingTrex = 733,
    OBJ_CCguardgiving = 734,
    OBJ_DB_egg = 735,
    OBJ_DBPointMum = 737,
    OBJ_WM_BossDrakor = 738,
    OBJ_CClogpush = 739,
    OBJ_CCseqobject = 740,
    OBJ_CCgolden_nugget = 741,
    OBJ_CCkrazoaTablet = 742,
    OBJ_CCLever = 743,
    OBJ_CCfirecrystalin = 744,
    OBJ_CClevcontrol = 745,
    OBJ_CCvines = 746,
    OBJ_CCfirecrystal = 747,
    OBJ_CCbeacon = 748,
    OBJ_CCKrazoaTabletP = 749,
    OBJ_SHtricky = 750,
    OBJ_CCkrazoabright = 751,
    OBJ_CCfloor = 752,
    OBJ_CCcage = 753,
    OBJ_IMMultiSeq = 754,
    OBJ_CClightfoot = 755,
    OBJ_CCspellpage = 756,
    OBJ_CCclawdoor = 757,
    OBJ_DBTrigger = 758,
    OBJ_DBSpike = 759,
    OBJ_EneryCoil = 760,
    OBJ_WMtesla = 761,
    OBJ_IMSpaceThruster = 763,
    OBJ_CannonClaw = 764,
    OBJ_DBPlaceHolder = 765,
    OBJ_DBFloodWater = 766,
    OBJ_VFP_LevelContro = 767,
    OBJ_DBlevelControl = 768,
    OBJ_IMSpaceRing = 769,
    OBJ_IMSpaceRingGen = 770,
    OBJ_DBFire = 771,
    OBJ_IMSpaceTractor = 772,
    OBJ_DBFireBall = 773,
    OBJ_SnowWormSmall = 774,
    OBJ_DBmap = 777,
    OBJ_IceBallSmall = 778,
    OBJ_MMP_telescope = 779,
    OBJ_DBMagicBridge = 780,
    OBJ_DBDiamond = 781,
    OBJ_DIMBikeDoor = 783,
    OBJ_BossDrakorGalax = 784,
    OBJ_AnimClub = 785,
    OBJ_DIM_LevelContro = 786,
    OBJ_foodbagNewMeat = 787,
    OBJ_foodbagNewFish = 788,
    OBJ_CCkrazoaRecepta = 789,
    OBJ_CCdockdoor1 = 790,
    OBJ_CCdockdoor2 = 791,
    OBJ_CCcageSupport = 792,
    OBJ_DIMAlpineRoot2 = 793,
    OBJ_DIMTruthHornPla = 794,
    OBJ_NWseqobject = 795,
    OBJ_TrickyWarp = 796,
    OBJ_CCCellKey = 797,
    OBJ_CCCellDoor = 798,
    OBJ_NWtricky = 799,
    OBJ_CCportcullis = 801,
    OBJ_CCkdoor1 = 802,
    OBJ_CCkdoor2 = 803,
    OBJ_CCkdoor3 = 804,
    OBJ_CCkdoor4 = 805,
    OBJ_CCkdoor5 = 806,
    OBJ_RollingMinedoor = 807,
    OBJ_RollingStatueAn = 808,
    OBJ_Bronto = 809,
    OBJ_RD_seqobj = 810,
    OBJ_DBExpWall = 813,
    OBJ_DBExpbit = 815,
    OBJ_DBwhitehole = 817,
    OBJ_CF_MovDeckDoor = 818,
    OBJ_DIMTent = 819,
    OBJ_DIMBigTent = 820,
    OBJ_DBwaterhole = 821,
    OBJ_Lunaimar = 823,
    OBJ_DIMWoodDoor2 = 824,
    OBJ_DBbignest = 825,
    OBJ_SC_totembond = 827,
    OBJ_DBwaterplant = 828,
    OBJ_WM_Spellbook = 829,
    OBJ_WMKrazoa1 = 830,
    OBJ_WMKrazoa2 = 831,
    OBJ_WMthorntailanim = 832, // name may be incorrect
    OBJ_WMthorntailanim_ = 833, // name may be incorrect
    OBJ_DBwaterspray = 835,
    OBJ_WMBossDrakorhea = 836,
    OBJ_DBWaterCurve = 837,
    OBJ_DBplatform = 839,
    OBJ_DBAnimDiamond = 840,
    OBJ_DBlgtbeam = 841,
    OBJ_DIMBossIceSmash = 842,
    OBJ_DBbridgeanim = 843,
    OBJ_DBshooterball = 844,
    OBJ_DBbullet = 845,
    OBJ_DBNatShield = 847,
    OBJ_DBKillBot = 848,
    OBJ_DBSupShield = 849,
    OBJ_DBDustGeezer = 850,
    OBJ_DBbonedust = 851,
    OBJ_AreaFXEmit = 852,
    OBJ_DBkillboulder = 853,
    OBJ_DB_WaterGaterig = 854,
    OBJ_SandGrabber = 856,
    OBJ_DBScaleTile = 857,
    OBJ_DB_AnimEgg = 858,
    OBJ_DBEggBroke1 = 859,
    OBJ_DBEggBroke2 = 860,
    OBJ_TAreaFXEmit = 862,
    OBJ_SHwaterlily = 863,
    OBJ_SC_lightfootSpe = 864,
    OBJ_AnimSpell = 865,
    OBJ_CFAnimPowerRoom = 867,
    OBJ_BossDrakorNebul = 868, // name may be incorrect
    OBJ_Swoop = 869,
    OBJ_BossDrakorLevel = 870,
    OBJ_SHroot = 871,
    OBJ_DoorOpen = 872,
    OBJ_BassaltWeavel = 873,
    OBJ_CF_WallTorch = 874,
    OBJ_DFSH_LaserBeam = 875,
    OBJ_CFExplodePieces = 876,
    OBJ_SHrocketmushroo = 877,
    OBJ_SHmushroombit = 878,
    OBJ_DBSH_Torch = 879,
    OBJ_BossDrakorNebul_ = 880, // name may be incorrect
    OBJ_Caictua = 881,
    OBJ_Caictua_Thorn = 882,
    OBJ_GPSharpClaw = 883,
    OBJ_GPSeqObject = 884,
    OBJ_GP_LevelControl = 885,
    OBJ_BossDrakorDiamo = 886,
    OBJ_WaterFallSpray = 887,
    OBJ_DFlevelcontrol = 888,
    OBJ_WL_PlanDoor1 = 890,
    OBJ_WL_PlanDoor2 = 891,
    OBJ_WL_PlanDoor3 = 892,
    OBJ_WL_PlanDoor4 = 893,
    OBJ_DFdebris1piece = 894,
    OBJ_SHredflower = 895,
    OBJ_BossDrakorQuake = 897,
    OBJ_SHblueflower = 898,
    OBJ_FlameWall = 899,
    OBJ_PerchObject = 900,
    OBJ_FindKyteObject = 902,
    OBJ_DFdebris3piece = 903,
    OBJ_CRSnowClaw = 905,
    OBJ_CRSnowClaw2 = 906,
    OBJ_CRCloudRace = 907,
    OBJ_CRSnowBike = 908,
    OBJ_CRSnowClawBike = 909,
    OBJ_CRSnowClawBike2 = 910,
    OBJ_SC_totempole = 911,
    OBJ_CRSpellstone = 912,
    OBJ_DIMMagicLight = 913,
    OBJ_AnimSpellstone = 914,
    OBJ_SC_BirchTree = 915,
    OBJ_CFWaterDoor = 916,
    OBJ_DFmole = 917,
    OBJ_AnimQueenEarthW = 919,
    OBJ_RD_smallpalm = 920,
    OBJ_RD_mediumpalm = 921,
    OBJ_RD_palmleaf = 922,
    OBJ_SC_totblocks = 923,
    OBJ_SC_totemstrengt = 924,
    OBJ_Tumbleweed1 = 925,
    OBJ_KyteCurveCreate = 926,
    OBJ_VFP_MiniFire = 928,
    OBJ_DFSH_Door2Speci = 929,
    OBJ_DFSH_Door3Speci = 930,
    OBJ_DFSH_Door4Speci = 931,
    OBJ_SC_Lantern = 932,
    OBJ_CFExplodeTunnPi = 933,
    OBJ_VFP_statuea = 934,
    OBJ_VFP_Maindoor = 935,
    OBJ_VFP_Door2 = 936,
    OBJ_VFP_statueball = 937,
    OBJ_VFP_Maindoor2 = 938,
    OBJ_VFP_Door2B = 939,
    OBJ_VFP_Doorlock = 940,
    OBJ_VFP_statue = 941,
    OBJ_VFP_statueb = 942,
    OBJ_BigScorpionRobo = 943,
    OBJ_VFP_Ladders = 944,
    OBJ_DR_Platform = 945,
    OBJ_DR_AnimEarthWar = 946,
    OBJ_DR_Lever = 947,
    OBJ_DR_LiftLever = 948,
    OBJ_DR_FootClamp = 949,
    OBJ_DR_Seqobj = 950,
    OBJ_VFPLift1 = 951,
    OBJ_VFP_LiftSwitch = 952,
    OBJ_VFP_Block1 = 953,
    OBJ_VFP_Platform1 = 954,
    OBJ_VFP_RoundDoor = 955,
    OBJ_VFP_DoorSwitch = 956,
    OBJ_VFP_seqpoint = 957,
    OBJ_VFP_Spellstone = 958,
    OBJ_VFPLift2 = 959,
    OBJ_VFPLavaBlock = 960,
    OBJ_SC_totempuzzle = 961,
    OBJ_VFPDragHead = 962,
    OBJ_VFPDragBreath = 965,
    OBJ_VFP_SmallRoundD = 966,
    OBJ_VFP_stepstone = 967,
    OBJ_VFP_coreplat = 968,
    OBJ_RobottrackBeam = 969,
    OBJ_SC_MusicTree = 970,
    OBJ_VFP_coreplathol = 971,
    OBJ_DFwhirlpool = 972,
    OBJ_applePickup = 973,
    OBJ_DIMAnimSpellsto = 974,
    OBJ_SmallBasket = 975,
    OBJ_DIMafterbossrub = 976,
    OBJ_Green_scarab = 979,
    OBJ_Red_scarab = 980,
    OBJ_Gold_scarab = 981,
    OBJ_Rain_scarab = 982,
    OBJ_SmallCrate = 983,
    OBJ_KT_RexLevel = 984,
    OBJ_KT_Rex = 985,
    OBJ_KT_RexSequences = 986,
    OBJ_KT_RexDoorPlaye = 987,
    OBJ_KT_RexDoorTrex = 988,
    OBJ_KT_RexFloorSwit = 989,
    OBJ_MediumBasket = 990,
    OBJ_Blue_bean = 991,
    OBJ_KT_Lazerwall = 992,
    OBJ_ZBomb = 993,
    OBJ_Scorpion = 994,
    OBJ_KT_Lazerlight = 995,
    OBJ_CF_Lamp = 996,
    OBJ_KT_Torch = 997,
    OBJ_NWtrickyball = 998,
    OBJ_VFP_LiftIndicat = 999,
    OBJ_KT_Fallingrocks = 1000,
    OBJ_EndObject = 1001,
    OBJ_AnimSwoop = 1002,
    OBJ_SB_CloudrunnerA = 1003,
    OBJ_AnimKrystal = 1004,
    OBJ_CFPowerLock = 1005,
    OBJ_MMSH_Torch = 1006,
    OBJ_AnimShadowHunte = 1007,
    OBJ_CFCheapGalleon = 1008,
    OBJ_CCgrubBlue = 1009,
    OBJ_CCgrubRed = 1010,
    OBJ_ECSH_Creator = 1011,
    OBJ_KT_AnimSpellSto = 1012,
    OBJ_CFBrickTest = 1013,
    OBJ_DIMbosscrackpar = 1014,
    OBJ_TDtextureCreato = 1015,
    OBJ_CFBrickTest2 = 1016,
    OBJ_CF_DFBackGround = 1017,
    OBJ_CF_MMPBackGroun = 1018,
    OBJ_Tumbleweed2 = 1019,
    OBJ_WGSH_projball = 1020,
    OBJ_TumbleWeedBush2 = 1021,
    OBJ_VampireBat = 1022,
    OBJ_SC_musclelightf = 1023,
    OBJ_foodbagBlueMush = 1024,
    OBJ_foodbagBlueGrub = 1025,
    OBJ_WGSH_Torch = 1026,
    OBJ_sidefoodbagGene = 1027,
    OBJ_GPSH_flybaddie = 1028,
    OBJ_NWreplaymedal = 1030,
    OBJ_DustDevil = 1031,
    OBJ_GPSH_Colrise = 1032,
    OBJ_GPSHswapstone = 1033,
    OBJ_Tumbleweed1twig = 1034,
    OBJ_Tumbleweed2twig = 1035,
    OBJ_NWMultiSeq = 1036,
    OBJ_SC_steppingston = 1037,
    OBJ_CFliftGate = 1039,
    OBJ_NWSH_colpushped = 1041,
    OBJ_NWSH_ped = 1042,
    OBJ_SC_meterblock = 1043,
    OBJ_PortalSpellDoor = 1044,
    OBJ_DR_EarthWarrior = 1046,
    OBJ_DR_LaserCannon = 1047,
    OBJ_DR_PushCart = 1048,
    OBJ_DR_CloudRunner = 1049,
    OBJ_foodbagGreenApp = 1050,
    OBJ_foodbagBrownApp = 1051,
    OBJ_foodbagSmokedFi = 1052,
    OBJ_foodbagOldMeat = 1053,
    OBJ_foodbagRedBean = 1054,
    OBJ_foodbagBrownBea = 1055,
    OBJ_foodbagBlueBean = 1056,
    OBJ_foodbagRedMushr = 1057,
    OBJ_foodbagRedGrub = 1058,
    OBJ_foodbagOldMushr = 1059,
    OBJ_foodbagOldGrub = 1060,
    OBJ_foodbagapple = 1061,
    OBJ_DR_IonCannon = 1062,
    OBJ_ScorpionRobot = 1063,
    OBJ_DR_IonCannonPol = 1064,
    OBJ_DRbullet = 1065,
    OBJ_DR_FireBall = 1066,
    OBJ_DFP_Spellstone = 1067,
    OBJ_DFP_seqpoint = 1068,
    OBJ_DFP_DoorSwitch = 1069,
    OBJ_DFP_RoundDoor = 1070,
    OBJ_DFPLift1 = 1071,
    OBJ_DFP_LevelContro = 1073,
    OBJ_DFP_ObjCreator = 1074,
    OBJ_GPbonfire = 1075,
    OBJ_icebeam = 1076,
    OBJ_DRBlastedWall = 1077,
    OBJ_DRExplodeWall = 1078,
    OBJ_DRExplodePieces = 1079,
    OBJ_DR_NiceSharpy = 1080,
    OBJ_CChightop = 1081,
    OBJ_DRLavaControl = 1082,
    OBJ_FireFlyLantern = 1083,
    OBJ_LanternFireFly = 1084,
    OBJ_SC_MMP_Key = 1085,
    OBJ_DR_BigSkeetla = 1086,
    OBJ_DR_Creator = 1087,
    OBJ_TrickyGuard = 1088,
    OBJ_DR_SmallSkeetla = 1089,
    OBJ_DFP_Torch = 1090,
    OBJ_VariableObject = 1091,
    OBJ_appleAnim = 1092,
    OBJ_beanAnim = 1093,
    OBJ_meatAnim = 1094,
    OBJ_fishAnim = 1095,
    OBJ_mushroomAnim = 1096,
    OBJ_grubAnim = 1097,
    OBJ_RD_wall = 1098,
    OBJ_RD_frond = 1099,
    OBJ_SC_BWC_door = 1101,
    OBJ_DR_tube = 1104,
    OBJ_Green_scarabAni = 1105,
    OBJ_Red_scarabAnim = 1106,
    OBJ_Gold_scarabAnim = 1107,
    OBJ_GPBoneHead = 1109,
    OBJ_WG_PollenPod = 1110,
    OBJ_WG_PollenCannon = 1111,
    OBJ_WG_Triffid = 1112,
    OBJ_DR_SupGuardClaw = 1113,
    OBJ_WG_Tentacle = 1114,
    OBJ_CCkrazoaBits = 1115,
    OBJ_SPShop = 1116,
    OBJ_SPShopKeeper = 1117,
    OBJ_SPFruit = 1118,
    OBJ_SPMeat = 1119,
    OBJ_SPRedMushroom = 1120,
    OBJ_SPRedMaggot = 1121,
    OBJ_SPMagic = 1122,
    OBJ_SPFishingNet = 1123,
    OBJ_SPLantern = 1124,
    OBJ_SPTranslator = 1125,
    OBJ_SPSideFood = 1126,
    OBJ_SPMagicChest = 1127,
    OBJ_SPFoodContainer = 1128,
    OBJ_SPMap = 1129,
    OBJ_SPReplayDisk = 1130,
    OBJ_DR_Vines = 1131,
    OBJ_DR_Geezer = 1132,
    OBJ_DR_ExplodeDoor = 1133,
    OBJ_DR_Chimmey = 1136,
    OBJ_DR_CageControl = 1137,
    OBJ_DR_Cage = 1138,
    OBJ_DR_CloudDoorA = 1139,
    OBJ_DR_CloudDoorB = 1140,
    OBJ_DR_PressurePad = 1141,
    OBJ_SPWell = 1142,
    OBJ_DRPerch = 1143,
    OBJ_PortalDoorAnim = 1145,
    OBJ_VisAnimator = 1146,
    OBJ_Pollen = 1147,
    OBJ_DR_Shackle = 1148,
    OBJ_DR_BigShackle = 1149,
    OBJ_SPDoor = 1150,
    OBJ_SPScarab = 1151,
    OBJ_SPSeqObj = 1153,
    OBJ_PollenFragment = 1154,
    OBJ_SPDrape = 1155,
    OBJ_DR_HighTop = 1156,
    OBJ_DR_Bell = 1157,
    OBJ_DR_Rock = 1158,
    OBJ_DFP_floorbar = 1159,
    OBJ_DFP_wallbar = 1160,
    OBJ_DR_HighDoorA = 1161,
    OBJ_DR_HighDoorB = 1162,
    OBJ_DR_HighPlatform = 1163,
    OBJ_DFP_PuzzlePad = 1164,
    OBJ_DFP_ForceAway = 1165,
    OBJ_SHLevelControl = 1166,
    OBJ_DFP_PitSwitch = 1168,
    OBJ_DFP_DoorSwitch2 = 1169,
    OBJ_DFP_dish = 1170,
    OBJ_DFP_BigDoor1 = 1171,
    OBJ_DFP_BigDoor2 = 1172,
    OBJ_DFP_SmallDoor = 1173,
    OBJ_DFP_Statue1 = 1175,
    OBJ_DFP_RotatePuzzl = 1176,
    OBJ_DFP_LaserBeam = 1177,
    OBJ_DFP_PerchSwitch = 1179,
    OBJ_DFP_PerchBase = 1180,
    OBJ_DFP_ForceSwitch = 1181,
    OBJ_DR_CloudSmallDo = 1182,
    OBJ_MediumMetalCrat = 1183,
    OBJ_DR_pulley = 1185,
    OBJ_DR_TrackDoor = 1186,
    OBJ_DR_TrackDoor2 = 1187,
    OBJ_DR_IceFire = 1188,
    OBJ_DR_WireFence = 1189,
    OBJ_DR_cradle = 1191,
    OBJ_TexFrameAnimato = 1192,
    OBJ_DR_SupPortal = 1193,
    OBJ_SHswaplift = 1194,
    OBJ_DR_Lever_OnePre = 1195,
    OBJ_Skeetla = 1196,
    OBJ_SkeetlaWall = 1197,
    OBJ_SPitembeam = 1198,
    OBJ_DRProjectileSwi = 1200,
    OBJ_PortalSpell = 1201,
    OBJ_SHplantspore = 1202,
    OBJ_DR_TrackLever = 1203,
    OBJ_DRCollapsePieac = 1204,
    OBJ_DFP_TargetBlock = 1205, // name may be incorrect
    OBJ_DR_CollapseTube = 1206,
    OBJ_DRPlatformColla = 1207, // name may be incorrect
    OBJ_DRPlatformColla_ = 1208, // name may be incorrect
    OBJ_TumbleWeedBush3 = 1209,
    OBJ_Tumbleweed3 = 1210,
    OBJ_Tumbleweed3twig = 1211,
    OBJ_DR_CollapseCont = 1212,
    OBJ_DR_PartSeqobj = 1213,
    OBJ_GP_ShrinePillar = 1214,
    OBJ_DFP_blockwall = 1215,
    OBJ_DR_CaveIn = 1216,
    OBJ_SC_flamegamefla = 1218,
    OBJ_DFP_SpellPlace = 1219,
    OBJ_DR_LightBeam = 1222,
    OBJ_DFP_SmallTunDoo = 1223,
    OBJ_DR_LandSquare = 1224,
    OBJ_grenade = 1225,
    OBJ_GP_ChimneySwipe = 1226,
    OBJ_CCmetaldoor = 1227,
    OBJ_barrel = 1228,
    OBJ_CCrockDoor = 1229,
    OBJ_CCrockDoorPiece = 1230,
    OBJ_BlownUpTarget = 1231,
    OBJ_CCgrassfloor = 1232,
    OBJ_CCgrassfloorPie = 1233,
    OBJ_DRSpecialLoader = 1234,
    OBJ_CRSnowClaw3 = 1235,
    OBJ_CRSnowClawBike3 = 1236,
    OBJ_DR_LightPole = 1237,
    OBJ_DR_LightHalo = 1238,
    OBJ_Nurse = 1239,
    OBJ_CCsettlementroo = 1240,
    OBJ_KamerianBoss = 1241,
    OBJ_DR_CloudPerch = 1242,
    OBJ_BossDrakorAster = 1243,
    OBJ_BossDrakorFlatR = 1244,
    OBJ_DFP_BomBot = 1245,
    OBJ_DFP_SmallDoor2 = 1246,
    OBJ_KamerianAcid = 1247,
    OBJ_DFP_TargetBlock_ = 1248, // name may be incorrect
    OBJ_BossDrakor_sequ = 1249,
    OBJ_DR_EarthCallPad = 1250,
    OBJ_KamerianFlame = 1251,
    OBJ_DR_CloudCallPad = 1253,
    OBJ_DFP_Textblock = 1254,
    OBJ_DR_CaveInFlow = 1255,
    OBJ_DR_AnimCollPiea = 1256,
    OBJ_DRSmallExplodeW = 1257,
    OBJ_DRSmallExplodeP = 1258,
    OBJ_GP_Shrine = 1259,
    OBJ_iceblast = 1260,
    OBJ_BossDrakor_Lase = 1261,
    OBJ_AMLevelControl = 1263,
    OBJ_flameblast = 1264,
    OBJ_CCkrazoaTabletA = 1265,
    OBJ_DusterAnim = 1267,
    OBJ_DR_LightPoleYel = 1268,
    OBJ_KamSwitch = 1269,
    OBJ_KamColumn = 1270,
    OBJ_LaserEmitter = 1271,
    OBJ_DR_LightLampYel = 1272,
    OBJ_DFP_Platform1 = 1273,
    OBJ_DFP_PowerBolt = 1274,
    OBJ_WCQueenEarthWal = 1275,
    OBJ_WCTrex = 1276,
    OBJ_WCTeethBowl = 1277,
    OBJ_WCBouncyCrate = 1278,
    OBJ_AnimKingEarthWa = 1279,
    OBJ_WCKingEarthWalk = 1280,
    OBJ_DFP_SmallBrownD = 1281,
    OBJ_GP_PillarDoor = 1282,
    OBJ_BossDrakor_Dumm = 1283,
    OBJ_DFP_translator = 1284,
    OBJ_WCSeqObject = 1285,
    OBJ_WCTrexChase = 1286,
    OBJ_WCFlameBurst = 1287,
    OBJ_WCSabreChase = 1288,
    OBJ_WCLevelControl = 1289,
    OBJ_WCSunTempleDoor = 1290,
    OBJ_WCMoonTempleDoo = 1291,
    OBJ_WCSlabDoor = 1292,
    OBJ_WCCageDoor = 1293,
    OBJ_WCPressureSwitc = 1294,
    OBJ_WCBeacon = 1295,
    OBJ_WCTrexStatue = 1296,
    OBJ_WCBossDoor = 1297,
    OBJ_fruitBranchRock = 1298,
    OBJ_DR_LightLamp = 1299,
    OBJ_WCFlameSource = 1300,
    OBJ_WCPushBlock = 1301,
    OBJ_GPanimBonehead = 1302,
    OBJ_MMP_trenchFX = 1303,
    OBJ_MMP_gyservent = 1304,
    OBJ_MMP_moonrock = 1305,
    OBJ_LunaimarSpit = 1307,
    OBJ_MMP_asteroid_fl = 1308,
    OBJ_WCTile = 1309,
    OBJ_WGbouncyVine = 1310,
    OBJ_WCSunDoor = 1311,
    OBJ_WCMoonDoor = 1312,
    OBJ_MMP_Krazoa = 1313,
    OBJ_WCTrexTooth = 1314,
    OBJ_MMP_moonseedbus = 1315,
    OBJ_MMP_moonseedvin = 1316,
    OBJ_MMP_levelcontro = 1317,
    OBJ_WCInvUseObj = 1318,
    OBJ_WCGeneralDoor = 1319,
    OBJ_WCMoonTempleLif = 1320,
    OBJ_WCSunTempleLift = 1321,
    OBJ_WCAnimSilverToo = 1322,
    OBJ_WCAnimGoldTooth = 1323,
    OBJ_WCAnimSunStone = 1324,
    OBJ_WCAnimMoonStone = 1325,
    OBJ_DR_BarrelPositi = 1326,
    OBJ_KD_Sequences = 1327,
    OBJ_BKfleshmelt = 1328,
    OBJ_WGSeqObject = 1329,
    OBJ_WGmutant = 1330,
    OBJ_WGsunDial = 1331,
    OBJ_WGsunDialVane = 1332,
    OBJ_WGkameriaBelt = 1333,
    OBJ_WGblackeyePod = 1334,
    OBJ_WGboulder = 1335,
    OBJ_AnimSabre = 1336,
    OBJ_DBstealerworm = 1337,
    OBJ_MMP_asteroid_re = 1338,
    OBJ_AnimDrakor = 1339,
    OBJ_MMP_Bridge = 1340,
    OBJ_VFPLift3 = 1343,
    OBJ_VFP_PodiumPoint = 1344,
    OBJ_DB_SuperDoor = 1345,
    OBJ_DB_FlameSwitch = 1346,
    OBJ_DB_OrbDoor = 1347,
    OBJ_DB_SuperSymbol = 1348,
    OBJ_DBStaticDiamond = 1349,
    OBJ_VFP_PuzzlePad = 1350,
    OBJ_VFP_PitSwitch = 1351,
    OBJ_VFP_Ladders2 = 1352,
    OBJ_VFP_PowerBolt = 1353,
    OBJ_VFP_Block2 = 1354,
    OBJ_MMP_moonseed = 1355,
    OBJ_MMP_mseedrecept = 1356,
    OBJ_DBAnimshooterba = 1357,
    OBJ_VFP_SpellPlace = 1358, // name may be incorrect
    OBJ_BWAlphaAnim = 1359,
    OBJ_CCperchSwitch = 1360,
    OBJ_VFP_flamepoint = 1361,
    OBJ_CCfireflyfind = 1363,
    OBJ_BWLevelControl = 1364,
    OBJ_CCsandwormBoss = 1365,
    OBJ_PortalTexAnimat = 1366,
    OBJ_DB_fruittree = 1367,
    OBJ_DB_shortfruittr = 1368,
    OBJ_VFP_lavapool = 1369,
    OBJ_VFP_lavastar = 1370,
    OBJ_VFP_SpellPlace_ = 1372, // name may be incorrect
    OBJ_RestPerch = 1373,
    OBJ_LunaimarShield = 1374,
    OBJ_VFP_coreplatani = 1375,
    OBJ_NWmutant = 1376,
    OBJ_WM_Planets = 1377,
    OBJ_NWanimice1 = 1378,
    OBJ_NWanimice2 = 1379,
    OBJ_NWanimice3 = 1380,
    OBJ_NWice1 = 1381,
    OBJ_NWice2 = 1382,
    OBJ_NWice3 = 1383,
    OBJ_WM_PlanetsSun = 1385,
    OBJ_VFP_mocklazer = 1386,
    OBJ_CCnewseqobject = 1387,
    OBJ_WM_TransTop = 1388,
    OBJ_DB_FakeHorizon = 1389,
    OBJ_animbubble = 1390,
    OBJ_coldWaterContro = 1394,
    OBJ_Fall_Ladders = 1395,
    OBJ_CFDoubleSwitch = 1396,
    OBJ_CF_DoorLight = 1397,
    OBJ_CFAnimTreasChes = 1398,
    OBJ_CFExplodeWall = 1399,
    OBJ_CFBlastedWall = 1400,
    OBJ_CFWallPieaces = 1401,
    OBJ_MagicPlantBase = 1403,
    OBJ_AnimGuardClaw = 1404,
    OBJ_CFAnimTreasureC = 1405,
    OBJ_CFKyteGoldPerch = 1406,
    OBJ_CRFuelTank = 1407,
    OBJ_DFdebris2piece = 1408,
    OBJ_SHwhitemushroom = 1409,
    OBJ_KP_red_orb = 1411,
    OBJ_KP_red_green = 1412,
    OBJ_KP_red_blue = 1413,
    OBJ_KP_red_yellow = 1414,
    OBJ_KP_red_purple = 1415,
    OBJ_SC_DinoMole = 1419,
    OBJ_SHsign = 1420,
    OBJ_waterfallContro = 1421,
    OBJ_CF_RockPiece = 1422,
    OBJ_KP_console_fire = 1423,
    OBJ_KP_console_eart = 1424,
    OBJ_KP_console_wate = 1425,
    OBJ_KP_console_magi = 1426,
    OBJ_KP_textblock_fi = 1427,
    OBJ_KP_textblock_ea = 1428,
    OBJ_KP_textblock_wa = 1429,
    OBJ_KP_textblock_ma = 1430,
    OBJ_KP_AnimKrazoa = 1431,
    OBJ_KP_RedKrazoa = 1432,
    OBJ_KP_sequences = 1433,
    OBJ_KP_Transporter = 1434,
    OBJ_CCextbridge = 1435,
    OBJ_KP_SectionDoor = 1436,
    OBJ_BalloonBaddie = 1437,
    OBJ_KP_FinDoor = 1438,
    OBJ_CFExplosiveKey = 1439,
    OBJ_CCExplosiveDoor = 1440,
    OBJ_SB_ShipGunBroke = 1441,
    OBJ_CCcannonSwitch = 1442,
    OBJ_SwarmBaddie = 1443,
    OBJ_PinPonBaddie = 1444,
    OBJ_PirahnaBaddie = 1445,
    OBJ_WispBaddie = 1446,
    OBJ_TurtleBaddie = 1447,
    OBJ_SpellOverlay = 1449,
    OBJ_CCexplodedoor = 1450,
    OBJ_CCexplodedoorPi = 1451,
    OBJ_CCgasvent = 1452,
    OBJ_CCgasventContro = 1453,
    OBJ_CCboulder = 1454,
    OBJ_CCgoldnuggetPic = 1455,
    OBJ_MagicDustSmallA = 1456,
    OBJ_MagicDustMidAni = 1457,
    OBJ_MagicDustLargeA = 1458,
    OBJ_MagicDustHugeAn = 1459,
    OBJ_SidekickBallAni = 1466
};

#endif
