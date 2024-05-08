#include <common.h>

#include "h21_Bank_ResetAllocator.c"
#include "h22_Bank_Alloc.c"
#include "h23_Bank_AssignSpuAddrs.c"
#include "h24_Bank_Destroy.c"
#include "h25_Bank_ClearInRange.c"
#include "h26_Bank_Load.c"
#include "h27_Bank_DestroyLast.c"
#include "h28_Bank_DestroyUntilIndex.c"
#include "h29_Bank_DestroyAll.c"
#include "h30_howl_InstrumentPitch.c"
#include "h31_howl_InitGlobals.c"
#include "h32_howl_ParseHeader.c"
#include "h33_howl_ParseCseqHeader.c"
#include "h34_howl_LoadHeader.c"
#include "h35_howl_SetSong.c"
#include "h36_howl_LoadSong.c"
#include "h37_howl_ErasePtrCseqHeader.c"
#include "h38_howl_GetNextNote.c"
#include "h39_cseq_opcode01_noteoff.c"
#include "h40_cseq_opcode03.c"
#include "h41_howl_InitChannelAttr_Music.c"
#include "h42_cseq_opcode_from06and07.c"
#include "h43_cseq_opcode05_noteon.c"
#include "h44_cseq_opcode06.c"
#include "h45_cseq_opcode07.c"
#include "h46_cseq_opcode08.c"
#include "h47_cseq_opcode09.c"
#include "h48_cseq_opcode0a.c"
#include "h49_SongPool_FindFreeChannel.c"
#include "h50_SongPool_CalculateTempo.c"
#include "h51_SongPool_ChangeTempo.c"
#include "h52_SongPool_Start.c"
#include "h53_SongPool_Volume.c"
#include "h54_SongPool_AdvHub1.c"
#include "h55_SongPool_AdvHub2.c"
#include "h56_SongPool_StopCseq.c"
#include "h57_SongPool_StopAllCseq.c"
#include "h58_howl_Disable.c"
#include "h59_UpdateChannelVol_EngineFX.c"
#include "h60_UpdateChannelVol_OtherFX.c"
#include "h61_UpdateChannelVol_Music.c"
#include "h62_UpdateChannelVol_EngineFX_All.c"
#include "h63_UpdateChannelVol_Music_All.c"
#include "h64_UpdateChannelVol_OtherFX_All.c"

#include "../AltMods/Mods3.c"

void Mods3_EndOfFile()
{
	// leave empty
}