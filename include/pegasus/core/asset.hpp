#ifndef _PEGASUS_ASSET_HPP_
#define _PEGASUS_ASSET_HPP_

#include <string>

namespace pegasus
{
    enum class eAssetType
    {
        TEXTURE
    };

    class Asset
    {
    protected:
        std::string  m_name;
        unsigned int m_id;

    public:
        explicit Asset();
        virtual ~Asset() = default;

        const std::string& getName() const;
        void setName(const std::string& name);

        unsigned int getID() const;
    };

} //namespace pegasus

#endif//_PEGASUS_ASSET_HPP_
