#ifndef _SPARKY_XML_SERIALIZABLE_SERVICE_HPP_
#define _SPARKY_XML_SERIALIZABLE_SERVICE_HPP_

#include <sparky/utilities/iserializable_service.hpp>

namespace sparky
{
	class XmlSerializableService final : public ISerializableService
	{
	public:
		explicit XmlSerializableService();
		~XmlSerializableService() = default;

		Asset* deserialize(eAssetType type, const std::string& filename) const override;
		std::unordered_map<std::string, std::string> deserializeResources(const std::string& filename) const override;
	};

} // namespace sparky

#endif//_SPARKY_XML_SERIALIZABLE_SERVICE_HPP_