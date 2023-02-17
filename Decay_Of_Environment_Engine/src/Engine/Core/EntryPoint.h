#pragma once

extern DOE_Engine::Application* DOE_Engine::createApplication();

int main(int argc, char** argv)
{
	DOE_Engine::Log::Init();
	DOE_CORE_WARN("Initilized Log");
	auto app = DOE_Engine::createApplication();

	app->Run();

	delete app;
}