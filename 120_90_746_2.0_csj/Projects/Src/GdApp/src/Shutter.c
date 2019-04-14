#include "Shutter.h"
#include "Own_Defines.h"

void Shutter_Off(void)
{
	SHUTTERON;
}

void Shutter_Stop(void)
{
	SHUTTERSTOP;
}

void Shutter_On(void)
{
	SHUTTEROFF;
}
