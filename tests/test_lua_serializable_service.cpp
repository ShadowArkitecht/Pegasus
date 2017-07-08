/*
* Sparky Engine
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
// Sparky includes
//====================
#include <sparky/utilities/lua_serializable_service.hpp> // Testing the LuaSerializableService class.
#include <sparky/utilities/exceptions/no_resource_exception.hpp> // Testing for correct exceptions being thrown.

//====================
// Library includes
//====================
#include <catch.hpp> // Unit test library.

using namespace sparky;

//====================
// Unit tests
//====================
/**********************************************************/
TEST_CASE("LuaSerializableService: Load Rsources.lua valid file.", "[LuaSerializableService]")
{
	// Arrange.
	LuaSerializableService service;
	// Act.
	auto values = service.deserializeResources("Resources.lua");
	// Assert.
	REQUIRE(!values.empty());
}

/**********************************************************/
TEST_CASE("LuaSerializableService: Load Resources.lua invalid file.", "[LuaSerializableService]")
{
	// Arrange.
	LuaSerializableService service;
	// Assert.
	REQUIRE_THROWS_AS(service.deserializeResources("garbage"), NoResourceException);
}