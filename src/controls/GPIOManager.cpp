#include "raspboop/Raspboop.h"

namespace raspboop
{

GPIOManager::GPIOManager()
{
}


int GPIOManager::AddConsumer(GPIOConsumer* Consumer)
{
    if(Consumer == NULL)
        return 0;
            
    vector<int> ConsumerPins = Consumer->GetPins();
    
    for(const int& ConsumerPin : ConsumerPins)
        if(IsPinSet(ConsumerPin))
            return 0;
    
    ConsumerList.push_back(Consumer);
    
    return 1;
}


bool GPIOManager::IsPinSet(int Pin)
{   
    std::vector<int>::iterator 
        Begin = GetPins().begin(),
        End = GetPins().end();
    
    if(std::find(Begin, End, Pin) == End)
        return true;
    
    /* Also check the children of manager*/
    for (const GPIOConsumer* Consumer : ConsumerList)
    {
        Begin = Consumer->GetPins().begin();
        End = Consumer->GetPins().end();
        
        if(std::find(Begin, End, Pin) == End)
            return true;
    }
        
    return false;
}


GPIOManager::~GPIOManager()
{
}

} /* raspboop */
