#include "components/RotatorComponent.h"

#include "Object.h"

RotatorComponent::RotatorComponent(Object& InOwner, float RotX, float RotY, float RotZ) : Component(InOwner)
{
    RotStep = {RotX, RotY, RotZ};
}

RotatorComponent::~RotatorComponent()
{
    RotStep.clear();
}

void RotatorComponent::Start()
{
}

void RotatorComponent::Update(float DeltaTime)
{
    Owner.Tr.Rotation[0] += RotStep[0] * DeltaTime;
    Owner.Tr.Rotation[1] += RotStep[1] * DeltaTime;
    Owner.Tr.Rotation[2] += RotStep[2] * DeltaTime;
}