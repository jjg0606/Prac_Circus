#pragma once
#include "ProgramCore.h"
#include "CircusScene.h"

// need library msimg32.lib



//Code here to Main
void ProgramCore::Init()
{
	ProgramCore::instance.ChangeScene(new CircusScene());
}