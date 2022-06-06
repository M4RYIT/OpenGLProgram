#include "scenes\Scene.h"

#include "Object.h"

Scene::Scene(int X, int Y, int W, int H) 
: ViewportPos{X, Y}, ViewportSize{W, H}
{

}

Scene::~Scene()
{
    Objects.clear();
}

void Scene::Start()
{
    for (Object*& Obj : Objects)
    {
        Obj->Start();
    }
}

void Scene::Update(float DeltaTime)
{
    for (Object*& Obj : Objects)
    {
        Obj->Update(DeltaTime);
    }
}