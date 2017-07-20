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
#include <pegasus/core/asset.hpp> // Class declaration.

namespace pegasus
{
    //====================
    // Ctors and dtor
    //====================
    /**********************************************************/
    Asset::Asset()
        : m_ID(0), m_name(), m_references(0)
    {
        // Empty.
    }

    //====================
    // Getters and setters
    //====================
    /**********************************************************/
    unsigned int Asset::getID() const
    {
        return m_ID;
    }

    /**********************************************************/
    const std::string& Asset::getName() const
    {
        return m_name;
    }

    /**********************************************************/
    void Asset::setName(const std::string& name)
    {
        m_name = name;
    }

    /**********************************************************/
    unsigned int Asset::getRefCount() const
    {
        return m_references;
    }

    /**********************************************************/
    bool Asset::isReferenced() const
    {
        return m_references > 0;
    }

    //====================
    // Methods
    //====================
    /**********************************************************/
    void Asset::retain()
    {
        ++m_references;
    }

    /**********************************************************/
    void Asset::release()
    {
        --m_references;
    }

} // namespace pegasus
