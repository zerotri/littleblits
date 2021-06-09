#include <rockit/platform/platform.h>
#include <rockit/graphics/renderer.h>

#include <SDL2/SDL_opengl.h>

namespace Rockit
{
//    class OpenGLTexture : public Texture
//    {
//    protected:
//        GLuint textureHandle = 0;
//    public:
//        OpenGLTexture(uint32_t width, uint32_t height, Texture::Format format)
//        : Texture(width, height, format)
//        {
//            GLint internalFormat = 0;
//            GLint dataFormat = 0;
//            GLint dataType = 0;
//
//            auto newFormat = format;
//
//            // for now, we treat the default as using back buffer formats
//            if(newFormat == Texture::Format::Backbuffer || newFormat == Texture::Format::Default)
//            {
//                auto applicationInstance = Application::GetApplicationInstance();
//                auto backBuffer = applicationInstance->GetBackBuffer();
//                auto backBufferTex = backBuffer->GetTexture();
//                auto backBufferFormat = backBufferTex->GetFormat();
//                newFormat = backBufferFormat;
//            }
//
//            switch(newFormat)
//            {
//                case Texture::Format::R8U:
//                    dataFormat = GL_R;
//                    dataType = GL_UNSIGNED_BYTE;
//                    break;
//                case Texture::Format::R32F:
//                    dataFormat = GL_R;
//                    dataType = GL_FLOAT;
//                    break;
//                case Texture::Format::RGB8U:
//                    dataFormat = GL_RGB;
//                    dataType = GL_UNSIGNED_BYTE;
//                    break;
//                case Texture::Format::RGB8S:
//                    dataFormat = GL_RGB;
//                    dataType = 	GL_BYTE;
//                    break;
//                case Texture::Format::RGBA8U:
//                    dataFormat = GL_RGBA;
//                    dataType = GL_UNSIGNED_BYTE;
//                    break;
//                case Texture::Format::RGBA8S:
//                    dataFormat = GL_RGBA;
//                    dataType = 	GL_BYTE;
//                    break;
//                case Texture::Format::RGBA32F:
//                    dataFormat = GL_RGBA;
//                    dataType = GL_FLOAT;
//                    break;
//                case Texture::Format::SRGB8:
//                    dataFormat = GL_SRGB;
//                    dataType = GL_UNSIGNED_BYTE;
//                    break;
//                case Texture::Format::SRGBA8:
//                    dataFormat = GL_SRGB_ALPHA;
//                    dataType = GL_UNSIGNED_BYTE;
//                    break;
//                default:
//                    // invalid format
//                    break;
//            }
//
//            if(newFormat != Texture::Format::None)
//            {
//                internalFormat = dataFormat;
//                glGenTextures(1, &textureHandle);
//                glActiveTexture(GL_TEXTURE0);
//                glBindTexture(GL_TEXTURE_2D, textureHandle);
//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, (GLint)width, (GLint)height, 0, dataFormat, dataType, nullptr);
//            }
//        }
//        ~OpenGLTexture() override
//        {
//            if(textureHandle != 0)
//            glDeleteTextures(1, &textureHandle);
//        }
//    };
}