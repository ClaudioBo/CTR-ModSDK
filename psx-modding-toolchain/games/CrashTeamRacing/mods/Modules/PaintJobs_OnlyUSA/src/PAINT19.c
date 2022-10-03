#include <common.h>

struct Texture
{
	const short * front;
	const short * back;
	const short * floor;
	const short * brown;
	const short * motorside;
	const short * motortop;
	const short * bridge;
	const short * exhaust;
};

short brown_reddishorange[16] __attribute__ ((section (".data"))) = {
0x1953,0x1952,0x1932,0x1911,0x18ee,0x18cb,0x190b,0x214d,0x2d8f,0x0,0x0,0x0,0x0,0x0,0x0,0x0,};

short motortop_reddishorange[16] __attribute__ ((section (".data"))) = {
0xd6,0xfb,0xb3,0x24c2,0x1462,0x6a,0x8f,0x2d03,0x6c,0x1d9d,0x3e5d,0x6f7e,0x3d88,0x4a0c,0x3545,0x41a9,};

short floor_reddishorange[16] __attribute__ ((section (".data"))) = {
0x25,0x6b,0xb3,0x6e,0xd6,0xfa,0xd7,0x6f,0x6c,0xb2,0x90,0x47,0x2091,0x1c25,0x22,0x49,};

short motorside_reddishorange[16] __attribute__ ((section (".data"))) = {
0xb2,0xd5,0xd7,0x6b,0xc42,0x1ca2,0x2905,0xfa,0x4186,0x49ea,0x524f,0x820,0xd8,0x1d9d,0x3e5d,0x6f7e,};

short front_reddishorange[16] __attribute__ ((section (".data"))) = {
0x1ce6,0x35ee,0x4b17,0x635b,0x8f,0xb2,0xd7,0xfc,0x157c,0x363d,0x93c,0x4abd,0x6b,0x47,0x3a93,0x4b17,};

short back_reddishorange[16] __attribute__ ((section (".data"))) = {
0x1cc5,0x39ac,0x3651,0x4716,0x5759,0x42b4,0x6d,0x91,0xb5,0xfa,0x25dd,0x3e5d,0x93c,0x5f1e,0x49,0x46,};

short bridge_reddishorange[16] __attribute__ ((section (".data"))) = {
0x18a3,0x2926,0x48,0xd5,0xd5c,0x6b,0xd9,0x3d5c,0x3dca,0x90,0x3a5d,0x4edd,0x4a2e,0x5ab2,0x4e50,0x6b36,};

short exhaust_reddishorange[16] __attribute__ ((section (".data"))) = {
0x49,0x6d,0xd7,0xfa,0x4630,0x5292,0x5ab5,0x4a51,0x6716,0x737b,0x6b38,0x41ec,0x318a,0x18c5,0x2528,0xc63,};

struct Texture PAINT19[] __attribute__ ((section (".sdata"))) = {
	[0] =
	{
		.front = front_reddishorange,
		.back = back_reddishorange,
		.floor = floor_reddishorange,
		.brown = brown_reddishorange,
		.motorside = motorside_reddishorange,
		.motortop = motortop_reddishorange,
		.bridge = bridge_reddishorange,
		.exhaust = exhaust_reddishorange,
	},
};