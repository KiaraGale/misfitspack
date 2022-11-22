// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: SpearBlock Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "SpearBlock.h"
#include "Global/Zone.h"

ObjectSpearBlock *SpearBlock        = NULL;
ModObjectSpearBlock *Mod_SpearBlock = NULL;

void *SpearBlock_State_SpearRetracted = NULL;
void *SpearBlock_State_SpearExtended  = NULL;

void SpearBlock_StageLoad(void)
{
    Mod.Super(SpearBlock->classID, SUPER_STAGELOAD, NULL);

    Mod_SpearBlock->sfxSpear = RSDK.GetSfx("MTZ/Spear.wav");
}

bool32 SpearBlock_State_SpearRetracted_Hook(bool32 skippedState)
{
    RSDK_THIS(SpearBlock);

    // if the state isn't spearRetracted anymore, the sfx should play
    if (self->state != SpearBlock_State_SpearRetracted)
        RSDK.PlaySfx(Mod_SpearBlock->sfxSpear, false, 0xFF);

    return false;
}

bool32 SpearBlock_State_SpearExtended_Hook(bool32 skippedState)
{
    RSDK_THIS(SpearBlock);

    // if the state isn't spearExtended anymore, the sfx should play
    if (self->state != SpearBlock_State_SpearExtended)
        RSDK.PlaySfx(Mod_SpearBlock->sfxSpear, false, 0xFF);

    return false;
}
