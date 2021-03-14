#pragma once

namespace Engine {

	class EOpenGLTexture2D : public ETexture2D
	{
	public:
		EOpenGLTexture2D(const EString& path, bool srgb);
		EOpenGLTexture2D(const EString& name, ETextureFormat format, u32 width, u32 height);

		virtual ~EOpenGLTexture2D();

		virtual u32 GetRendererID() const override { return fRendererID; }
		virtual void Bind(u32 slot) const override;

		virtual ETextureFormat GetFormat() const override { return fFormat; }
		virtual u32 GetHeight() const override { return fHeight; }
		virtual u32 GetWidth() const override { return fWidth; }

		virtual void SetTextureData(byte* pixels, u32 width, u32 height) override;

		virtual bool OnLoad() override;
	private:
		u32 fRendererID;
		ETextureFormat fFormat;
		u32 fWidth;
		u32 fHeight;
		byte* fImageData;
	};

	class EOpenGLTextureCube : public ETextureCube
	{
	public:
		EOpenGLTextureCube(const EString& path, bool srgb = false);

		virtual ~EOpenGLTextureCube();

		virtual u32 GetRendererID() const override { return fRendererID; }
		virtual void Bind(u32 slot) const override;

		virtual ETextureFormat GetFormat() const override { return fFormat; }
		virtual u32 GetHeight() const override { return fHeight; }
		virtual u32 GetWidth() const override { return fWidth; }

		virtual bool OnLoad() override;
	private:
		u32 fRendererID;
		ETextureFormat fFormat;
		u32 fWidth;
		u32 fHeight;
		byte* fImageData;
	};

}
