#ifndef OBJ_SPEARBLOCK_H
#define OBJ_SPEARBLOCK_H

#include "Misfits.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox blockHitbox;
    Hitbox spearHitboxes[4];
    uint16 aniFrames;
    Animator animator;
} ObjectSpearBlock;

// Modded Object Class
typedef struct {
    uint16 sfxSpear;
} ModObjectSpearBlock;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 spearDir;
    Vector2 spearPos;
    int32 timer;
    Animator animator;
}EntitySpearBlock;

// Object Entity
extern ObjectSpearBlock *SpearBlock;
extern ModObjectSpearBlock *Mod_SpearBlock;

// State Hooks
extern void *SpearBlock_State_SpearRetracted;
extern void *SpearBlock_State_SpearExtended;

// Standard Entity Events
void SpearBlock_StageLoad(void);

// Extra Entity Functions
bool32 SpearBlock_State_SpearRetracted_Hook(bool32 skippedState);
bool32 SpearBlock_State_SpearExtended_Hook(bool32 skippedState);

#endif //!OBJ_SPEARBLOCK_H
