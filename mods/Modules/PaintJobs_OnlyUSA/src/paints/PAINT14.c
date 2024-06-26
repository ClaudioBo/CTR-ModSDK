#include <common.h>
#include "../tex.h"

short brown_fakecrash[16] __attribute__ ((section (".data"))) = {
0x20c5,0x1cc5,0x1ca4,0x1483,0x1042,0xc21,0x214d,0x190b,0x2d8f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
short motortop_fakecrash[16] __attribute__ ((section (".data"))) = {
0x3568,0x41ab,0x3127,0x24c2,0x1462,0x1862,0x24c4,0x2d03,0x1883,0x564d,0x6ab2,0x7b79,0x3d88,0x4e2d,0x3545,0x41a9,};
short floor_fakecrash[16] __attribute__ ((section (".data"))) = {
0x1861,0x20c3,0x3547,0x28e4,0x3968,0x4189,0x3d88,0x3967,0x24c4,0x3126,0x1882,0x2d06,0x1461,0xc41,0xc41,0x1ca3,};
short motorside_fakecrash[16] __attribute__ ((section (".data"))) = {
0x2d05,0x3548,0x3969,0x2480,0xc42,0x1ca2,0x2905,0x41aa,0x4186,0x49ea,0x524f,0x820,0x3d89,0x564d,0x6ab2,0x7b79,};
short front_fakecrash[16] __attribute__ ((section (".data"))) = {
0x1ce6,0x35ee,0x4737,0x677c,0x24c4,0x2d06,0x3968,0x45ca,0x562c,0x66af,0x49eb,0x6b12,0x1c82,0xc40,0x3ab3,0x4f38,};
short back_fakecrash[16] __attribute__ ((section (".data"))) = {
0x1cc5,0x39ac,0x3651,0x4b37,0x5b7a,0x46d5,0x20a3,0x2ce5,0x3547,0x45aa,0x5e4d,0x6ad0,0x49eb,0x7355,0x1861,0xc20,};
short bridge_fakecrash[16] __attribute__ ((section (".data"))) = {
0x18a3,0x2926,0x1441,0x3548,0x5dec,0x1c82,0x4189,0x520c,0x3dca,0x24c5,0x6e91,0x72f4,0x4a2e,0x5ed3,0x5271,0x6f57,};
short exhaust_fakecrash[16] __attribute__ ((section (".data"))) = {
0x1861,0x20a3,0x3968,0x45aa,0x4630,0x56b3,0x5ed6,0x4a52,0x6b37,0x779c,0x6f59,0x41ec,0x318a,0x18c5,0x2528,0xc63,};

Texture PAINT14[] __attribute__ ((section (".sdata"))) = {
	[0] =
	{
		.front = (char*)front_fakecrash,
		.back = (char*)back_fakecrash,
		.floor = (char*)floor_fakecrash,
		.brown = (char*)brown_fakecrash,
		.motorside = (char*)motorside_fakecrash,
		.motortop = (char*)motortop_fakecrash,
		.bridge = (char*)bridge_fakecrash,
		.exhaust = (char*)exhaust_fakecrash,
	},
};