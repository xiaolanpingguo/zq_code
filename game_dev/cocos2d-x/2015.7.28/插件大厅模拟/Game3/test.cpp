#include "GameClass.h"
#include <iostream>
#include <windows.h>

class Game3 : public CGameClass
{
public:
	virtual const char* name()
	{
		return "“Ù¿÷£°";
	}
	virtual void init()
	{
		
	}
	virtual void run()
	{
		Beep(200, 500);
		Beep(250, 500);
		Beep(300, 500);
		Beep(350, 500);
		Beep(400, 500);
		Beep(450, 500);
	}
	virtual void end()
	{
		
	}
};

__declspec(dllexport) CGameClass* getGame()
{
	return new Game3;
}