#ifndef _SPARKY_LUA_SERIALIZABLE_SERVICE_HPP_
#define _SPARKY_LUA_SERIALIZABLE_SERVICE_HPP_

#include <sparky/utilities/iserializable_service.hpp>

namespace sparky
{
	class LuaSerializableService final : public ISerializableService
	{
	public:
		explicit LuaSerializableService();
		~LuaSerializableService() = default;

		Asset* deserialize(eAssetType type, const std::string& name) const override;
		std::unordered_map<std::string, std::string> deserializeResources(const std::string& filename) const override;
	};

} // namespace sparky

#endif//_SPARKY_LUA_SERIALIZABLE_SERVICE_HPP_