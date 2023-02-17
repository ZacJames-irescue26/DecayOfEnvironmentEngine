#pragma once

#include "Engine/Renderer/Buffer.h"

namespace DOE_Engine
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetLayout(const BufferLayout& layout) override
		{
			m_Layout = layout;
		}
		virtual const BufferLayout GetLayout() override
		{
			return m_Layout;
		}

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indicies, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const {return m_Count;}
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}