#include "Misfits.h"
#include "All.h"

ObjectSwingRope *SwingRope = NULL;

void SwingRope_StageLoad(void) {
    Mod.Super(SwingRope->classID, SUPER_STAGELOAD, NULL);
    SwingRope->aniFrames = RSDK.LoadSpriteAnimation("AIZ/SwingRope.bin", SCOPE_STAGE);
}