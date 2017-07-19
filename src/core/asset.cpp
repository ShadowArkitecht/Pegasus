#include <pegasus/core/asset.hpp>

namespace pegasus
{
    Asset::Asset()
        : m_ID(0), m_name()
    {
        // Empty.
    }

    unsigned int Asset::getID() const
    {
        return m_ID;
    }

    const std::string& Asset::getName() const
    {
        return m_name;
    }

    void Asset::setName(const std::string& name)
    {
        m_name = name;
    }

} // namespace pegasus
