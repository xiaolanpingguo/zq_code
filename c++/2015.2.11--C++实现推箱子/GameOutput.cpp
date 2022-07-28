#include "GameOutput.h"
#include <iostream>
#include "Render.h"
void CGameOutput::GamePrint(CRender* render)
{
	std::cout<<render->GetRender();
}