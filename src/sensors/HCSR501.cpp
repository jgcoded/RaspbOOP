#include "raspboop/Raspboop.h"

namespace raspboop
{

HCSR501::HCSR501()
{
	SignalPin = -1;
	Signalled = false;
}

HCSR501* HCSR501::Create(int SIGNAL)
{
	HCSR501* H = (HCSR501*)malloc(sizeof(HCSR501));

	// Not enough memory. Should notify user
	if(H == NULL)
		return NULL;

	new(H) HCSR501;

	H->SignalPin = SIGNAL;

	H->SetInputPin(SIGNAL);

	return H;
}

void HCSR501::Sense()
{
	Signalled = digitalRead(SignalPin);
}

void HCSR501::ReleasePins()
{
}

HCSR501::~HCSR501()
{
	ReleasePins();
}

} /* raspboop */
