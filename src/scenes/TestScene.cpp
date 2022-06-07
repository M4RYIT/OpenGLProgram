#include "scenes\TestScene.h"

#include "Camera.h"
#include "Color.h"
#include "Mesh.h"
#include "Object.h"
#include "components\PointLightComponent.h"
#include "components\RenderComponent.h"
#include "components\RotatorComponent.h"
#include "shaders\SimpleShader.h"
#include "shaders\IndexShader.h"
#include "shaders\ColorMulShader.h"
#include "shaders\MvpPhongShader.h"
#include "shaders\TexBlendShader.h"
#include "shaders\TexProjRotShader.h"
#include "shaders\TexProjShader.h"
#include "singletons\Settings.h"
#include "singletons\Renderer.h"
#include <glad\glad.h>
#include "utils/obj_parser.h"

TestScene::TestScene() : Scene()
{
}

TestScene::TestScene(int X, int Y, int W, int H) : Scene(X, Y, W, H)
{    
}

void TestScene::Init()
{
    Renderer::Get().SetViewport(ViewportPos[0], ViewportPos[1], ViewportSize[0], ViewportSize[1]);
    Renderer::Get().SetBackgroundColor(0.5f, 0.5f, 0.5f, 1.f);
    Cam = new Camera();
    MvpPhong();
}

void TestScene::SimpleTriangle()
{
    Mesh triangleMesh;
    triangleMesh.Vertices = 
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
    QuadMesh.Vertices = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, //top left
        0.5f,  0.5f, 0.0f  //top right
    };

    QuadMesh.Indices = 
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
    QuadMesh.Vertices = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, //top left
        0.5f,  0.5f, 0.0f  //top right
    };

    QuadMesh.Indices = 
    {
        1, 0, 3, //right triangle
        1, 3, 2  //right triangle
    };

    Object* QuadObj = new Object();
    ColorMulShader* CololrMulSh = new ColorMulShader();
    CololrMulSh->BaseColor = {1.f, 0.f, 0.f, 1.f};
    CololrMulSh->VertsColors = 
    {
        1.f, 0.f, 0.f,
        0.f, 1.f, 0.f,
        0.f, 0.f, 1.f,
        0.f, 1.f, 0.f
    };

    RenderComponent* RndComp = new RenderComponent(*QuadObj, CololrMulSh, QuadMesh);

    QuadObj->AddComponent(RndComp);
    Objects.push_back(QuadObj);
}

void TestScene::TexBlend()
{
    Mesh QuadMesh;
    QuadMesh.Vertices = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, //top left
        0.5f,  0.5f, 0.0f  //top right
    };

    QuadMesh.Indices = 
    {
        0, 1, 2, //right triangle
        2, 3, 0  //right triangle
    };

    QuadMesh.UVs =
    {
        1.f, 0.f,
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f 
    };

    Object* QuadObj = new Object();
    TexBlendShader* TexBlendSh = new TexBlendShader();
    TexBlendSh->BaseColor = {1.f, 0.f, 0.f, 1.f};
    TexBlendSh->Tex1 = Shader::CreateTexture("resources/textures/smile.png");
    TexBlendSh->Tex2 = Shader::CreateTexture("resources/textures/wood-box.jpg");

    RenderComponent* RndComp = new RenderComponent(*QuadObj, TexBlendSh, QuadMesh);

    QuadObj->AddComponent(RndComp);
    Objects.push_back(QuadObj);
}

void TestScene::TexProj()
{
    Mesh QuadMesh;
    QuadMesh.Vertices = 
    {
        0.5f, -0.5f, 0.0f, //bottom right
       -0.5f, -0.5f, 0.0f, //bottom left
       -0.5f,  0.5f, 0.0f, //top left
        0.5f,  0.5f, 0.0f  //top right
    };

    QuadMesh.Indices = 
    {
        0, 1, 2, //right triangle
        2, 3, 0  //right triangle
    };

    QuadMesh.UVs =
    {
        1.f, 0.f,
        0.f, 0.f,
        0.f, 1.f,
        1.f, 1.f 
    };

    Object* QuadObj = new Object();
    TexProjShader* TexBlendSh = new TexProjShader();
    TexBlendSh->BaseColor = {1.f, 0.f, 0.f, 1.f};
    TexBlendSh->Tex1 = Shader::CreateTexture("resources/textures/smile.png");
    TexBlendSh->Tex2 = Shader::CreateTexture("resources/textures/wood-box.jpg");

    RenderComponent* RndComp = new RenderComponent(*QuadObj, TexBlendSh, QuadMesh);

    QuadObj->AddComponent(RndComp);
    Objects.push_back(QuadObj);
}

void TestScene::TexProjRot()
{
    Mesh CubeMesh;
    ParseObj("resources/models/cube_no_norm.obj", CubeMesh);

    Object* CubeObj = new Object();
    CubeObj->Tr.Position[2] += 5.f;

    TexProjRotShader* TexProjRotSh = new TexProjRotShader();
    TexProjRotSh->AspectRatio = (float)ViewportSize[0] / (float)ViewportSize[1];
    TexProjRotSh->Cam = Cam;
    TexProjRotSh->Obj = CubeObj;
    TexProjRotSh->Tex = Shader::CreateTexture("resources/textures/wood-box.jpg");

    RenderComponent* RndComp = new RenderComponent(*CubeObj, TexProjRotSh, CubeMesh);

    RotatorComponent* RotComp = new RotatorComponent(*CubeObj, 0.f, 20.f, 0.f);

    CubeObj->AddComponent(RndComp);
    CubeObj->AddComponent(RotComp);

    Objects.push_back(CubeObj);
}

void TestScene::MvpPhong()
{
    Object* LightObj = new Object();
    LightObj->Tr.Position[1] += 4.f;

    Color LightCol = {1.f, 1.f, 1.f, 1.f};
    PointLightComponent* LightComp = new PointLightComponent(*LightObj, 10.f, LightCol);
    LightObj->AddComponent(LightComp);

    Mesh Mesh;
    ParseObj("resources/models/stormtrooper.obj", Mesh);

    Object* Obj = new Object();
    Obj->Tr.Position[1] -= 2.f;
    Obj->Tr.Position[2] += 3.f;

    MvpPhongShader* MvpPhongSh = new MvpPhongShader();
    MvpPhongSh->AspectRatio = (float)ViewportSize[0] / (float)ViewportSize[1];
    MvpPhongSh->Cam = Cam;
    MvpPhongSh->Obj = Obj;
    MvpPhongSh->Tex = Shader::CreateTexture("resources/models/stormtrooper.png");
    MvpPhongSh->AmbientFactor = 0.2f;
    MvpPhongSh->SpecularFactor = 40.f;
    MvpPhongSh->PointLight = LightComp;

    RenderComponent* RndComp = new RenderComponent(*Obj, MvpPhongSh, Mesh);
    Obj->AddComponent(RndComp);

    Objects.push_back(LightObj);
    Objects.push_back(Obj);
}