#include "components/PointLightComponent.h"

PointLightComponent::PointLightComponent(Object& InOwner, float Intensity, Color Col) : Component(InOwner)
{
    LightIntensity = Intensity;
    LightColor = Col;
}

void PointLightComponent::Start()
{
}

void PointLightComponent::Update(float DeltaTime)
{
}