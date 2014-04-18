#include "raspboop/Raspboop.h"

namespace raspboop
{

GPIOManager::GPIOManager()
{
}


GPIOManager* GPIOManager::Create()
{
    GPIOManager* G;
    
    G = (GPIOManager*)malloc(sizeof(GPIOManager));
    
    if(G == NULL)
        return NULL;
    
    new (G) GPIOManager;
    
    return G;
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


bool GPIOManager::IsPinSet(int Pin) const
{   
    std::vector<int>::const_iterator
        Begin = GetPins().begin(),
        End = GetPins().end();
    
    if(std::find(Begin, End, Pin) == End)
        return true;
    
    /* Also check the children of manager */
    for (const GPIOConsumer* Consumer : ConsumerList)
    {
        Begin = Consumer->GetPins().begin();
        End = Consumer->GetPins().end();
        
        if(std::find(Begin, End, Pin) == End)
            return true;
    }
        
    return false;
}


int GPIOManager::ConsumePin(int Pin, int Mode)
{
    if(IsPinSet(Pin))
        return 0;
    
    GPIOConsumer::ConsumePin(Pin, Mode);
    
    return 1;
}


GPIOManager::~GPIOManager()
{
    for(GPIOConsumer* C : ConsumerList)
    {
        delete C;
        C = NULL;
    }
}

} /* raspboop */
