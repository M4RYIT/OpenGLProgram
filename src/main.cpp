#include "singletons\Settings.h"
#include "Window.h"
#include "scenes\TestScene.h"
#include "singletons\Renderer.h"

int main() 
{
	Settings::Init();

	Window* Win = Window::NewWindow();

	TestScene* Scene = new TestScene();	
	Scene->Init();
	Scene->Start();

	while(Win->IsOpen())
	{
		Scene->Update(Win->GetDeltaTime());
		Renderer::Get().Update(Win->GetDeltaTime());

		Win->Update();
	}

	delete Scene;
	delete Win;

	return 0;	
}