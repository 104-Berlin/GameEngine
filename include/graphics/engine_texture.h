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

		virtual void Bind(uint slot) const = 0;
		
		virtual ETextureFormat GetFormat() const = 0;
		virtual uint GetWidth() const = 0;
		virtual uint GetHeight() const = 0;
		virtual uint GetRendererID() const = 0;
		

		virtual bool Reload(const EString& filePath) = 0;

		virtual const EString& GetPath() const = 0;
	};

	class ETexture2D : public ETexture
	{
	public:
		ETexture2D(const EString& filePath, const EString& name = "Unknown") : ETexture(filePath, name) {}

		static ETexture2D* Create(const EString& path, bool srgb = false);
		static ETexture2D* Create(ETextureFormat format, uint width, uint height);
	};

	class ETextureCube : public ETexture
	{
	public:
		ETextureCube(const EString& filePath, const EString& name = "Unknown") : ETexture(filePath, name) {}

		static ETextureCube* Create(const EString& path, bool srgb = false);
	};

}
