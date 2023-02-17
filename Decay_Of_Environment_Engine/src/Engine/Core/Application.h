#pragma once
#include "Core.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Core/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"

#include "Window.h"

namespace DOE_Engine
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window;}
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_BlueShader;


		static Application* s_Instance;

	};

	Application* createApplication();
}