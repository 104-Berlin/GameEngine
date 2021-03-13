#pragma once

namespace Engine {


	enum class ETextureFormat
	{
		None = 0,
		RGB = 1,
		RGBA = 2
	};

	class E_API ETexture : public EResource
	{
	public:
		ETexture(const EString& filePath) : EResource(filePath) {}
		virtual ~ETexture() {  }

		virtual void Bind(u32 slot) const = 0;
		
		virtual ETextureFormat GetFormat() const = 0;
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		virtual u32 GetRendererID() const = 0;
		
		virtual void SetTextureData(byte* pixels, u32 width, u32 height) {}

		virtual bool OnLoad() = 0;
	};

	class E_API ETexture2D : public ETexture
	{
	public:
		ETexture2D(const EString& filePath) : ETexture(filePath) {}

		static ERef<ETexture2D> Create(const EString& path, bool srgb = false);
		static ERef<ETexture2D> Create(ETextureFormat format, u32 width, u32 height);
	};

	class E_API ETextureCube : public ETexture
	{
	public:
		ETextureCube(const EString& filePath) : ETexture(filePath) {}

		static ERef<ETextureCube> Create(const EString& path, bool srgb = false);
	};




// Load Function for resource manager
ERef<ETexture2D> Engine_LoadTextureFromFileBuffer(EString name, ESharedBuffer fileBuffer);

}
