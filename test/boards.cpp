#include <stdio.h>
#include <raspboop/Raspboop.h>

using raspboop::L298N;

int main(int argc, char* argv[])
{

#define IN1 23
#define IN2 24
#define IN3 3
#define IN4 4


	raspboop::Init(0);
	L298N* Controller = L298N::Create(IN1, IN2, IN3, IN4);

	Controller->UseSoftPWM();

	Controller->SetPWMValue(1, 50);
	Controller->SetPWMValue(4, 50);

	delete Controller;

	return 0;
}
