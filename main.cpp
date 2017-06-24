#include <sparky/core/resources.hpp>
#include <sparky/utilities/no_resource_exception.hpp>

#include <iostream>
#include <fstream>

using namespace sparky;

int main(int argc, char** argv)
{
    try
    {
	    Resources::load();
    }
    catch (NoResourceException&)
    {
        // TODO(Ben): Log this exception.
        return 1;
    }

	std::ifstream file;
	file.open(Resources::get("test.asset"));

	std::string line;
	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}

    getchar();
    return 0;
}

