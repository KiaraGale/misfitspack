#include "Misfits.h"
#include "All.h"

ObjectOrbinaut *Orbinaut = NULL;

void Orbinaut_StageLoad(void) {
    Mod.Super(Orbinaut->classID, SUPER_STAGELOAD, NULL);
    Orbinaut->aniFrames = RSDK.LoadSpriteAnimation("MMZ/Orbinaut.bin", SCOPE_STAGE);
}