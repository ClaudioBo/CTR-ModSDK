#include <common.h>

void CS_Podium_Prize_ThTick1(struct Thread *th)
{
    short interp;
    int angular;

    // get instance from thread
    struct Instance *inst = th->inst;

    // get object from thread
    short *prize = th->object;

    if (OVR_233.PodiumInitUnk3 != 0)
    {

        if (th->modelIndex != 0x38)
        {
            // Make visible
            inst->flags &= ~(HIDE_MODEL);
        }
        interp = DECOMP_VehMath_InterpBySpeed(prize[0x12], 0x14, 0);
        prize[0x12] = interp;
        interp = DECOMP_VehMath_InterpBySpeed(prize[0x11], 1, 0);
        prize[0x11] = interp;
    }

    // Sine(angle)
    angular = MATH_Sin(prize[5]);

    // posX and posY
    inst->matrix.t[0] = prize[0] + (prize[0x11] * angular >> 12);
    inst->matrix.t[1] = prize[1] + prize[0x12];

    // Cosine(angle)
    angular = MATH_Cos(prize[5]);

    // posZ
    inst->matrix.t[2] = prize[2] + (prize[0x11] * angular >> 12);

    if (OVR_233.isCutsceneOver != 0)
    {
        prize[0x14] = 0xf;
        prize[0x13] = 0xf;
        prize[0x15] = 0;

        inst->unk50 = 0x80;
        inst->unk51 = 0x80;

        // instance scale (x, y, z)
        inst->scale[0] = 0x1000;
        inst->scale[1] = 0x1000;
        inst->scale[2] = 0x1000;

        inst->matrix.t[0] = 0;
        inst->matrix.t[1] = 0;
        inst->matrix.t[2] = prize[10];

        ((struct InstDrawPerPlayer *)INST_GETIDPP(inst))->tileView = sdata->gGT->tileView_UI;

        OtherFX_Stop2(175);
        OtherFX_Stop2(174);

        // Play Sound
        // 0x9A - "Boing boing" -- when adding to trophy counter
        OtherFX_Play(0x9a, 1);

        // execute, then assign per-frame funcPtr to thread
        ThTick_SetAndExec(th, CS_Podium_Prize_ThTick2);
		return;
    }
    
	CS_Podium_Prize_Spin(inst, prize);
}