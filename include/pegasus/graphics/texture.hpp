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

#ifndef _PEGASUS_TEXTURE_HPP_
#define _PEGASUS_TEXTURE_HPP_

//====================
// Pegasus includes
//====================
#include <pegasus/core/asset.hpp>                   // The texture is a type of asset.
#include <pegasus/graphics/texture_description.hpp> // The description for the texture object.

//====================
// Library includes
//====================
#include <glm/glm.hpp>                              // Storing the dimensions of the texture.

namespace pegasus
{
	//====================
	// Forward declarations
	//====================
	class Logger;

	class Texture final : public Asset 
	{
	private:
		//====================
		// Member variables
		//====================
		/** The default texture that is returned if any errors are encountered. */
		static Texture*  m_pDefault;
		/** Log information to do with loading and using the texture. */
		Logger&          m_logger;
		/** The dimensions (width and height) of the texture. */
		glm::ivec2       m_size;
		/** The type of texture being used. */
		gl::eTextureType m_type;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the Texture object.
		 * 
		 * When a texture is created with the default constructor, it is only
		 * assigned a default buffer ID. The buffer can be bound but no additional
		 * behavior has been defined. The texture will not render when initialized 
		 * in this manner, an additional call to Texture::loadFromFile must be made.
		 */
		explicit Texture();

		/**
		 * @brief Constructs a texture and loads an image supplied by the description.
		 * 
		 * When the texture is instantiated with this constructor, it will utilise the details
		 * supplied in the description and create a texture from the supplied image. If the load
		 * was successful, the texture can be bound for additional rendering behavior. If the texture
		 * failed to load, the rendering context will be unaltered when the texture is bound.
		 * 
		 * @param description The description to create the texture from.
		 */
		explicit Texture(const TextureDescription_t& description);

		/**
		 * @brief Destructor for the texture.
		 * 
		 * When the destructor is called, it will destroy any texture buffers
		 * that are being retained by the object.
		 */
		~Texture();

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieve the default representation of a texture.
		 * 
		 * The default texture is just a simple texture that is only used
		 * when a texture was not loaded correctly or encountered errors during
		 * de-serialization. The default is lazily loaded and only created when
		 * needed.
		 * 
		 * @returns A default texture object.
		 */
		static Texture* getDefault();

		/**
		 * @brief Retrieves the width and height of the texture.
		 * 
		 * The width and height represents (in pixels) the dimensions of the texture.
		 * These values are immutable and cannot be changed, they are only altered when 
		 * a texture is first loaded into the buffer. If a texture has not been loaded, the
		 * default is [ 0, 0 ].
		 * 
		 * @returns The dimensions of the texture.
		 */
		const glm::ivec2& getSize() const;

		/**
		 * @brief Retrieves the type of the texture object.
		 * 
		 * The texture type defines the behavior of the texture itself, and the amount
		 * of dimensions that the texture will affect when it is bound to the rendering
		 * context. The most common type is of TEXTURE2D. 
		 * 
		 * @return The type of the texture.
		 */
		gl::eTextureType getType() const;

		//====================
		// Methods
		//====================
		/**
		 * @brief Loads an image from a file directory and converts it into a useable texture.
		 * 
		 * When this method is invoked, It will load an image defined within a texture description
		 * and convert it into a format that the pegasus engine can utilise. If the description cannot
		 * be converted into a texture, the method will return false and it will not alter the rendering
		 * context. 
		 * 
		 * @param description The description of the texture to create.
		 * 
		 * @returns True if the description was converted successfully. 
		 */
		bool loadFromFile(const TextureDescription_t& description);

		/**
		 * @brief Binds a texture to the rendering context.
		 * 
		 * When the texture is bound to the current context, when a shader is rendered and
		 * utilises samplers, it will use the behavior defined within the texture. 
		 * 
		 * @param texture The texture to bind to the rendering context.
		 * @param location The optional location to bind the texture to.
		 */
		static void bind(const Texture& texture, GLuint location = 0);

		/**
		 * @brief Unbinds the texture from the rendering context.
		 * 
		 * When the texture is unbound, it will no longer be utilised by the rendering
		 * context.
		 * 
		 * @param texture The texture to unbind from the texture.
		 */
		static void unbind(const Texture& texture);
	};

} // namespace pegasus

#endif//_PEGASUS_TEXTURE_HPP_