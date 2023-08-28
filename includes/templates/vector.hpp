#ifndef VECTOR
	#define VECTOR

	#include <sstream> // ---> std::ostringstream
	#include "algorithm.hpp"
	#include "type_traits.hpp"
	#include "iterator.hpp"

	namespace ft
	{
		template < class T, class Allocator = std::allocator< T > >
		class vector
		{
			public :

				// TYPES DE CLASSE
				typedef	T 														value_type;
				typedef	std::size_t												size_type;
				typedef Allocator												allocator_type;
				typedef vector_iterator< value_type >							iterator;
				typedef vector_iterator< const value_type >						const_iterator;
				typedef	vector_rev_iter< iterator >								reverse_iterator;
				typedef	vector_rev_iter< const_iterator >						const_reverse_iterator;
				typedef typename allocator_type::reference						reference;
				typedef typename allocator_type::const_reference				const_reference;
				typedef typename allocator_type::pointer						pointer;
				typedef typename allocator_type::const_pointer					const_pointer;
				typedef typename iterator_traits< iterator >::difference_type	difference_type;

				// CONSTRUCTEURS + DESTRUCTEUR
				vector( void ) :
				_allocator( allocator_type() ),
				_capacity( 0 ),
				_size( 0 ),
				_container( NULL )
				{}

				vector( const vector& other ) :
				_allocator( other._allocator ),
				_capacity( 0 ),
				_size( 0 ),
				_container( NULL )
				{ *this = other; }

				explicit vector( const allocator_type& alloc ) :
				_allocator( alloc ),
				_capacity( 0 ),
				_size( 0 ),
				_container( NULL )
				{}

				explicit vector( size_type count, const value_type& value = value_type(), const allocator_type& alloc = allocator_type() ) :
				_allocator( alloc ),
				_capacity( 0 ),
				_size( 0 ),
				_container( NULL )
				{ assign( count, value ); }

				template < class Iter >
				vector( Iter first, Iter last, const allocator_type& alloc = allocator_type(),
				typename enable_if< !is_integral< Iter >::value, Iter >::type* = 0 ) :
				_allocator( alloc ),
				_capacity( 0 ),
				_size( 0 ),
				_container( NULL )
				{ assign( first, last ); }

				~vector()
				{ destroy_content(); }

				// SURCHARGES D'OPERATEURS MEMBRES
				vector& operator=( const vector& other )
				{
					assign( other.begin(), other.end() );
					return *this;
				}

				reference operator[]( size_type pos )
				{ return _container[ pos ]; }

				const_reference operator[]( size_type pos ) const
				{ return _container[ pos ]; }

				// SURCHARGES D'OPERATEURS NON-MEMBRES
				friend bool operator==( const vector& lhs, const vector& rhs )
				{ return lhs.size() == rhs.size() && ft::equal( lhs.begin(), lhs.end(), rhs.begin() ); }

				friend bool operator!=( const vector& lhs, const vector& rhs )
				{ return !( lhs == rhs ); }

				friend bool operator<( const vector& lhs, const vector& rhs )
				{
					for ( size_type i = 0 ; i < lhs.size() && i < rhs.size() ; i++ )
						if ( lhs[ i ] != rhs[ i ] )
							return lhs[ i ] < rhs[ i ];

					return lhs.size() < rhs.size();
				}

				friend bool operator<=( const vector& lhs, const vector& rhs )
				{
					for ( size_type i = 0 ; i < lhs.size() && i < rhs.size() ; i++ )
						if ( lhs[ i ] != rhs[ i ] )
							return lhs[ i ] < rhs[ i ];

					return lhs.size() <= rhs.size();
				}

				friend bool operator>( const vector& lhs, const vector& rhs )
				{
					for ( size_type i = 0 ; i < lhs.size() && i < rhs.size() ; i++ )
						if ( lhs[ i ] != rhs[ i ] )
							return lhs[ i ] > rhs[ i ];

					return lhs.size() > rhs.size();
				}

				friend bool operator>=( const vector& lhs, const vector& rhs )
				{
					for ( size_type i = 0 ; i < lhs.size() && i < rhs.size() ; i++ )
						if ( lhs[ i ] != rhs[ i ] )
							return lhs[ i ] > rhs[ i ];

					return lhs.size() >= rhs.size();
				}

				// ELEMENTS D'ACCES
				allocator_type get_allocator( void ) const
				{ return _allocator; }

				reference at( size_type pos )
				{
					if ( pos >= _size )
					{
						std::ostringstream	pos_str;
						std::ostringstream	size_str;

						pos_str << pos;
						size_str << _size;
						throw std::out_of_range( "vector::_M_range_check: __n (which is " + pos_str.str() + ") >= this->size() (which is " + size_str.str() + ")" );
					}
					return _container[ pos ];
				}

				const_reference at( size_type pos ) const
				{
					if ( pos >= _size )
					{
						std::ostringstream	pos_str;
						std::ostringstream	size_str;

						pos_str << pos;
						size_str << _size;
						throw std::out_of_range( "vector::_M_range_check: __n (which is " + pos_str.str() + ") >= this->size() (which is " + size_str.str() + ")" );
					}
					return _container[ pos ];
				}

				reference front( void )
				{ return _container[ 0 ]; }

				const_reference front( void ) const
				{ return _container[ 0 ]; }

				reference back( void )
				{ return _container[ _size - 1 ]; }

				const_reference back( void ) const
				{ return _container[ _size - 1 ]; }

				pointer data( void )
				{ return _container; }

				const_pointer data( void ) const
				{ return _container; }

				// ITERATEURS
				iterator begin( void )
				{ return iterator( &( _container[ 0 ] ) ); }

				const_iterator begin( void ) const
				{ return const_iterator( &( _container[ 0 ] ) ); }

				iterator end( void )
				{ return iterator( &( _container[ _size ] ) ); }

				const_iterator end( void ) const
				{ return const_iterator( &( _container[ _size ] ) ); }

				reverse_iterator rbegin( void )
				{ return reverse_iterator( end() ); }

				const_reverse_iterator rbegin( void ) const
				{ return const_reverse_iterator( end() ); }

				reverse_iterator rend( void )
				{ return reverse_iterator( begin() ); }

				const_reverse_iterator rend( void ) const
				{ return const_reverse_iterator( begin() ); }

				// CAPACITE
				bool empty( void ) const
				{ return _size == 0; }

				size_type size( void ) const
				{ return _size; }

				size_type max_size( void ) const
				{ return _allocator.max_size(); }

				void reserve( size_type new_cap )
				{
					if ( new_cap > max_size() )
						throw std::length_error( "vector::reserve" );

					if ( new_cap > _capacity )
					{
						pointer 	backup = _allocator.allocate( new_cap );
						size_type	i;

						for ( i = 0 ; i < _size ; i++ )
							_allocator.construct( backup + i, *( _container + i ) );
						destroy_content();
						_size = i;
						_capacity = new_cap;
						_container = backup;
					}
				}

				size_type capacity( void ) const
				{ return _capacity; }

				// MODIFIEURS
				void assign( size_type count, const_reference value )
				{
					if ( max_size() < count )
						throw std::length_error( "cannot create std::vector larger than max_size()" );
					if ( _capacity < count )
						realloc( count );
					else
						clear();
					for ( size_type i = 0 ; i < count ; i++ )
						push_back( value );
				}

				template < class Iter >
				void assign( Iter first, Iter last,
				typename enable_if< !is_integral< Iter >::value, Iter >::type* = 0 )
				{
					vector temp;
					for ( ; first != last ; first++ )
						temp.push_back( *first );

					const size_type count = temp._size;

					if ( _capacity < count )
						realloc( count );
					else
						clear();
					for ( iterator temp_it = temp.begin(); temp_it != temp.end() ; temp_it++ )
						push_back( *temp_it );
				}

				void clear( void )
				{
					for ( size_type i = 0; i < _size; i++ )
						_allocator.destroy( _container + i );
					_size = 0;
				}

				iterator insert( iterator pos, const_reference value )
				{
					const size_type diff = pos - begin();

					if ( !_capacity )
						realloc( 1 );
					if ( _size == _capacity )
					{
						pointer 	backup = _allocator.allocate( _size * 2 );
						size_type	i;

						for ( i = 0 ; i < _size ; i++ )
							_allocator.construct( backup + i, *( _container + i ) );
						destroy_content();
						_size = i;
						_capacity = _size * 2;
						_container = backup;
					}

					pos = begin() + diff;
					_allocator.construct( _container + _size, value );
					for ( iterator temp = end(); temp != pos ; temp-- )
						*temp = *( temp - 1 );
					*pos = value;
					_size++;

					return pos;
				}

				void insert( iterator pos, size_type count, const_reference value )
				{
					const size_type	diff = pos - begin();
					size_type		i;

					if ( !count )
						return ;
					if ( max_size() < count )
						throw std::length_error( "cannot create std::vector larger than max_size()" );

					if ( _size + count > _capacity )
					{
						pointer 	backup;
						size_type	new_size;
						size_type	i;

						if ( count > _size )
							new_size =_size + count;
						else
							new_size = _size * 2;

						backup = _allocator.allocate( new_size );

						for ( i = 0 ; i < _size ; i++ )
							_allocator.construct( backup + i, *( _container + i ) );
						destroy_content();
						_size = i;
						_capacity = new_size;
						_container = backup;
					}

					for ( i = _size ; i < _size + count ; i++ )
						_allocator.construct( _container + i, value_type() );
					if ( diff < _size )
						for ( i = _size + count - 1 ; i > diff + count - 1 ; i-- )
							*( begin() + i ) = *( begin() + i - count );
					pos = begin() + diff;
					for ( i = 0 ; i < count ; i++ )
						*( pos + i ) = value;
					_size += count;
				}

				template < class Iter >
				void insert( iterator pos, Iter first, Iter last,
				typename enable_if< !is_integral< Iter >::value, Iter >::type* = 0 )
				{
					vector temp;
					for ( ; first != last ; first++ )
						temp.push_back( *first );

					const size_type	count = temp._size;
					const size_type	diff = pos - begin();
					size_type		i;

					if ( _size + count > _capacity )
					{
						pointer 	backup;
						size_type	new_size;
						size_type	i;

						if ( count > _size )
							new_size =_size + count;
						else
							new_size = _size * 2;

						backup = _allocator.allocate( new_size );

						for ( i = 0 ; i < _size ; i++ )
							_allocator.construct( backup + i, *( _container + i ) );
						destroy_content();
						_size = i;
						_capacity = new_size;
						_container = backup;
					}

					for ( i = _size ; i < _size + count ; i++ )
						_allocator.construct( _container + i, value_type() );
					if ( diff < _size )
						for ( i = _size + count - 1 ; i > diff + count - 1 ; i-- )
							*( begin() + i ) = *( begin() + i - count );
					pos = begin() + diff;
					for ( i = 0 ; i < count ; i++ )
						*( pos + i ) = *( temp.begin() + i );
					_size += count;
				}

				iterator erase( iterator pos )
				{
					for ( iterator temp = pos ; temp != end() - 1 ; temp++ )
						*temp = *( temp + 1 );
					pop_back();
					return pos;
				}

				iterator erase( iterator first, iterator last )
				{
					const size_type count = last - first;

					if ( last != end() )
						for ( iterator temp = first ; temp + count != end() ; temp++ )
							*temp = *( temp + count );
					for ( size_type i = 0 ; i < count ; i++ )
						pop_back();

					return first;
				}

				void push_back( const value_type& value )
				{
					if ( !_capacity )
						realloc( 1 );
					if ( _size == _capacity )
					{
						pointer 	backup = _allocator.allocate( _size * 2 );
						size_type	i;

						for ( i = 0 ; i < _size ; i++ )
							_allocator.construct( backup + i, *( _container + i ) );
						destroy_content();
						_size = i;
						_capacity = _size * 2;
						_container = backup;
					}
					_allocator.construct( _container + _size, value );
					_size++;
				}

				void pop_back( void )
				{
					_allocator.destroy( _container + _size - 1 );
					if ( _size )
						_size--;
				}

				void resize( size_type count, value_type value = value_type() )
				{
					if ( count > max_size() )
						throw std::length_error( "vector::_M_fill_insert" );
					if ( count < _size )
						while ( _size != count )
							pop_back();
					if ( count > _size )
					{
						size_type i;

						if ( count > _capacity )
						{
							pointer backup = _allocator.allocate( count );

							for ( i = 0 ; i < _size ; i++ )
								_allocator.construct( backup + i, *( _container + i ) );
							destroy_content();
							_size = i;
							_capacity = count;
							_container = backup;
						}
						for ( i = _size ; i != count ; i++ )
							push_back( value );
					}
				}

				void swap( vector& other )
				{
					size_type	temp_capacity = other._capacity;
					size_type	temp_size = other._size;
					pointer		temp_container = other._container;

					other._capacity = _capacity;
					other._size = _size;
					other._container = _container;
					_capacity = temp_capacity;
					_size = temp_size;
					_container = temp_container;
				}

			private :

				// VARIABLES
				allocator_type	_allocator;
				size_type		_capacity;
				size_type		_size;
				pointer			_container;

				// ALLOCATION
				void destroy_content( void )
				{
					if ( _container )
					{
						clear();
						_allocator.deallocate( _container, _capacity );
					}
				}

				void realloc( size_type value )
				{
					destroy_content();
					_container = _allocator.allocate( value );
					_capacity = value;
				}
		};

		// FONCTIONS NON-MEMBRES
		template < class value_type, class allocator_type >
		void swap( vector< value_type, allocator_type >& lhs, vector< value_type, allocator_type >& rhs )
		{ lhs.swap( rhs ); }
	}

#endif
