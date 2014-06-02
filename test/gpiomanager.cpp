#include "raspboop/Raspboop.h"

using raspboop::WiringPiPins;
using raspboop::GPIOManager;
using raspboop::HCSR04;

int main(int argc, char* argv[])
{
    
    raspboop::Init();
    
    GPIOManager* manager = GPIOManager::Create();
    HCSR04* DistanceSensor = HCSR04::Create(WiringPiPins::GPIO0,
                                           WiringPiPins::GPIO1);
    
    manager->AddConsumer(DistanceSensor);
    
    manager->ConsumePin(WiringPiPins::GPIO3, INPUT);
    
    // We only need to delete manager; manager deletes other consumers
    delete manager;
    
    return 0;
}
