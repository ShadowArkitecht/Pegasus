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

#ifndef _PEGASUS_SHADER_PROGRAM_FACTORY_HPP_
#define _PEGASUS_SHADER_PROGRAM_FACTORY_HPP_

//====================
// C++ includes
//====================
#include <unordered_map> // Storing a list of retained assets.

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/iasset_factory.hpp> // The factory is a type of asset factory.

namespace pegasus
{
	//====================
	// Forward declarations
	//====================
	class Logger;
	
	class ShaderProgramFactory final : public IAssetFactory
	{
	private:
		//====================
		// Member variables
		//====================
		/** Logging warnings and messages to the external files. */
		Logger& m_logger;
		/** Storing a list of shaders. */
		std::unordered_map<std::string, Asset*> m_shaders;

	public:
		//====================
		// Ctors and dtor
		//====================
		/**
		 * @brief Default constructor for the shader program factory.
		 * 
		 * The default constructor will set the member variables to default
		 * values and set the logger to log messages to the external log file.
		 */
		explicit ShaderProgramFactory();

		/**
		 * @brief Destructor for the ShaderProgramFactory.
		 * 
		 * The shader program is wholly responsible for the lifetime of shader programs.
		 * When the destructor is invoked, it will delete all of the retained resources
		 * and free the memory. This will typically only happen at the end of the programs
		 * life-time.	
		 */
		~ShaderProgramFactory();

		/**
		 * @brief Loads an external serialized file and stores it as an asset.
		 * 
		 * When the load method is invoked, it will use the bound serializable
		 * service to de-serialize the specified asset and store it in a map object.
		 * If the object has already been loaded, it will use the retained resource, instead
		 * of re-creating an identical object.
		 * 
		 * @param name The name of the asset to retrieve.
		 * @returns The asset being loaded.
		 */
		Asset* load(const std::string& name) override;
	};

} // namespace pegasus

#endif//_PEGASUS_SHADER_PROGRAM_FACTORY_HPP_