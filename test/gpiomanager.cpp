#include "raspboop/Raspboop.h"

using raspboop::GPIOManager;
using raspboop::HCSR04;
using raspboop::HCSR501;

int main(int argc, char* argv[])
{
    
#define SIG 6
#define TRIG 4
#define ECHO 5
#define MISC 7
    
    raspboop::Init();
    
    GPIOManager* manager = GPIOManager::Create();
    
    manager->AddConsumer(HCSR04::Create(TRIG, ECHO));
    manager->AddConsumer(HCSR501::Create(SIG));
    
    manager->ConsumePin(MISC, INPUT);
    
    // We only need to delete manager
    delete manager;
    
    return 0;
}
