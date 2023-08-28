#include "../../includes/header.hpp"

int	main( int argc, char** argv )
{
	std::cout << " [ FT VERSION ] --->" << std::endl;
	std::cout << std::endl << std::endl << " [ TESTING VECTOR ] --->" << std::endl;
	vectorTest();
	std::cout << std::endl << std::endl << " [ TESTING STACK ] --->" << std::endl;
	stackTest();
	std::cout << std::endl << std::endl << " [ TESTING MAP ] --->" << std::endl;
	mapTest();
	std::cout << std::endl << std::endl << " [ 42 TEST ] --->" << std::endl;
	_42test( argc, argv );

	return 0;
}
