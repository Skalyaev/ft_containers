#ifndef STACK
	#define STACK

	#include "vector.hpp"

	namespace ft
	{
		template< class T, class Container = ft::vector< T > >
		class stack
		{
			public :

				// TYPES DE CLASSE
				typedef Container							container_type;
				typedef typename Container::value_type		value_type;
				typedef typename Container::size_type		size_type;
				typedef typename Container::reference		reference;
				typedef typename Container::const_reference	const_reference;

				// CONSTRUCTEURS + DESTRUCTEUR
				explicit stack( const container_type& ctnr = container_type() ) :
				c( ctnr )
				{}

				stack( const stack& other ) :
				c( other.c )
				{}

				~stack()
				{}

				// SURCHARGES D'OPERATEURS MEMBRES
				stack& operator=( const stack& other )
				{
					c = other.c;
					return *this;
				}

				// SURCHARGES D'OPERATEURS NON-MEMBRES
				friend bool operator==( const ft::stack< T, Container >& lhs, const ft::stack< T, Container >& rhs )
				{ return lhs.c == rhs.c; }

				friend bool operator!=( const ft::stack< T, Container >& lhs, const ft::stack< T, Container >& rhs )
				{ return lhs.c != rhs.c; }

				friend bool operator<( const ft::stack< T, Container >& lhs, const ft::stack< T, Container >& rhs )
				{ return lhs.c < rhs.c; }

				friend bool operator<=( const ft::stack< T, Container >& lhs, const ft::stack< T, Container >& rhs )
				{ return lhs.c <= rhs.c; }

				friend bool operator>( const ft::stack< T, Container >& lhs, const ft::stack< T, Container >& rhs )
				{ return lhs.c > rhs.c; }

				friend bool operator>=( const ft::stack< T, Container >& lhs, const ft::stack< T, Container >& rhs )
				{ return lhs.c >= rhs.c; }

				// ELEMENTS D'ACCES
				reference top( void )
				{ return c.back(); }

				const_reference top( void ) const
				{ return c.back(); }

				// CAPACITE
				bool empty( void ) const
				{ return c.empty(); }

				size_type size( void ) const
				{ return c.size(); }

				// MODIFIEURS
				void push( const value_type& value )
				{ c.push_back( value ); }

				void pop( void )
				{ c.pop_back(); }

			protected :

				// VARIABLES
				container_type c;
		};
	}

#endif