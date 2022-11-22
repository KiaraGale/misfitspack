#include "Misfits.h"

#include "All.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void)
{
    // Get Public Functions
    Player_CheckBadnikTouch = Mod.GetPublicFunction(NULL, "Player_CheckBadnikTouch");
    Player_CheckBadnikBreak = Mod.GetPublicFunction(NULL, "Player_CheckBadnikBreak");
    SpearBlock_State_SpearRetracted = Mod.GetPublicFunction(NULL, "SpearBlock_State_SpearRetracted");
    SpearBlock_State_SpearExtended  = Mod.GetPublicFunction(NULL, "SpearBlock_State_SpearExtended");

    // Register State Hooks
    Mod.RegisterStateHook(SpearBlock_State_SpearRetracted, SpearBlock_State_SpearRetracted_Hook, true);
    Mod.RegisterStateHook(SpearBlock_State_SpearExtended, SpearBlock_State_SpearExtended_Hook, true);

    // Register Object Hooks
    MOD_REGISTER_OBJECT_HOOK(Player);
    MOD_REGISTER_OBJECT_HOOK(Zone);
    MOD_REGISTER_OBJECT_HOOK(DebugMode);

    // Register Inherited Objects
    MOD_REGISTER_OBJ_OVERLOAD_MSV(SpearBlock, Mod_SpearBlock, NULL, NULL, NULL, NULL, NULL, SpearBlock_StageLoad, NULL, NULL, NULL);
    
    MOD_REGISTER_OBJ_OVERLOAD(Orbinaut, NULL, NULL, NULL, NULL, NULL, Orbinaut_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(SwingRope, NULL, NULL, NULL, NULL, NULL, SwingRope_StageLoad, NULL, NULL, NULL);
    MOD_REGISTER_OBJ_OVERLOAD(Stalactite, NULL, NULL, NULL, NULL, NULL, Stalactite_StageLoad, NULL, NULL, NULL);

    // Register New Objects
    MOD_REGISTER_OBJECT(Burrobot, NULL, Burrobot_Update, NULL, NULL, Burrobot_Draw, Burrobot_Create, Burrobot_StageLoad, Burrobot_EditorDraw, Burrobot_EditorLoad, Burrobot_Serialize);
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id)
{
#if MANIA_USE_PLUS
    LinkGameLogicDLL(info);
#else
    LinkGameLogicDLL(*info);
#endif

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif