#ifndef OBJ_STALACTITE_H
#define OBJ_STALACTITE_H

#include "Misfits.h"

typedef struct ObjectStalactite ObjectStalactite;
typedef struct EntityStalactite EntityStalactite;

// Object Class
struct ObjectStalactite {
    RSDK_OBJECT
    Hitbox hitboxStalactite;
    Hitbox hitboxRange;
    uint16 aniFrames;
    uint16 sfxShoot;
};

// Entity Class
struct EntityStalactite {
    RSDK_ENTITY
    StateMachine(state);
    Animator animator;
};

// Object Struct
extern ObjectStalactite *Stalactite;

// Standard Entity Events
// void Stalactite_Update(void);
// void Stalactite_LateUpdate(void);
// void Stalactite_StaticUpdate(void);
// void Stalactite_Draw(void);
// void Stalactite_Create(void *data);
void Stalactite_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
// void Stalactite_EditorDraw(void);
// void Stalactite_EditorLoad(void);
#endif
// void Stalactite_Serialize(void);

#endif //! OBJ_STALACTITE_H
