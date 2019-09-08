#include "Renderer.h"
#include "ProgramCore.h"

HDC Renderer::getMemDC()
{
	return ProgramCore::instance.getMemDC();
}
