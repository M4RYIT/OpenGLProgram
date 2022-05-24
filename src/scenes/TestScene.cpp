#include "scenes\TestScene.h"

#include "Mesh.h"
#include "Object.h"
#include "components\RenderComponent.h"
#include "shaders\SimpleShader.h"
#include "shaders\IndexShader.h"
#include "shaders\ColorMulShader.h"
#include "singletons\Settings.h"
#include "singletons\Renderer.h"
#include <glad\glad.h>

void TestScene::Init()
{
    const WindowData& WinData = Settings::Get().WinData;
    Renderer::Get().SetViewport(0, 0, WinData.Width, WinData.Height);
    Renderer::Get().SetBackgroundColor(0.f, 0.f, 0.f, 1.f);

    ColorMulQuad();
}

void TestScene::SimpleTriangle()
{
    Mesh triangleMesh;
    triangleMesh.VertsPosition = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
        0.0f, 0.5f,  0.0f //top
    };

    Object* TriangleObj = new Object();
    TriangleObj->AddComponent(new RenderComponent(*TriangleObj, new SimpleShader(), triangleMesh));
    Objects.push_back(TriangleObj);
}

void TestScene::SimpleIndexQuad()
{
    Mesh QuadMesh;
    QuadMesh.VertsPosition = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, //top left
        0.5f,  0.5f, 0.0f  //top right
    };

    QuadMesh.VertsIndex = 
    {
        1, 0, 3, //right triangle
        1, 3, 2  //right triangle
    };

    Object* QuadObj = new Object();
    QuadObj->AddComponent(new RenderComponent(*QuadObj, new IndexShader(), QuadMesh));
    Objects.push_back(QuadObj);
}

void TestScene::ColorMulQuad()
{
    Mesh QuadMesh;
    QuadMesh.VertsPosition = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, //top left
        0.5f,  0.5f, 0.0f  //top right
    };

    QuadMesh.VertsColors =
    {
        1.0f, 0.f, 0.f,
        0.f, 1.0f, 0.f,
        0.f, 0.f, 1.0f,
        0.f, 1.0f, 1.0f
    };

    QuadMesh.VertsIndex = 
    {
        1, 0, 3, //right triangle
        1, 3, 2  //right triangle
    };

    Object* QuadObj = new Object();
    RenderComponent* RndComp = new RenderComponent(*QuadObj, new ColorMulShader(), QuadMesh);
    
    // std::vector<float> BaseColor = {1.0f, 1.0f, 0.f, 1.0f};
    // SET_VECTOR(RndComp->RenderMaterial.Id(), base_color, 4fv, (GLfloat*)BaseColor.data());

    QuadObj->AddComponent(RndComp);
    Objects.push_back(QuadObj);
}