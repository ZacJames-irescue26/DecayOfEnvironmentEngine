#include "pch.h"
#include "ImGuiLayer.h"
#include "Engine/Core/Application.h"

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace DOE_Engine
{

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
		
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{

	}


	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// find out why imgui wont link properly
		if (io.ConfigFlags /*& ImGuiConfigFlags_ViewportsEnable*/)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			/*ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();*/
			glfwMakeContextCurrent(backup_current_context);
		}


	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}