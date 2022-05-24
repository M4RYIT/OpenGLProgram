#include "Object.h"
#include "components\Component.h"

void Object::AddComponent(Component* Component)
{
    Components.push_back(Component);
}

Object::~Object()
{
    Components.clear();
}

void Object::Start()
{
    for (Component*& Component : Components)
    {
        Component->Start();
    }
}

void Object::Update(float DeltaTime)
{
    for (Component*& Component : Components)
    {
        Component->Update(DeltaTime);
    }
}