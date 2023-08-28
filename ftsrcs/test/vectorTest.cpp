#include "../../includes/header.hpp"

#define name		ft
typedef std::string	myType;

void displayVectorContent( name::vector< myType >& ref )
{
	for ( std::size_t i = 0 ; i < ref.size() ; i++ )
	{
		std::cout << ref.data()[ i ];
		std::cout << " ";
	}
	std::cout << std::endl;
}

void displayVector( name::vector< myType >* a, name::vector< myType >* b,
	name::vector< myType >* c, name::vector< myType >* d, name::vector< myType >* e )
{
	if ( a )
	{
		std::cout << "a -> capacity : " << a->capacity() << " | size : " << a->size() << " | content : ";
		displayVectorContent( *a );
	}
	if ( b )
	{
		std::cout << "b -> capacity : " << b->capacity() << " | size : " << b->size() << " | content : ";
		displayVectorContent( *b );
	}
	if ( c )
	{
		std::cout << "c -> capacity : " << c->capacity() << " | size : " << c->size() << " | content : ";
		displayVectorContent( *c );
	}
	if ( d )
	{
		std::cout << "d -> capacity : " << d->capacity() << " | size : " << d->size() << " | content : ";
		displayVectorContent( *d );
	}
	if ( e )
	{
		std::cout << "e -> capacity : " << e->capacity() << " | size : " << e->size() << " | content : ";
		displayVectorContent( *e );
	}
}

void vectorTest( void )
{
	name::vector< myType >	a;
	name::vector< myType >	b( a.get_allocator() );
	name::vector< myType >	c( 4, "42" );
	name::vector< myType >	d( c );
	name::vector< myType >	e( c.begin(), c.end() );
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t| TEST DES CONSTRUCTEURS |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "Creation de a()" << std::endl;
	std::cout << "Creation de b( a.get_allocator() )" << std::endl;
	std::cout << "Creation de c( 4, 42 )" << std::endl;
	std::cout << "Creation de d( c )" << std::endl;
	std::cout << "Creation de e( c.begin(), c.end() )" << std::endl;
	displayVector( &a, &b, &c, &d, &e );


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES OPERATEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "c[ 0 ] -> " << c[ 0 ] << std::endl;
	std::cout << "c[ c.size() - 1 ] -> " << c[ c.size() - 1 ] << std::endl;
	std::cout << "( c == d ) -> " << ( c == d ) << std::endl;
	std::cout << "( c >= d ) -> " << ( c >= d ) << std::endl;
	std::cout << "( c <= d ) -> " << ( c <= d ) << std::endl;
	c[ 0 ] = "77";
	d[ 1 ] = "77";
	d.push_back( "99" );
	std::cout << "Modifications de c et d --->" << std::endl;
	displayVector( NULL, NULL, &c, &d, NULL );
	std::cout << "( c == d ) -> " << ( c == d ) << std::endl;
	std::cout << "( c != d ) -> " << ( c != d ) << std::endl;
	std::cout << "( c > d ) -> " << ( c > d ) << std::endl;
	std::cout << "( c >= d ) -> " << ( c >= d ) << std::endl;
	std::cout << "( c < d ) -> " << ( c < d ) << std::endl;
	std::cout << "( c <= d ) -> " << ( c <= d ) << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES ITERATEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	std::cout << "*( d.begin() ) -> " << *( d.begin() ) << std::endl;
	std::cout << "*( d.begin() + 1 ) -> " << *( d.begin() + 1 ) << std::endl;
	std::cout << "*( d.end() - 1 ) -> " << *( d.end() - 1 ) << std::endl;
	std::cout << "*( d.rbegin() ) -> " << *( d.rbegin() ) << std::endl;
	std::cout << "*( d.rbegin() + 1 ) -> " << *( d.rbegin() + 1 ) << std::endl;
	std::cout << "*( d.rend() - 1 ) -> " << *( d.rend() - 1 ) << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES \"GETTERS\"   |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "d.front() -> " << d.front() << std::endl;
	std::cout << "d.back() -> " << d.back() << std::endl;
	try
	{ std::cout << "d.at( -1 ) -> " << d.at( -1 ) << std::endl; }
	catch ( const std::exception& ex )
	{ std::cerr << ex.what() << std::endl; }
	std::cout << "d.at( 0 ) -> " << d.at( 0 ) << std::endl;
	std::cout << "d.at( d.size() - 1 ) -> " << d.at( d.size() - 1 ) << std::endl;
	try
	{ std::cout << "d.at( d.size() ) -> " << d.at( d.size() ) << std::endl; }
	catch ( const std::exception& ex )
	{ std::cerr << ex.what() << std::endl; }
	std::cout << "a.empty() -> " << a.empty() << std::endl;
	std::cout << "d.empty() -> " << d.empty() << std::endl;
	std::cout << "d.max_size() -> " << d.max_size() << std::endl;
	std::cout << "d.size() -> " << d.size() << std::endl;
	std::cout << "d.capacity() -> " << d.capacity() << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES \"SETTERS\"   |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	try
	{
		std::cout << "d.reserve( -1 ) -> ";
		d.reserve( -1 );
		std::cout << "DONE" << std::endl;
	}
	catch ( const std::exception& ex )
	{ std::cerr << ex.what() << std::endl; }
	d.reserve( 10 );
	d.pop_back();
	std::cout << "d.reserve( 10 ) -> DONE" << std::endl;
	std::cout << "d.pop_back -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.clear();
	std::cout << "d.clear()-> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.assign( 4, "77" );
	std::cout << "d.assign( 4, 77 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	try
	{
		std::cout << "d.resize( -1 ) -> ";
		d.resize( -1 );
		std::cout << "DONE" << std::endl;
	}
	catch ( const std::exception& ex )
	{ std::cerr << ex.what() << std::endl; }
	d.resize( 10 );
	std::cout << "d.resize( 10 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.resize( 1 );
	std::cout << "d.resize( 1 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.erase( d.begin() );
	std::cout << "d.erase( d.begin() ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	c.erase( c.begin(), c.end() );
	std::cout << "c.erase( c.begin(), c.end() ) -> DONE" << std::endl;
	displayVector( NULL, NULL, &c, &d, &e );
	d.assign( e.begin(), e.end() );
	std::cout << "d.assign( e.begin(), e.end() ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.insert( d.begin(), "33" );
	std::cout << "d.insert( d.begin(), 33 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.insert( d.begin(), 4, "23" );
	std::cout << "d.insert( d.begin(), 4, 23 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	d.insert( d.begin(), e.begin(), e.begin() + 3 );
	std::cout << "d.insert( d.begin(), e.begin(), e.begin() + 3 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, NULL );
	e.assign( 7, "33" );
	std::cout << "e.assign( 7, 33 ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, NULL, &e );
	name::vector< myType >::iterator it = d.begin();
	std::cout << "*it -> " << *it << std::endl;
	d.swap( e );
	std::cout << "d.swap( e ) -> DONE" << std::endl;
	std::cout << "*it -> " << *it << std::endl;
	displayVector( NULL, NULL, NULL, &d, &e );
	name::swap( d, e );
	std::cout << "std::swap( d, e ) -> DONE" << std::endl;
	displayVector( NULL, NULL, NULL, &d, &e );

	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t| TEST DES DESTRUCTEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
}
