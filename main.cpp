#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define UNUSED(variable) (void)variable;

int main(int argc, char const *argv[])
{
	UNUSED(argc)
	UNUSED(argv)
    try
    {
		;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}