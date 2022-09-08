#include "Player.h"

ObjectPlayer* Player;

// Public Functions
bool32 (*Player_CheckBadnikTouch)(EntityPlayer* player, void* entity, Hitbox* entityHitbox) = NULL;
bool32 (*Player_CheckBadnikBreak)(EntityPlayer* player, void* entity, bool32 destroy) = NULL;