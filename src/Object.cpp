#include "Object.h"
#include "components\Component.h"

void Object::AddComponent(Component* Component)
{
    Components.push_back(Component);
}

Object::Object()
{
    Tr.Position = {0.f, 0.f, 0.f};
    Tr.Rotation = {0.f, 0.f, 0.f};
    Tr.Scale = {1.f, 1.f, 1.f};
}

Object::Object(Transform InTransform) : Tr(InTransform)
{
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