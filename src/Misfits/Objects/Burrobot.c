// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania The Misfits Pack
// Object Description: Burrobot Object
// Object Author: Ducky (RDC)
// ---------------------------------------------------------------------

#include "Burrobot.h"

#include "Player.h"
#include "Zone.h"
#include "DebugMode.h"

ObjectBurrobot *Burrobot;

void Burrobot_Update(void)
{
    RSDK_THIS(Burrobot);

    StateMachine_Run(self->state);
}

void Burrobot_Draw(void)
{
    RSDK_THIS(Burrobot);

    RSDK.DrawSprite(&self->animator, NULL, false);
}

void Burrobot_Create(void *data)
{
    RSDK_THIS(Burrobot);

    if (data) {
        int32 type = VOID_TO_INT(data);

        self->type      = type & 2;
        self->direction = type & 1;
    }

    self->visible = true;
    self->drawFX |= FX_FLIP;
    self->drawGroup     = Zone->objectDrawGroup[0];
    self->startPos      = self->position;
    self->startDir      = self->direction;
    self->active        = ACTIVE_BOUNDS;
    self->updateRange.x = TO_FIXED(128);
    self->updateRange.y = TO_FIXED(128);

    RSDK.SetSpriteAnimation(Burrobot->aniFrames, self->type < 2 ? 2 : 4, &self->animator, true, 0);
    self->state = Burrobot_State_Init;
}

void Burrobot_StageLoad(void)
{
    Burrobot->aniFrames = RSDK.LoadSpriteAnimation("LZ/Burrobot.bin", SCOPE_STAGE);

    Burrobot->hitboxBadnik.left   = -12;
    Burrobot->hitboxBadnik.top    = -18;
    Burrobot->hitboxBadnik.right  = 12;
    Burrobot->hitboxBadnik.bottom = 18;

    DEBUGMODE_ADD_OBJ(Burrobot);
}

void Burrobot_DebugDraw(void)
{
    RSDK.SetSpriteAnimation(Burrobot->aniFrames, DebugMode->itemType < 2 ? 2 : 4, &DebugMode->animator, true, 0);
    DebugMode->itemType &= 3;

    RSDK.DrawSprite(&DebugMode->animator, NULL, false);
}
void Burrobot_DebugSpawn(void)
{
    RSDK_THIS(DebugMode);

    CREATE_ENTITY(Burrobot, INT_TO_VOID(DebugMode->itemType), self->position.x, self->position.y);
}
void Burrobot_CheckOffScreen(void)
{
    RSDK_THIS(Burrobot);

    if (!RSDK.CheckOnScreen(self, NULL) && !RSDK.CheckPosOnScreen(&self->startPos, &self->updateRange)) {
        self->position  = self->startPos;
        self->direction = self->startDir;
        Burrobot_Create(NULL);
    }
}
void Burrobot_CheckPlayerCollisions(void)
{
    RSDK_THIS(Burrobot);

    if (!Player_CheckBadnikTouch || !Player_CheckBadnikBreak)
        return;

    foreach_active(Player, player)
    {
        if (Player_CheckBadnikTouch(player, self, &Burrobot->hitboxBadnik))
            Player_CheckBadnikBreak(player, self, true);
    }
}

void Burrobot_State_Init(void)
{
    RSDK_THIS(Burrobot);

    self->state = Burrobot_State_AwaitPlayer;
    Burrobot_State_AwaitPlayer();
}

void Burrobot_State_AwaitPlayer(void)
{
    RSDK_THIS(Burrobot);

    RSDK.ProcessAnimation(&self->animator);

    int32 targetDistance       = 0x7FFFFFFF;
    EntityPlayer *targetPlayer = NULL;
    self->targetPlayer         = RSDK_GET_ENTITY_GEN(SLOT_PLAYER1);

    foreach_active(Player, player)
    {
        int32 distance = abs(player->position.x - self->position.x);
        if (distance < targetDistance) {
            targetDistance     = distance;
            self->targetPlayer = (Entity *)player;
        }

        if (distance < TO_FIXED(96)) {
            if (player->position.y <= self->position.y) {
                if (targetPlayer) {
                    if (player->position.y < targetPlayer->position.y)
                        targetPlayer = player;
                }
                else {
                    targetPlayer = player;
                }
            }
        }
    }

    if (targetPlayer) {
        int32 distance = self->position.y - targetPlayer->position.y;
        if (distance >= 0 && distance <= TO_FIXED(128)) {
            if (RSDK.Rand(0, 8) == 0) {
                self->state  = Burrobot_State_Jumped;
                self->active = ACTIVE_NORMAL;

                if (targetPlayer->position.x < self->position.x) {
                    self->direction  = FLIP_NONE;
                    self->velocity.x = -0x8000;
                }
                else {
                    self->direction  = FLIP_X;
                    self->velocity.x = 0x8000;
                }
            }

            self->velocity.y = -0x40000;
            RSDK.SetSpriteAnimation(Burrobot->aniFrames, 2, &self->animator, true, 0);
        }
    }
    else {
        self->direction = self->targetPlayer->position.x < self->position.x ? FLIP_NONE : FLIP_X;
    }

    Burrobot_CheckPlayerCollisions();
    Burrobot_CheckOffScreen();
}

void Burrobot_State_Jumped(void)
{
    RSDK_THIS(Burrobot);

    RSDK.ProcessAnimation(&self->animator);

    if (self->velocity.y > 0 && self->animator.animationID == 2) {
        RSDK.SetSpriteAnimation(Burrobot->aniFrames, 3, &self->animator, true, 0);
    }

    self->position.x += self->velocity.x;
    self->position.y += self->velocity.y;
    self->velocity.y += 0x1800;

    if (self->velocity.y > 0) {

        if (RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, 0, 20 << 16, true)) {
            self->direction = self->targetPlayer->position.x < self->position.x ? FLIP_NONE : FLIP_X;

            self->timer = 256;
            RSDK.SetSpriteAnimation(Burrobot->aniFrames, 0, &self->animator, true, 0);
            self->state = Burrobot_State_Moving;
        }
    }

    Burrobot_CheckPlayerCollisions();
    Burrobot_CheckOffScreen();
}

void Burrobot_State_Moving(void)
{
    RSDK_THIS(Burrobot);

    RSDK.ProcessAnimation(&self->animator);

    self->position.x += self->velocity.x;
    --self->timer;

    bool32 collided = false;
    if (self->direction == FLIP_NONE) {
        collided |= RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, -TO_FIXED(12), TO_FIXED(21), true);
        collided |= RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, -TO_FIXED(12), TO_FIXED(20), true);
        collided |= RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, -TO_FIXED(12), TO_FIXED(19), true);
    }
    else {
        collided |= RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, TO_FIXED(12), TO_FIXED(21), true);
        collided |= RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, TO_FIXED(12), TO_FIXED(20), true);
        collided |= RSDK.ObjectTileCollision(self, Zone->collisionLayers, CMODE_FLOOR, 0, TO_FIXED(12), TO_FIXED(19), true);
    }

    RSDK.ObjectTileGrip(self, Zone->collisionLayers, CMODE_FLOOR, 0, 0, TO_FIXED(20), 8);

    if (!self->timer || !collided) {
        if (!(Zone->timer & 4)) {
            self->velocity.y = -0x40000;
            RSDK.SetSpriteAnimation(Burrobot->aniFrames, 2, &self->animator, true, 0);
            self->state = Burrobot_State_Jumped;
        }
        else {
            self->timer = 60;
            RSDK.SetSpriteAnimation(Burrobot->aniFrames, 1, &self->animator, true, 0);
            self->state = Burrobot_State_Stopped;
        }
    }

    Burrobot_CheckPlayerCollisions();
    Burrobot_CheckOffScreen();
}

void Burrobot_State_Stopped(void)
{
    RSDK_THIS(Burrobot);

    RSDK.ProcessAnimation(&self->animator);

    if (!--self->timer) {
        self->velocity.x = -self->velocity.x;
        self->direction  = self->velocity.x < 0 ? FLIP_NONE : FLIP_X;

        self->timer = 256;
        RSDK.SetSpriteAnimation(Burrobot->aniFrames, 0, &self->animator, true, 0);
        self->state = Burrobot_State_Moving;
    }

    Burrobot_CheckPlayerCollisions();
    Burrobot_CheckOffScreen();
}

#if RETRO_INCLUDE_EDITOR
void Burrobot_EditorDraw(void) { Burrobot_Draw(); }

void Burrobot_EditorLoad(void)
{
    Burrobot->aniFrames = RSDK.LoadSpriteAnimation("LZ/Burrobot.bin", SCOPE_STAGE);

    // RSDK_ACTIVE_VAR(Burrobot, type);

    RSDK_ACTIVE_VAR(Burrobot, direction);
    RSDK_ENUM_VAR("Left", FLIP_NONE);
    RSDK_ENUM_VAR("Right", FLIP_X);
}
#endif

void Burrobot_Serialize(void)
{
    RSDK_EDITABLE_VAR(Burrobot, VAR_UINT8, type);
    RSDK_EDITABLE_VAR(Burrobot, VAR_UINT8, direction);
}
