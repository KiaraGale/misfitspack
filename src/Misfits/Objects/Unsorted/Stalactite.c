#include "../All.h"
#include "Misfits.h"

ObjectStalactite *Stalactite = NULL;

void Stalactite_StageLoad(void) {
  Mod.Super(Stalactite->classID, SUPER_STAGELOAD, NULL);
  Stalactite->aniFrames =
      RSDK.LoadSpriteAnimation("LRZ1/Stalactite.bin", SCOPE_STAGE);
}