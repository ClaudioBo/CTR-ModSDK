#include <common.h>
#include "../tex.h"

short brown_roo[16] __attribute__ ((section (".data"))) = {
0x111,0xee,0xcc,0xaa,0x67,0x45,0x214d,0x190b,0x2d8f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};
short motortop_roo[16] __attribute__ ((section (".data"))) = {
0x158,0x19d,0x114,0x24c2,0x1462,0x866,0xce,0x2d03,0x489,0x5de,0x265e,0x3ede,0x3d88,0x4e2d,0x3545,0x41a9,};
short floor_roo[16] __attribute__ ((section (".data"))) = {
0x68,0xad,0x136,0xd0,0x137,0x17a,0x159,0xce,0x113,0x114,0x113,0x89,0xf2,0x7,0x5,0x8b,};
short motorside_roo[16] __attribute__ ((section (".data"))) = {
0x112,0x158,0x17a,0x89,0xc42,0x1ca2,0x2905,0x1be,0x4186,0x49ea,0x524f,0x820,0x19c,0x121e,0x2e9e,0x4b3e,};
short front_roo[16] __attribute__ ((section (".data"))) = {
0x1ce6,0x35ee,0x4737,0x677c,0xaf,0x112,0x159,0x19d,0x1e3e,0x2e9e,0x9de,0x3f1e,0x6a,0x25,0x3ab3,0x4f38,};
short back_roo[16] __attribute__ ((section (".data"))) = {
0x1cc5,0x39ac,0x3651,0x4b37,0x5b7a,0x46d5,0xad,0xf2,0x157,0x1be,0x1a9e,0x3f1e,0xa3e,0x577c,0x89,0x24,};
short bridge_roo[16] __attribute__ ((section (".data"))) = {
0x18a3,0x2926,0x48,0x158,0x1be,0x6b,0x19d,0x1a3e,0x3dca,0xf1,0x225e,0x32fe,0x4a2e,0x5ed3,0x5271,0x6f57,};
short exhaust_roo[16] __attribute__ ((section (".data"))) = {
0x69,0xad,0x158,0x19f,0x4630,0x5ad4,0x62f7,0x4e72,0x6f58,0x7bbd,0x737a,0x41ec,0x318a,0x18c5,0x2528,0xc63,};

Texture PAINT9[] __attribute__ ((section (".sdata"))) = {
	[0] =
	{
		.front = (char*)front_roo,
		.back = (char*)back_roo,
		.floor = (char*)floor_roo,
		.brown = (char*)brown_roo,
		.motorside = (char*)motorside_roo,
		.motortop = (char*)motortop_roo,
		.bridge = (char*)bridge_roo,
		.exhaust = (char*)exhaust_roo,
	},
};