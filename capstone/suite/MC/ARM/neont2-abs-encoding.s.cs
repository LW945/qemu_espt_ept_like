# CS_ARCH_ARM, CS_MODE_THUMB, None
0xf1,0xff,0x20,0x03 = vabs.s8 d16, d16
0xf5,0xff,0x20,0x03 = vabs.s16 d16, d16
0xf9,0xff,0x20,0x03 = vabs.s32 d16, d16
0xf9,0xff,0x20,0x07 = vabs.f32 d16, d16
0xf1,0xff,0x60,0x03 = vabs.s8 q8, q8
0xf5,0xff,0x60,0x03 = vabs.s16 q8, q8
0xf9,0xff,0x60,0x03 = vabs.s32 q8, q8
0xf9,0xff,0x60,0x07 = vabs.f32 q8, q8
0xf0,0xff,0x20,0x07 = vqabs.s8 d16, d16
0xf4,0xff,0x20,0x07 = vqabs.s16 d16, d16
0xf8,0xff,0x20,0x07 = vqabs.s32 d16, d16
0xf0,0xff,0x60,0x07 = vqabs.s8 q8, q8
0xf4,0xff,0x60,0x07 = vqabs.s16 q8, q8
0xf8,0xff,0x60,0x07 = vqabs.s32 q8, q8
