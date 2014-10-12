#include <raspboop/Raspboop.h>
#include <iostream>

using namespace rbp;
using namespace std;

int main(int argc, char* argv[])
{
    rbp::Init();

    bool shouldRun = true;
    HCSR04 distanceSensor(WiringPiPins::GPIO0,
                          WiringPiPins::GPIO1);

    HCSR501 infraredSensor(WiringPiPins::GPIO2);

    while(shouldRun)
    {

        infraredSensor.Sense();
        distanceSensor.Sense();

        bool motion = infraredSensor.IsSignalled();
        float distance = distanceSensor.GetDistance();

        cout << "Motion Detected: " << motion << endl;
        cout << "Distance: " << distance << " cm" << endl << endl;

        if(distance < 20.0f)
            shouldRun = false;
        else
            delay(1000);
    }

    return 0;
}
