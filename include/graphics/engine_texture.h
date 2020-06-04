#pragma once

namespace Engine {

	enum class ETextureFormat
	{
		None = 0,
		RGB = 1,
		RGBA = 2
	};

	class ETexture : public Resource
	{
	public:
		ETexture(const EString& filePath, const EString& name = "Unknown") : Resource(name, filePath) {}
		virtual ~ETexture() {  }

		virtual void Bind(u32 slot) const = 0;
		
		virtual ETextureFormat GetFormat() const = 0;
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		virtual u32 GetRendererID() const = 0;
		

		virtual bool Reload(const EString& filePath) = 0;

		virtual const EString& GetPath() const = 0;
	};

	class ETexture2D : public ETexture
	{
	public:
		ETexture2D(const EString& filePath, const EString& name = "Unknown") : ETexture(filePath, name) {}

		static ETexture2D* Create(const EString& path, bool srgb = false);
		static ETexture2D* Create(ETextureFormat format, u32 width, u32 height);
	};

	class ETextureCube : public ETexture
	{
	public:
		ETextureCube(const EString& filePath, const EString& name = "Unknown") : ETexture(filePath, name) {}

		static ETextureCube* Create(const EString& path, bool srgb = false);
	};

}
