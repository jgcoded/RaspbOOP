#include <raspboop/Raspboop.h>

using namespace rbp;

int main(int argc, char* argv[])
{
    rbp::Init();

    bool ShouldRun = true;
    HCSR04* DistanceSensor = HCSR04::Create(WiringPiPins::GPIO0,
                                            WiringPiPins::GPIO1);

    HCSR501* InfraredSensor = HCSR501::Create(WiringPiPins::GPIO2);

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
