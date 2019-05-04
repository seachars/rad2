#include "Shutter.h"
#include "Own_Defines.h"

void Shutter_Off(void)
{
	SHUTTEROFF;
}

void Shutter_Stop(void)
{
	SHUTTERSTOP;
}

void Shutter_On(void)
{
	SHUTTERON;
}
