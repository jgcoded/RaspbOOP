#include <stdio.h>
#include <raspboop/Raspboop.h>

using raspboop::HCSR04;
using raspboop::HCSR501;

int main(int argc, char* argv[])
{

#define SIG 6
#define TRIG 4
#define ECHO 5

    raspboop::Init(raspboop::WIRING);

    bool ShouldRun = true;
    HCSR04* DistanceSensor = HCSR04::Create(ECHO, TRIG);
    HCSR501* InfraredSensor = HCSR501::Create(SIG);

    while(ShouldRun)
    {

        InfraredSensor->Sense();
        DistanceSensor->Sense();

        int Motion = InfraredSensor->IsSignalled();
        float Distance = DistanceSensor->GetDistance();

        printf("Motion Detected: %d\n", Motion);
        printf("Distance: %0.2f centimeters\n\n", Distance);

        if(Distance < 20.0f)
            ShouldRun = false;
        else
            delay(1000);
    }

    delete InfraredSensor;
    delete DistanceSensor;

    return 0;
}
