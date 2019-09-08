#include "GameObject.h"
#include "ProgramCore.h"

using namespace std;

bool GameObject::GetKey(WPARAM keyName)
{
	return ProgramCore::instance.GetKey(keyName);
}

float GameObject::getDeltaTime()
{
	return ProgramCore::instance.getDeltaTime();
}
