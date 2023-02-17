#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace DOE_Engine
{

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None: DOE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		}
		DOE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;

	}

}