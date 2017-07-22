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
#include <pegasus/graphics/shader_program_factory.hpp>            // Class declaration.
#include <pegasus/graphics/shader_program.hpp>                    // Loading in and storing shader programs.
#include <pegasus/utilities/logger_factory.hpp>                   // Retrieving the log file.
#include <pegasus/utilities/exceptions/serialize_exception.hpp>   // Catching any thrown serialize exceptions.
#include <pegasus/utilities/exceptions/no_resource_exception.hpp> // Catching any thrown resource exceptions.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	ShaderProgramFactory::ShaderProgramFactory()
		: IAssetFactory(typeid(ShaderProgram)), m_logger(LoggerFactory::getLogger("file.logger")), m_shaders()
	{
		m_logger.debug("ShaderProgramFactory constructed.");
	}

	/**********************************************************/
	ShaderProgramFactory::~ShaderProgramFactory()
	{
		// Iterate through all the retained assets and delete them.
		for (auto& shader : m_shaders)
		{
			// Delete the shader program.
			delete shader.second;
		}
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	Asset* ShaderProgramFactory::load(const std::string& name) // override
	{
		try
		{
			std::string file = m_resources.get(name);
			// See if the shader being requested has already been loaded.
			auto itr = m_shaders.find(file);
			// It has been found, return a copy of that object.
			if (itr != m_shaders.end())
			{
				return itr->second;
			}
			// De-serialize and create a new shader program.
			auto shader = this->getService()->deserialize(eAssetType::SHADER, file);
			// Insert the shader into the map.
			m_shaders.insert({ file, shader });
			// Return the new shader program.
			return shader;
		}
		catch (SerializeException& e)
		{
			m_logger.warning("ShaderProgramFactory:", e.what(), ". Returning default shader asset.");
			return ShaderProgram::getDefault();
		}
		// Catch a wrong resource and return the default.
		catch (NoResourceException& e)
		{
			m_logger.warning("ShaderProgramFactory:", e.what(), ". Returning default shader asset.");
			return ShaderProgram::getDefault();
		}
		// Might aswell catch all, incase there's any problems that we're not expected.
		catch (std::exception& e)
		{
			m_logger.warning("ShaderProgramFactory:", e.what(), ". Returning default shader asset.");
			return ShaderProgram::getDefault();
		}
	}

} // namespace pegasus