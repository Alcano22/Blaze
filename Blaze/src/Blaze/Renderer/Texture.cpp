#include "blzpch.h"
#include "Texture.h"

#include "Blaze/Core/Log.h"

#include "Blaze/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Blaze
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BLZ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		}

		BLZ_CORE_ASSERT(false, "Unknown RendererAPI!")
		return nullptr;
	}

}