﻿#pragma once

#include <string>

#include "Blaze/Core/Core.h"

namespace Blaze
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual void Bind(uint32_t slot = 0) const = 0;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
	};
}
