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
#include <pegasus/scripting/scripting_manager.hpp> // ScriptingManager class declaration.
#include <pegasus/core/asset.hpp>                  // Binding the asset enum and class.
#include <pegasus/graphics/gl.hpp>                 // Binding specific graphics API objects.

namespace pegasus
{
	//====================
	// Private ctor
	//====================
	/**********************************************************/
	ScriptingManager::ScriptingManager()
		: Singleton<ScriptingManager>(), m_state()
	{
		m_state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::table, sol::lib::debug);
		// Bind the different classes/objects/enums.
		// Core library.
		this->bindAssetType();
		// Graphics library.
		this->bindShaderType();
		this->bindTextureType();
		this->bindFilterType();
		this->bindWrapType();
	}

	//====================
	// Private methods
	//====================
	/**********************************************************/
	void ScriptingManager::bindAssetType()
	{
		m_state.new_enum("AssetType",
			"Shader", eAssetType::SHADER,
			"Texture", eAssetType::TEXTURE);
	}

	/**********************************************************/
	void ScriptingManager::bindShaderType()
	{
		m_state.new_enum("ShaderType",
			"Vertex", gl::eShaderType::VERTEX,
			"Fragment", gl::eShaderType::FRAGMENT);
	}

	/**********************************************************/
	void ScriptingManager::bindTextureType()
	{
		m_state.new_enum("TextureType",
			"Texture2D", gl::eTextureType::TEXTURE_2D);
	}

	/**********************************************************/
	void ScriptingManager::bindFilterType()
	{
		m_state.new_enum("FilterType",
			"Nearest", gl::eFilterType::NEAREST,
			"Linear", gl::eFilterType::LINEAR);
	}

	/**********************************************************/
	void ScriptingManager::bindWrapType()
	{
		m_state.new_enum("WrapType",
			"Repeat", gl::eWrapType::REPEAT,
			"Clamp", gl::eWrapType::CLAMP);
	}

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	sol::state& ScriptingManager::getState()
	{
		return m_state;
	}

} // namespace pegasus
