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
#include <pegasus/core/resources.hpp>                             // Class declaration.
#include <pegasus/utilities/exceptions/no_resource_exception.hpp> // Throwing exceptions if resource not found.

//====================
// Library includes
//====================
#include <pugixml.hpp> // De-serializing the Resources.xml file.

namespace pegasus
{
	//====================
	// Static declaration.
	//====================
	std::unordered_map<std::string, std::string> Resources::m_resources;
	ISerializableService* Resources::m_pService;

	//====================
	// Getters and setters
	//====================
	/**********************************************************/
	void Resources::setService(ISerializableService& service)
	{
		m_pService = &service;
	}

	/**********************************************************/
	std::string Resources::get(const std::string& name) const
	{
		auto itr = m_resources.find(name);
		if (itr == m_resources.end())
		{
			throw NoResourceException("Unable to load file location for resource: " + name);
		}

		return itr->second;
	}

	//====================
	// Methods
	//====================
	/**********************************************************/
	void Resources::load(const std::string& filename)
	{
		m_resources = m_pService->deserializeResources(filename);
	}

} // namespace pegasus
