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
#include <pegasus/utilities/iasset_factory.hpp> // class declaration.

namespace pegasus
{
	//====================
	// Ctors and dtor
	//====================
	/**********************************************************/
	IAssetFactory::IAssetFactory(const std::type_index& type, std::size_t threshold/*= 10*/)
		: m_type(type), m_threshold(threshold)
	{
		// Empty.
	}
	
	//====================
	// Getters and setters
	//====================
	/**********************************************************/
    ISerializableService* IAssetFactory::getService() const
    {
        return m_service.get();
    }

	/**********************************************************/
    void IAssetFactory::setService(ISerializableService* pService)
    {
        m_service.reset(pService);
    }
	
	/**********************************************************/
	const std::type_index& IAssetFactory::getType() const
	{
		return m_type;
	}
	
	/**********************************************************/
	std::size_t IAssetFactory::getThreshold() const
	{
		return m_threshold;
	}
	
	/**********************************************************/
	void IAssetFactory::setThreshold(std::size_t threshold)
	{
		m_threshold = threshold;
	}
	
} // namespace pegasus
