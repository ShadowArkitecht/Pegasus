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

#ifndef _PEGASUS_SCRIPTING_MANAGER_HPP_
#define _PEGASUS_SCRIPTING_MANAGER_HPP_

//====================
// Pegasus includes
//====================
#include <pegasus/utilities/singleton.hpp> // The scripting manager is a type of singleton.

//====================
// Library includes
//====================
#include <sol/sol.hpp>   // The sol lua state object.

namespace pegasus
{
	/**
	 * @author Benjamin Carter
	 *
	 * @class pegasus::ScriptingManager
	 * @ingroup scripting
	 *
	 * @brief The global scripting manager responsible for storing and loading the lua libraries.
	 *
	 * The scripting manager is responsible for storing and utilising the global lua state and making
	 * it globally available to the entire application. When the scripting manager is first initialised,
	 * it will load all of the default lua libaries and bind all of the functions that are exposed from within
	 * the engine to lua scripting interface.
	 */
	class ScriptingManager final : public Singleton<ScriptingManager>
	{
		friend class Singleton<ScriptingManager>;

	private:
		//====================
		// Member variables
		//====================
		/** The lua state that executes all lua scripts. */
		sol::state m_state;

	private:
		//====================
		// Private ctor
		//====================
		/**
		 * @brief The default constructor for the ScriptingManager singleton.
		 *
		 * The constructor for the scripting manager is private to apply to the
		 * singleton design pattern. The constructor will initialise the lua state
		 * and load of the needed lua libraries.
		 */
		explicit ScriptingManager();

		/**
		 * @brief Binds the shader type enum to the scripting interface.
		 * 
		 * This method is invoked when the scripting API is first instantiated, it will bind
		 * the eShaderType enum to the scripts so that it can be used within the serialized
		 * shader program tables.
		 */
		void bindShaderType();

	public:
		//====================
		// Dtor
		//====================
		/**
		 * @brief Default destructor for the ScriptingManager.
		 *
		 * The destructor will destroy the lua state as it is stored as a unique pointer.
		 */
		~ScriptingManager() = default;

		//====================
		// Getters and setters
		//====================
		/**
		 * @brief Retrieves a reference to the lua state.
		 *
		 * The lua state is responsible for running lua scripts and retrieving values from
		 * the subsequent scripts. It is used for de-serializing different objects into formats
		 * that the Pegasus Engine can utilise.
		 *
		 * @returns The global lua state.
		 */
		sol::state& getState();
	};

} // namespace pegasus

#endif//_PEGASUS_SCRIPTING_MANAGER_HPP_
