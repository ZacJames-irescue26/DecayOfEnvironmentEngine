#include "DOE_Engine.h"
#include "glm/glm.hpp"

class ExampleLayer : public DOE_Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.0, 1.0, -1.0, 1.0)
	{
		std::shared_ptr<DOE_Engine::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<DOE_Engine::IndexBuffer> m_IndexBuffer;

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

		float squareVertices[3 * 4] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f

		};

		std::shared_ptr<DOE_Engine::VertexBuffer> squareVB;
		squareVB.reset(DOE_Engine::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		DOE_Engine::BufferLayout squareVBlayout = {
			{DOE_Engine::ShaderDataType::Float3, "a_Position"}

		};
		squareVB->SetLayout(squareVBlayout);

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareindices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<DOE_Engine::IndexBuffer> squareIB;
		squareIB.reset(DOE_Engine::IndexBuffer::Create(squareindices, sizeof(squareindices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new DOE_Engine::Shader(vertexSrc, fragmentSrc));


		std::string BlueShaderVertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			uniform mat4 u_ViewProjection;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string BlueShaderFragmentSrc2 = R"(
			#version 450 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}

		)";

		m_BlueShader.reset(new DOE_Engine::Shader(BlueShaderVertexSrc, BlueShaderFragmentSrc2));
	}

	void OnUpdate() override
	{
		if (DOE_Engine::Input::IsKeyPressed(DOE_Engine::Key::A))
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}
		if (DOE_Engine::Input::IsKeyPressed(DOE_Engine::Key::D))
		{
			m_CameraPosition.x += m_CameraSpeed;
		}
		if (DOE_Engine::Input::IsKeyPressed(DOE_Engine::Key::S))
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}
		if (DOE_Engine::Input::IsKeyPressed(DOE_Engine::Key::W))
		{
			m_CameraPosition.y += m_CameraSpeed;
		}
		DOE_Engine::RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1.0 });
		DOE_Engine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);

		DOE_Engine::Renderer::BeginScene(m_Camera);

		DOE_Engine::Renderer::Submit(m_BlueShader, m_SquareVA);
		DOE_Engine::Renderer::Submit(m_Shader, m_VertexArray);

		DOE_Engine::Renderer::EndScene();
	}
	void OnEvent(DOE_Engine::Event& event) override
	{
		
	}
private:
	std::shared_ptr<DOE_Engine::Shader> m_Shader;

	std::shared_ptr<DOE_Engine::VertexArray> m_VertexArray;

	std::shared_ptr<DOE_Engine::VertexArray> m_SquareVA;
	std::shared_ptr<DOE_Engine::Shader> m_BlueShader;

	DOE_Engine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1;
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