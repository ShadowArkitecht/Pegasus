/*
* Pegasus Engine
* 2017 - Benjamin Carter (bencarterdev@outlook.com)
*
* This software is provided 'as-is', without any express or implied warranty.
* In no event will the authors be held liable for any damages arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it freely,
* subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgement
*    in the product documentation would be appreciated but is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

//====================
// Pegasus includes
//====================
#include <pegasus/graphics/texture.hpp>          // Class declaration.
#include <pegasus/utilities/logger_factory.hpp>  // Initializing the logger.

//====================
// Library includes
//====================
#include <SDL2/SDL_image.h>                      // Loading in an external image into SDL.

namespace pegasus
{	
	//====================
	// Static variables
	//====================
	Texture* Texture::m_pDefault = nullptr;

	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	Texture::Texture()
		: Asset(), m_logger(LoggerFactory::getLogger("file.logger")), m_size(), m_type()
	{
		m_ID = gl::genTexture();
	}

	/**********************************************************/
	Texture::Texture(const TextureDescription_t& description)
		: Asset(), m_logger(LoggerFactory::getLogger("file.logger")), m_size(), m_type()
	{
		m_ID = gl::genTexture();
		this->loadFromFile(description);
	}

	/**********************************************************/
	Texture::~Texture()
	{
		if (m_ID)
		{
			glDeleteTextures(1, &m_ID);
		}
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	Texture* Texture::getDefault()
	{
		if (!m_pDefault)
		{
			m_pDefault = new Texture();
		}

		return m_pDefault;
	}

	/**********************************************************/
	const glm::ivec2& Texture::getSize() const
	{
		return m_size;
	}

	/**********************************************************/
	gl::eTextureType Texture::getType() const
	{
		return m_type;
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	bool Texture::loadFromFile(const TextureDescription_t& description)
	{
		// TODO(Ben): Check file location.
		SDL_Surface* pSurface = IMG_Load(description.source.c_str());
		// Check the surface allocates correctly.
		if (!pSurface)
		{
			m_logger.warning("Texture: failed to load image:", description.source, "Error:", IMG_GetError());
			return false;
		}

		// Set the size and type of the texture and retain the information.
		m_size = glm::vec2(pSurface->w, pSurface->h);
		m_type = description.type;

		// Auto-detect the rgb type.
		GLenum format = pSurface->format->BytesPerPixel == 3 ? GL_RGB : GL_RGBA;

		// Bind the texture and set the information.
		Texture::bind(*this);
		// Bind the texture types to the OpenGL types.
		GLenum type = static_cast<GLenum>(description.type);
		GLenum filter = static_cast<GLenum>(description.filtering);
		GLenum wrapping = static_cast<GLenum>(description.wrapping);
		// Set the generic texture information.
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapping);
		// Set the texture image and generate some mip-maps.
		glTexImage2D(type, 0, format, m_size.x, m_size.y, 0, format, GL_UNSIGNED_BYTE, pSurface->pixels);
		glGenerateMipmap(type);

		Texture::unbind(*this);
		// Free the surface, it's no longer needed.
		SDL_FreeSurface(pSurface);
		return true;
	}

	/**********************************************************/
	void Texture::bind(const Texture& texture, GLuint location/*= 0*/)
	{
		glActiveTexture(GL_TEXTURE0 + location);
		gl::bindTexture(texture.getType(), texture.getID());
	}

	/**********************************************************/
	void Texture::unbind(const Texture& texture)	
	{
		gl::bindTexture(texture.getType(), 0);
	}

} // namespace pegasus	