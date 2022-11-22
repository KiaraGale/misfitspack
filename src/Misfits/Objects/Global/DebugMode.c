#include "DebugMode.h"

ObjectDebugMode* DebugMode;


void DebugMode_AddObject(uint16 id, void (*draw)(void), void (*spawn)(void)) {
	void (*AddObject)(uint16 id, void (*draw)(void), void (*spawn)(void)) = Mod.GetPublicFunction(NULL, "DebugMode_AddObject");

	if (AddObject)
		AddObject(id, draw, spawn);
}