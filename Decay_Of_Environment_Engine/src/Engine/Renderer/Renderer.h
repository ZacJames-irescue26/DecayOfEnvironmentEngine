#pragma once

#include "RenderCommand.h"

namespace DOE_Engine
{


	class Renderer
	{
	public:

		static void BeginScene();

		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}
	private:

	};
}