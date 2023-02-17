#include "pch.h"
#include "Engine/Core/Core.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace DOE_Engine
{

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DOE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}
		DOE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: DOE_CORE_ASSERT(false, "RendererAPI::None is not supported"); return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}
		DOE_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}