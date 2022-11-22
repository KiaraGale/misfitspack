#ifndef OBJ_ORBINAUT_H
#define OBJ_ORBINAUT_H

#include "Misfits.h"

#define ORBINAUT_ORB_COUNT (4)

typedef struct ObjectOrbinaut ObjectOrbinaut;
typedef struct EntityOrbinaut EntityOrbinaut;

// Object Class
struct ObjectOrbinaut {
    RSDK_OBJECT
    Hitbox hitboxBadnik;
    Hitbox hitboxOrb;
    uint16 aniFrames;
};

// Entity Class
struct EntityOrbinaut {
    RSDK_ENTITY
    StateMachine(state);
    int32 planeFilter;
    Vector2 startPos;
    uint8 startDir;
    uint8 activeOrbs;
    Vector2 orbPositions[ORBINAUT_ORB_COUNT];
    bool32 fireOrbs;
    Animator animatorFace;
    Animator animatorOrb;
};

// Object Entity
extern ObjectOrbinaut *Orbinaut;

// Standard Entity Events

// void Orbinaut_Update(void);
// void Orbinaut_LateUpdate(void);
// void Orbinaut_StaticUpdate(void);
// void Orbinaut_Draw(void);
// void Orbinaut_Create(void *data);
void Orbinaut_StageLoad(void);
#if RETRO_INCLUDE_EDITOR
// void Orbinaut_EditorDraw(void);
// void Orbinaut_EditorLoad(void);
#endif
// void Orbinaut_Serialize(void);


#endif //! OBJ_ORBINAUT_H
