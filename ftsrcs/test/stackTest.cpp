#include "../../includes/header.hpp"

#define name						ft
typedef int							vectorType;
typedef name::vector< vectorType >	myType;

void stackTest( void )
{
	myType								base_container( 4, 42 );
	name::stack< vectorType, myType >	a;
	name::stack< vectorType, myType >	b( base_container );
	name::stack< vectorType, myType >	c( b );
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t| TEST DES CONSTRUCTEURS |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "Creation de a()" << std::endl;
	std::cout << "Creation de b( base_container )" << std::endl;
	std::cout << "Creation de c( b )" << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES OPERATEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "( c >= a ) -> " << ( c >= a ) << std::endl;
	std::cout << "( c <= a ) -> " << ( c <= a ) << std::endl;
	std::cout << "( c == a ) -> " << ( c == a ) << std::endl;
	std::cout << "( c != a ) -> " << ( c != a ) << std::endl;
	std::cout << "( c > b ) -> " << ( c > b ) << std::endl;
	std::cout << "( c >= b ) -> " << ( c >= b ) << std::endl;
	std::cout << "( c < b ) -> " << ( c < b ) << std::endl;
	std::cout << "( c <= b ) -> " << ( c <= b ) << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|  TEST DES \"GETTERS\"  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "c.top() -> " << c.top() << std::endl;
	std::cout << "c.empty() -> " << c.empty() << std::endl;
	std::cout << "c.size() -> " << c.size() << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES \"SETTERS\"   |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "c.push( 24 )" << std::endl;
	std::cout << "c.top() -> " << c.top() << std::endl;
	std::cout << "c.pop()" << std::endl;
	std::cout << "c.top() -> " << c.top() << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t| TEST DES DESTRUCTEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
}
