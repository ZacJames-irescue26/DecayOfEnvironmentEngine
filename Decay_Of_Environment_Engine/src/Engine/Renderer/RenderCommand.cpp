#include "pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace DOE_Engine
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}