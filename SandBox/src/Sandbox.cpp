#include "DOE_Engine.h"
#include "glm/glm.hpp"

class ExampleLayer : public DOE_Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
	
	}
	void OnEvent(DOE_Engine::Event& event) override
	{
		/*DOE_TRACE("{0}", event);*/
	}
};

class Sandbox : public DOE_Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

DOE_Engine::Application* DOE_Engine::createApplication()
{
	return new Sandbox();
}