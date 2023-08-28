#include "../../includes/header.hpp"

#define name	std
typedef int		myKeyType;
typedef int		myValueType;

void displayMapContent( name::map< myKeyType, myValueType >& ref )
{
	name::map< myKeyType, myValueType >::iterator	i;

	for ( i = ref.begin() ; i != ref.end() ; i++ )
	{
		std::cout << "[ " << i->first << ", " << i->second << " ]";
		std::cout << " ";
	}
	std::cout << std::endl;
}

void displayMap( name::map< myKeyType, myValueType >* a, name::map< myKeyType, myValueType >* b,
	name::map< myKeyType, myValueType >* c, name::map< myKeyType, myValueType >* d, name::map< myKeyType, myValueType >* e )
{
	if ( a )
	{
		std::cout << "a -> size : " << a->size() << " | content : ";
		displayMapContent( *a );
	}
	if ( b )
	{
		std::cout << "b -> size : " << b->size() << " | content : ";
		displayMapContent( *b );
	}
	if ( c )
	{
		std::cout << "c -> size : " << c->size() << " | content : ";
		displayMapContent( *c );
	}
	if ( d )
	{
		std::cout << "d -> size : " << d->size() << " | content : ";
		displayMapContent( *d );
	}
	if ( e )
	{
		std::cout << "e -> size : " << e->size() << " | content : ";
		displayMapContent( *e );
	}
}

void mapTest( void )
{
	name::vector< name::pair< myKeyType, myValueType > > c_ref( 1, name::make_pair( 1, 42) );
	name::map< myKeyType, myValueType >	a;
	name::map< myKeyType, myValueType >	b( a.key_comp(), a.get_allocator() );
	name::map< myKeyType, myValueType >	c( c_ref.begin(), c_ref.end() );
	name::map< myKeyType, myValueType >	d( c );
	name::map< myKeyType, myValueType >	e( c.begin(), c.end() );
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t| TEST DES CONSTRUCTEURS |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "Creation de a()" << std::endl;
	std::cout << "Creation de b( a.key_comp(), a.get_allocator() )" << std::endl;
	std::cout << "Creation de c( c_ref.begin(), c_ref.end() )" << std::endl;
	std::cout << "Creation de d( c )" << std::endl;
	std::cout << "Creation de e( c.begin(), c.end() )" << std::endl;
	displayMap( &a, &b, &c, &d, &e );


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES OPERATEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "c[ 0 ] -> " << c[ 0 ] << std::endl;
	std::cout << "c[ c.size() - 1 ] -> " << c[ c.size() - 1 ] << std::endl;
	std::cout << "( c == d ) -> " << ( c == d ) << std::endl;
	std::cout << "( c >= d ) -> " << ( c >= d ) << std::endl;
	std::cout << "( c <= d ) -> " << ( c <= d ) << std::endl;
	c[ 0 ] = 77;
	d[ 2 ] = 77;
	std::cout << "Modifications de c et d --->" << std::endl;
	displayMap( NULL, NULL, &c, &d, NULL );
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
	displayMap( NULL, NULL, NULL, &d, NULL );
	std::cout << "( d.begin() )->first/second : [ " << ( d.begin() )->first << ", " << ( d.begin() )->second << " ]" << std::endl;
	std::cout << "( --d.end() )->first/second :  [ " << ( --d.end() )->first << ", " << ( --d.end() )->second << " ]" << std::endl;
	std::cout << "( d.rbegin() )->first/second :  [ " << ( d.rbegin() )->first << ", " << ( d.rbegin() )->second << " ]" << std::endl;
	std::cout << "( --d.rend() )->first/second :  [ " << ( --d.rend() )->first << ", " << ( --d.rend() )->second << " ]" << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES \"GETTERS\"   |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	try
	{ std::cout << "d.at( -1 ) -> " << d.at( -1 ) << std::endl; }
	catch ( std::exception& ex )
	{ std::cerr << ex.what() << std::endl; }
	std::cout << "d.at( 1 ) -> " << d.at( 1 ) << std::endl;
	std::cout << "a.empty() -> " << a.empty() << std::endl;
	std::cout << "d.empty() -> " << d.empty() << std::endl;
	std::cout << "d.size() -> " << d.size() << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|   TEST DES \"SETTERS\"  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	displayMap( NULL, NULL, NULL, &d, NULL );
	d.clear();
	std::cout << "d.clear()-> DONE" << std::endl;
	displayMap( NULL, NULL, NULL, &d, NULL );
	d.insert( name::make_pair( 3, 33 ) );
	std::cout << "d.insert( name::make_pair( 3, 33 ) ) -> DONE" << std::endl;
	displayMap( NULL, NULL, NULL, &d, NULL );
	d.insert( d.begin(), name::make_pair( 1, 11 ) );
	d.insert( d.begin(), name::make_pair( 2, 22 ) );
	d.insert( d.begin(), name::make_pair( 4, 44 ) );
	std::cout << "d.insert( d.begin(), name::make_pair( 1, 11 ) ) -> DONE" << std::endl;
	std::cout << "d.insert( d.begin(), name::make_pair( 2, 22 ) ) -> DONE" << std::endl;
	std::cout << "d.insert( d.begin(), name::make_pair( 4, 44 ) ) -> DONE" << std::endl;
	displayMap( NULL, NULL, NULL, &d, NULL );
	d.insert( d.begin(), d.end() );
	std::cout << "d.insert( d.begin(), d.end() ) -> DONE" << std::endl;
	displayMap( NULL, NULL, NULL, &d, NULL );
	d.erase( d.begin() );
	std::cout << "d.erase( d.begin() ) -> DONE" << std::endl;
	displayMap( NULL, NULL, &c, &d, NULL );
	c.erase( c.begin(), c.end() );
	std::cout << "c.erase( c.begin(), c.end() ) -> DONE" << std::endl;
	displayMap( NULL, NULL, &c, &d, &e );
	name::map< myKeyType, myValueType >::iterator it = d.begin();
	std::cout << "*it->first/begin : [ " << it->first << ", " << it->second << " ]" << std::endl;
	d.swap( e );
	std::cout << "d.swap( e ) -> DONE" << std::endl;
	std::cout << "*it->first/begin : [ " << it->first << ", " << it->second << " ]" << std::endl;
	displayMap( NULL, NULL, NULL, &d, &e );
	name::swap( d, e );
	std::cout << "std::swap( d, e ) -> DONE" << std::endl;
	displayMap( NULL, NULL, NULL, &d, &e );


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t|  TEST DES OPERATIONS   |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "d.count( 4 ) -> " << d.count( 4 ) << std::endl;
	std::cout << "d.find( 4 )->second -> " << d.find( 4 )->second << std::endl;
	std::cout << "d.equal_range( 4 ).first->second -> " << d.equal_range( 4 ).first->second << std::endl;


	std::cout << std::endl;
	std::cout << "\t--------------------------" << std::endl;
	std::cout << "\t| TEST DES DESTRUCTEURS  |" << std::endl;
	std::cout << "\t--------------------------" << std::endl;
}