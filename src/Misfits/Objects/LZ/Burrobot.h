#ifndef OBJ_BURROBOT_H
#define OBJ_BURROBOT_H

#include "Misfits.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    uint16 aniFrames;
}ObjectBurrobot;

// Entity Class
typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    uint8 type;
    int32 timer;
    Vector2 startPos;
    uint8 startDir;
    Animator animator;
    Entity* targetPlayer;
}EntityBurrobot;

// Object Struct
extern ObjectBurrobot* Burrobot;

// Standard Entity Events
void Burrobot_Update(void);
void Burrobot_Draw(void);
void Burrobot_Create(void* data);
void Burrobot_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
void Burrobot_EditorDraw(void);
void Burrobot_EditorLoad(void);
#endif
void Burrobot_Serialize(void);

// Extra Entity Functions
void Burrobot_DebugDraw(void);
void Burrobot_DebugSpawn(void);

void Burrobot_CheckOffScreen(void);
void Burrobot_CheckPlayerCollisions(void);

//States
void Burrobot_State_Init(void);
void Burrobot_State_AwaitPlayer(void);
void Burrobot_State_Jumped(void);
void Burrobot_State_Moving(void);
void Burrobot_State_Stopped(void);

#endif //! OBJ_BURROBOT_H
