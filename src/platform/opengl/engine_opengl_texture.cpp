#include "Engine.h"

#define STB_IMAGE_IMPLEMENTATION
#include "util/stb_image.h"


namespace Engine {

	static GLenum InfinitToOpenGLTextureFormat(ETextureFormat format)
	{
		switch (format)
		{
		case ETextureFormat::RGB:     return GL_RGB;
		case ETextureFormat::RGBA:    return GL_RGBA;
		case ETextureFormat::None:	  break;
		}
		return 0;
	}

	static int CalculateMipMapCount(int width, int height)
	{
		int levels = 1;
		while ((width | height) >> levels) {
			levels++;
		}
		return levels;
	}

	//Remove srgb??
	EOpenGLTexture2D::EOpenGLTexture2D(const EString& path, bool srgb)
		: ETexture2D(path)
	{
	}

	EOpenGLTexture2D::EOpenGLTexture2D(ETextureFormat format, u32 width, u32 height)
		: ETexture2D(""), fFormat(format), fWidth(width), fHeight(height)
	{
		IN_RENDER_S({
			glCall(glGenTextures(1, &self->fRendererID));
			glCall(glBindTexture(GL_TEXTURE_2D, self->fRendererID));

			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			glCall(glTexImage2D(GL_TEXTURE_2D, 0, InfinitToOpenGLTextureFormat(self->fFormat), self->fWidth, self->fHeight, 0, InfinitToOpenGLTextureFormat(self->fFormat), GL_UNSIGNED_BYTE, NULL));
			glCall(glGenerateMipmap(GL_TEXTURE_2D));

			glCall(glBindTexture(GL_TEXTURE_2D, 0));
		})
	}

	bool EOpenGLTexture2D::OnLoad()
	{
		int width, height, channels;
		std::cout << "Loading texture " << GetName() << std::endl;
		stbi_set_flip_vertically_on_load(false);
		fImageData = stbi_load(GetFilePath().c_str(), &width, &height, &channels, STBI_rgb_alpha);

		fWidth = width;
		fHeight = height;
		fFormat = ETextureFormat::RGBA;

		IN_RENDER_S({

				glCall(glGenTextures(1, &self->fRendererID));
				glCall(glBindTexture(GL_TEXTURE_2D, self->fRendererID));

				glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
				glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
				glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
				glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

				glCall(glTexImage2D(GL_TEXTURE_2D, 0, InfinitToOpenGLTextureFormat(self->fFormat), self->fWidth, self->fHeight, 0, InfinitToOpenGLTextureFormat(self->fFormat), GL_UNSIGNED_BYTE, self->fImageData));
				glCall(glGenerateMipmap(GL_TEXTURE_2D));

				glCall(glBindTexture(GL_TEXTURE_2D, 0));

				stbi_image_free(self->fImageData);
			})
		return true;
	}

	EOpenGLTexture2D::~EOpenGLTexture2D()
	{
		std::cout << "OpenGL Texture detroyed!" << std::endl;
		IN_RENDER_S({
				glCall(glDeleteTextures(1, &self->fRendererID));
			})
	}

	void EOpenGLTexture2D::Bind(u32 slot) const
	{
		IN_RENDER_S1(slot, {
				glCall(glActiveTexture(GL_TEXTURE0 + slot));
				glCall(glBindTexture(GL_TEXTURE_2D, self->fRendererID));
			})

	}

//REMOVE srgb??
	EOpenGLTextureCube::EOpenGLTextureCube(const EString& path, bool srgb)
		: ETextureCube(path), fWidth(0), fHeight(0)
	{
	}

	bool EOpenGLTextureCube::OnLoad()
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(false);
		fImageData = stbi_load(GetFilePath().c_str(), &width, &height, &channels, STBI_rgb);

		fWidth = width;
		fHeight = height;
		fFormat = ETextureFormat::RGB;

		unsigned int faceWidth = fWidth / 4;
		unsigned int faceHeight = fHeight / 3;
		//IN_CORE_ASSERT(faceWidth == faceHeight, "Non-square faces!");

		unsigned char** faces = new unsigned char*[6];
		for (size_t i = 0; i < 6; i++)
			faces[i] = new unsigned char[faceWidth * faceHeight * 3u]; // 3 BPP

		int faceIndex = 0;

		for (size_t i = 0; i < 4; i++)
		{
			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + i * faceWidth;
					faces[faceIndex][(x + y * faceWidth) * 3 + 0] = fImageData[(xOffset + yOffset * fWidth) * 3 + 0];
					faces[faceIndex][(x + y * faceWidth) * 3 + 1] = fImageData[(xOffset + yOffset * fWidth) * 3 + 1];
					faces[faceIndex][(x + y * faceWidth) * 3 + 2] = fImageData[(xOffset + yOffset * fWidth) * 3 + 2];
				}
			}
			faceIndex++;
		}

		for (size_t i = 0; i < 3; i++)
		{
			// Skip the middle one
			if (i == 1)
				continue;

			for (size_t y = 0; y < faceHeight; y++)
			{
				size_t yOffset = y + i * faceHeight;
				for (size_t x = 0; x < faceWidth; x++)
				{
					size_t xOffset = x + faceWidth;
					faces[faceIndex][(x + y * faceWidth) * 3 + 0] = fImageData[(xOffset + yOffset * fWidth) * 3 + 0];
					faces[faceIndex][(x + y * faceWidth) * 3 + 1] = fImageData[(xOffset + yOffset * fWidth) * 3 + 1];
					faces[faceIndex][(x + y * faceWidth) * 3 + 2] = fImageData[(xOffset + yOffset * fWidth) * 3 + 2];
				}
			}
			faceIndex++;
		}

		IN_RENDER_S3(faces, faceWidth, faceHeight, {

			glCall(glGenTextures(1, &self->fRendererID));
			glCall(glBindTexture(GL_TEXTURE_CUBE_MAP, self->fRendererID));

			glCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
			glCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			glCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			glCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			glCall(auto format = InfinitToOpenGLTextureFormat(self->fFormat));
			glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[2]));
			glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[0]));

			glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[4]));
			glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[5]));

			glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[1]));
			glCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, faces[3]));

			glCall(glGenerateMipmap(GL_TEXTURE_CUBE_MAP));

			glCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));

			for (size_t i = 0; i < 6; i++)
				delete[] faces[i];

			stbi_image_free(self->fImageData);
		})

		return true;
	}

	EOpenGLTextureCube::~EOpenGLTextureCube()
	{
		std::cout << "OpenGLTextureCube detroyed!" << std::endl;
		IN_RENDER_S({
				glCall(glDeleteTextures(1, &self->fRendererID));
			})
	}

	void EOpenGLTextureCube::Bind(u32 slot) const
	{
		IN_RENDER_S1(slot, {
				glCall(glActiveTexture(GL_TEXTURE0 + slot));
				glCall(glBindTexture(GL_TEXTURE_CUBE_MAP, self->fRendererID));
			})
	}

}
