#include "DOE_Engine.h"

#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public DOE_Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		DOE_Engine::Ref<DOE_Engine::VertexBuffer> m_VertexBuffer;
		DOE_Engine::Ref<DOE_Engine::IndexBuffer> m_IndexBuffer;

		m_VertexArray.reset(DOE_Engine::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
		};
		m_VertexBuffer.reset(DOE_Engine::VertexBuffer::Create(vertices, sizeof(vertices)));

		DOE_Engine::BufferLayout layout = {
			{DOE_Engine::ShaderDataType::Float3, "a_Position"},
			{DOE_Engine::ShaderDataType::Float4, "a_Color"}

		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(DOE_Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);


		m_SquareVA.reset(DOE_Engine::VertexArray::Create());

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f

		};

		std::shared_ptr<DOE_Engine::VertexBuffer> squareVB;
		squareVB.reset(DOE_Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		DOE_Engine::BufferLayout squareVBlayout = {
			{DOE_Engine::ShaderDataType::Float3, "a_Position"},
			{DOE_Engine::ShaderDataType::Float2, "a_TexCoord"}


		};
		squareVB->SetLayout(squareVBlayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareindices[6] = { 0, 1, 2, 2, 3, 0 };
		DOE_Engine::Ref<DOE_Engine::IndexBuffer> squareIB;
		squareIB.reset(DOE_Engine::IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform *  vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}

		)";

		m_Shader = DOE_Engine::Shader::Create("ColorTriangle", vertexSrc, fragmentSrc);


		std::string BlueShaderVertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;


			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string BlueShaderFragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}

		)";
		
		m_BlueShader = DOE_Engine::Shader::Create("FlatColor", BlueShaderVertexSrc, BlueShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("Assets/Shaders/Texture.glsl");

		m_Texture = DOE_Engine::Texture2D::Create("Assets/Textures/space.png");

		std::dynamic_pointer_cast<DOE_Engine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<DOE_Engine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(DOE_Engine::Timestep ts) override
	{
		//DOE_TRACE("DeltaTime: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliSeconds());
		m_CameraController.OnUpdate(ts);
		
		DOE_Engine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
		DOE_Engine::RenderCommand::Clear();


		DOE_Engine::Renderer::BeginScene(m_CameraController.GetCamera());


		std::dynamic_pointer_cast<DOE_Engine::OpenGLShader>(m_BlueShader)->Bind();
		std::dynamic_pointer_cast<DOE_Engine::OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color", m_FlatColor );

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), {1.0,1.0,0.0});

		DOE_Engine::Renderer::Submit(m_BlueShader, m_SquareVA, transform);

		auto textureShader = m_ShaderLibrary.Get("Texture");
		m_Texture->Bind(0);
		DOE_Engine::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5)));

		/*for (int x = 0; x < 10; x++)
		{
			for (int y = 0; y < 10; y++)
			{

			}
		}*/
		// Triangle
		//DOE_Engine::Renderer::Submit(m_Shader, m_VertexArray);

		DOE_Engine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square color", glm::value_ptr(m_FlatColor));

		ImGui::End();
	}

	void OnEvent(DOE_Engine::Event& e) override
	{
		m_CameraController.OnEvent(e);
		/*if (e.GetEventType() == DOE_Engine::EventType::WindowResize)
		{
			auto& re = (DOE_Engine::WindowResizeEvent&)e;
			float zoom = (float)re.GetWidth();
			m_CameraController.SetZoomLevel()
		}*/
	}
private:

	DOE_Engine::ShaderLibrary m_ShaderLibrary;

	DOE_Engine::Ref<DOE_Engine::Shader> m_Shader;

	DOE_Engine::Ref<DOE_Engine::VertexArray> m_VertexArray;

	DOE_Engine::Ref<DOE_Engine::VertexArray> m_SquareVA;
	DOE_Engine::Ref<DOE_Engine::Shader> m_BlueShader;

	DOE_Engine::Ref<DOE_Engine::Shader> m_TextureShader;
	DOE_Engine::Ref<DOE_Engine::Texture2D> m_Texture;

	DOE_Engine::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 1.0;

	glm::vec3 m_FlatColor = { 0.2, 0.3, 0.8 };
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