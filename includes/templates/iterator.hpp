#ifndef ITERATOR
	#define ITERATOR

	#include <iterator> // --> std::iterator_tags, std::allocator, std::size_t, std::ptrdiff_t, std::exceptions, std::less, "NULL" )
	#include "iostream"
	#include "utility.hpp"

	namespace ft
	{
		// ITERATOR TRAITS
		template< class Iter >
		struct iterator_traits
		{
			// TYPES DE STRUCT
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
		};

		template< class T >
		struct iterator_traits< T* >
		{
			// TYPES DE STRUCT
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;
		};

		template< class T >
		struct iterator_traits< const T* >
		{
			// TYPES DE STRUCT
			typedef std::ptrdiff_t					difference_type;
			typedef T								value_type;
			typedef const T*						pointer;
			typedef const T&						reference;
			typedef std::random_access_iterator_tag	iterator_category;
		};

		// BASE ITERATOR
		template < class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
		class base_iterator
		{
			public :

				// TYPES DE CLASSE
				typedef T			value_type;
				typedef Distance	difference_type;
				typedef Pointer		pointer;
				typedef Reference	reference;
				typedef Category	iterator_category;

				// CONSTRUCTEURS + DESTRUCTEUR
				base_iterator() :
				_ptr( NULL )
				{}

				base_iterator( pointer ptr ) :
				_ptr( ptr )
				{}

				base_iterator( const base_iterator& src ) :
				_ptr( NULL )
				{ *this = src; }

				virtual ~base_iterator()
				{}

				// SURCHARGES D'OPERATEURS MEMBRES
				base_iterator& operator=( const base_iterator& src )
				{
					_ptr = src._ptr;
					return *this;
				}

				operator base_iterator< iterator_category, const value_type, difference_type, const pointer, const reference >() const
				{ return base_iterator< iterator_category, const value_type, difference_type, const pointer, const reference >( _ptr ); }

				// ELEMENTS D'ACCES
				pointer base() const
				{ return _ptr; }

			protected :

				// VARIABLES
				pointer	_ptr;
		};

		// BASE ITERATOR - SURCHARGES D'OPERATEURS NON-MEMBRES
		template < class Category, class T1, class T2 >
		bool operator==( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() == rhs.base(); };

		template < class Category, class T1, class T2 >
		bool operator!=( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() != rhs.base(); };

		template < class Category, class T1, class T2 >
		bool operator<( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() < rhs.base(); };

		template < class Category, class T1, class T2 >
		bool operator<=( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() <= rhs.base(); };

		template < class Category, class T1, class T2 >
		bool operator>( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() > rhs.base(); };

		template < class Category, class T1, class T2 >
		bool operator>=( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() >= rhs.base(); };

		template < class Category, class T >
		base_iterator< Category, T > operator+( typename base_iterator< Category, T >::difference_type n, const base_iterator< Category, T >& it )
		{ return base_iterator< Category, T >( it.base() + n ); }

		template < class Category, class T1, class T2 >
		typename base_iterator< Category, T1 >::difference_type operator-( const base_iterator< Category, T1 >& lhs, const base_iterator< Category, T2 >& rhs )
		{ return lhs.base() - rhs.base();}

		// VECTOR ITERATOR
		template < class U >
		class vector_iterator : public base_iterator< std::random_access_iterator_tag, U >
		{
			public :

				// CONSTRUCTEURS + DESTRUCTEUR
				vector_iterator() :
				base_iterator< std::random_access_iterator_tag, U >::base_iterator()
				{}

				vector_iterator( typename base_iterator< std::random_access_iterator_tag, U >::pointer ptr ) :
				base_iterator< std::random_access_iterator_tag, U >::base_iterator( ptr )
				{}

				vector_iterator( const vector_iterator& src ) :
				base_iterator< std::random_access_iterator_tag, U >::base_iterator( src )
				{}

				~vector_iterator()
				{}

				// SURCHARGES D'OPERATEURS MEMBRES
				typename base_iterator< std::random_access_iterator_tag, U >::pointer operator->() const
				{ return this->_ptr; }

				typename base_iterator< std::random_access_iterator_tag, U >::reference operator*() const
				{ return *( this->_ptr ); }

				typename base_iterator< std::random_access_iterator_tag, U >::reference operator[]( typename base_iterator< std::random_access_iterator_tag, U >::difference_type n ) const
				{ return this->_ptr[ n ]; }

				operator vector_iterator< const U >() const
				{ return vector_iterator< const U >( this->_ptr ); }

				vector_iterator& operator++()
				{
					this->_ptr++;
					return *this;
				}

				vector_iterator operator++( int )
				{
					vector_iterator tmp = *this;
					operator++();
					return tmp;
				}

				vector_iterator& operator--()
				{
					this->_ptr--;
					return *this;
				}

				vector_iterator operator--( int )
				{
					vector_iterator tmp = *this;
					operator--();
					return tmp;
				}

				vector_iterator operator+( typename base_iterator< std::random_access_iterator_tag, U >::difference_type n ) const
				{ return vector_iterator( this->_ptr + n ); }

				vector_iterator operator-( typename base_iterator< std::random_access_iterator_tag, U >::difference_type n ) const
				{ return vector_iterator( this->_ptr - n ); }

				vector_iterator& operator+=( typename base_iterator< std::random_access_iterator_tag, U >::difference_type n )
				{
					this->_ptr += n;
					return *this;
				}

				vector_iterator& operator-=( typename base_iterator< std::random_access_iterator_tag, U >::difference_type n )
				{
					this->_ptr -= n;
					return *this;
				}
		};

		// VECTOR ITERATOR - SURCHARGES D'OPERATEURS NON-MEMBRES
		template < class U1, class U2 >
		bool operator==( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() == rhs.base(); };

		template < class U1, class U2 >
		bool operator!=( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() != rhs.base(); };

		template < class U1, class U2 >
		bool operator<( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() < rhs.base(); };

		template < class U1, class U2 >
		bool operator<=( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() <= rhs.base(); };

		template < class U1, class U2 >
		bool operator>( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() > rhs.base(); };

		template < class U1, class U2 >
		bool operator>=( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() >= rhs.base(); };

		template < class U >
		vector_iterator< U > operator+( typename vector_iterator< U >::difference_type n, const vector_iterator< U >& it )
		{ return vector_iterator< U >( it.base() + n ); }

		template < class U1, class U2 >
		typename vector_iterator< U1 >::difference_type operator-( const vector_iterator< U1 >& lhs, const vector_iterator< U2 >& rhs )
		{ return lhs.base() - rhs.base();}

		// MAP ITERATOR
		template < class U, class Ptr, class Ref >
		class map_iterator : public base_iterator< std::bidirectional_iterator_tag, U >
		{
			public :

				// TYPES DE CLASSE
				typedef Ptr	to_point;
				typedef Ref	to_ref;

				// CONSTRUCTEURS + DESTRUCTEUR
				map_iterator() :
				base_iterator< std::bidirectional_iterator_tag, U >::base_iterator()
				{}

				map_iterator( typename base_iterator< std::bidirectional_iterator_tag, U >::pointer ptr ) :
				base_iterator< std::bidirectional_iterator_tag, U >::base_iterator( ptr )
				{}

				template< class X, class Y, class Z >
				map_iterator( const map_iterator< X, Y, Z >& src ) :
				base_iterator< std::bidirectional_iterator_tag, U >::base_iterator( src )
				{}

				~map_iterator()
				{}

				// SURCHARGES D'OPERATEURS MEMBRES
				map_iterator& operator=( const map_iterator& src )
				{
					this->_ptr = src._ptr;
					return *this;
				}

				Ptr operator->() const
				{ return this->_ptr->_pair; }

				Ref operator*() const
				{ return *( this->_ptr->_pair ); }

				operator map_iterator< const U, const Ptr, const Ref >() const
				{ return map_iterator< const U, const Ptr, const Ref >( this->_ptr ); }

				map_iterator& operator++()
				{
					if ( this->_ptr->_child2 )
					{
						this->_ptr = this->_ptr->_child2;
						while ( this->_ptr->_child1 )
							this->_ptr = this->_ptr->_child1;
					}
					else
					{
						U* index = this->_ptr->_parent;
						for ( ; index && this->_ptr == index->_child2 ; index = index->_parent )
							this->_ptr = index;
						this->_ptr = index;
					}
					return *this;
				}

				map_iterator operator++( int )
				{
					map_iterator tmp = *this;
					operator++();
					return tmp;
				}

				map_iterator& operator--()
				{
					if ( this->_ptr->_child1 )
					{
						this->_ptr = this->_ptr->_child1;
						while ( this->_ptr->_child2 )
							this->_ptr = this->_ptr->_child2;
					}
					else
					{
						U* index = this->_ptr->_parent;
						for ( ; index && this->_ptr == index->_child1 ; index = index->_parent )
							this->_ptr = index;
						this->_ptr = index;
					}
					return *this;
				}

				map_iterator operator--( int )
				{
					map_iterator tmp = *this;
					operator--();
					return tmp;
				}

				// ELEMENTS D'ACCES
				Ptr base() const
				{ return this->_ptr->_pair; }

				U* data() const
				{ return this->_ptr; }
		};

		// MAP ITERATOR - SURCHARGES D'OPERATEURS NON-MEMBRES
		template < class U1, class U2, class Ptr, class Ref >
		bool operator==( const map_iterator< U1, Ptr, Ref >& lhs, const map_iterator< U2, Ptr, Ref >& rhs )
		{ return lhs.base() == rhs.base(); };

		template < class U1, class U2, class Ptr, class Ref >
		bool operator!=( const map_iterator< U1, Ptr, Ref >& lhs, const map_iterator< U2, Ptr, Ref >& rhs )
		{ return lhs.base() != rhs.base(); };

		template < class U1, class U2, class Ptr, class Ref >
		bool operator<( const map_iterator< U1, Ptr, Ref >& lhs, const map_iterator< U2, Ptr, Ref >& rhs )
		{ return lhs.base() < rhs.base(); };

		template < class U1, class U2, class Ptr, class Ref >
		bool operator<=( const map_iterator< U1, Ptr, Ref >& lhs, const map_iterator< U2, Ptr, Ref >& rhs )
		{ return lhs.base() <= rhs.base(); };

		template < class U1, class U2, class Ptr, class Ref >
		bool operator>( const map_iterator< U1, Ptr, Ref >& lhs, const map_iterator< U2, Ptr, Ref >& rhs )
		{ return lhs.base() > rhs.base(); };

		template < class U1, class U2, class Ptr, class Ref >
		bool operator>=( const map_iterator< U1, Ptr, Ref >& lhs, const map_iterator< U2, Ptr, Ref >& rhs )
		{ return lhs.base() >= rhs.base(); };

		// VECTOR REVERSE ITERATOR
		template< class Iter >
		class vector_rev_iter
		{
			public :

				// TYPES DE CLASSE
				typedef Iter															iterator_type;
				typedef typename iterator_traits< iterator_type >::iterator_category	iterator_category;
				typedef typename iterator_traits< iterator_type >::value_type			value_type;
				typedef typename iterator_traits< iterator_type >::difference_type		difference_type;
				typedef typename iterator_traits< iterator_type >::pointer				pointer;
				typedef typename iterator_traits< iterator_type >::reference			reference;

				// CONSTRUCTEURS + DESTRUCTEUR
				vector_rev_iter() :
				_current( iterator_type() )
				{}

				explicit vector_rev_iter( iterator_type it ) :
				_current( it )
				{}

				template< class Iter2 >
				vector_rev_iter( const vector_rev_iter< Iter2 >& rev_it ) :
				_current( rev_it.base() )
				{}

				~vector_rev_iter()
				{}

				// SURCHARGES D'OPERATEURS MEMBRES
				template< class Iter2 >
				vector_rev_iter& operator=( const vector_rev_iter< Iter2 >& other )
				{
					_current = other.base();
					return *this;
				}

				reference operator*() const
				{ return *( _current.base() - 1 ); }

				pointer operator->() const
				{ return &( operator*() );}

				reference operator[]( difference_type n ) const
				{ return _current[ -n - 1 ]; }

				operator vector_rev_iter< const iterator_type >() const
				{ return vector_rev_iter< const iterator_type >( _current ); }

				vector_rev_iter& operator++()
				{
					--_current;
					return *this;
				}

				vector_rev_iter operator++( int )
				{
					vector_rev_iter temp = *this;

					operator++();
					return temp;
				}

				vector_rev_iter& operator--()
				{
					++_current;
					return *this;
				}

				vector_rev_iter operator--( int )
				{
					vector_rev_iter temp = *this;

					operator--();
					return temp;
				}

				vector_rev_iter operator+( difference_type n ) const
				{ return vector_rev_iter< iterator_type >( _current - n ); }

				vector_rev_iter operator-( difference_type n ) const
				{ return vector_rev_iter< iterator_type >( _current + n ); }

				vector_rev_iter& operator+=( difference_type n )
				{
					_current -= n;
					return *this;
				}

				vector_rev_iter& operator-=( difference_type n )
				{
					_current += n;
					return *this;
				}

				// ELEMENTS D'ACCES
				iterator_type base() const
				{ return _current; }

			protected :

				// VARIABLES
				iterator_type _current;
		};

		// VECTOR REVERSE ITERATOR - SURCHARGES D'OPERATEURS NON-MEMBRES
		template< class Iter1, class Iter2 >
		bool operator==( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return lhs.base() == rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator!=( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return lhs.base() != rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator<( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return lhs.base() > rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator<=( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return lhs.base() >= rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator>( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return lhs.base() < rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator>=( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return lhs.base() <= rhs.base(); }

		template< class Iter >
		vector_rev_iter< Iter > operator+( typename vector_rev_iter< Iter >::difference_type n, const vector_rev_iter< Iter >& it )
		{ return vector_rev_iter< Iter >( it.base() - n ); }

		template< class Iter1, class Iter2 >
		typename vector_rev_iter< Iter1 >::difference_type operator-( const vector_rev_iter< Iter1 >& lhs, const vector_rev_iter< Iter2 >& rhs )
		{ return rhs.base() - lhs.base(); }

		// MAP REVERSE ITERATOR
		template< class Iter >
		class map_rev_iter
		{
			public :

				// TYPES DE CLASSE
				typedef Iter															iterator_type;
				typedef typename iterator_traits< iterator_type >::iterator_category	iterator_category;
				typedef typename iterator_traits< iterator_type >::value_type			value_type;
				typedef typename iterator_traits< iterator_type >::difference_type		difference_type;
				typedef typename iterator_traits< iterator_type >::pointer				pointer;
				typedef typename iterator_traits< iterator_type >::reference			reference;

				// CONSTRUCTEURS + DESTRUCTEUR
				map_rev_iter() :
				_current( iterator_type() )
				{}

				explicit map_rev_iter( iterator_type it ) :
				_current( it )
				{}

				template< class Iter2 >
				map_rev_iter( const map_rev_iter< Iter2 >& rev_it ) :
				_current( rev_it.base() )
				{}

				~map_rev_iter()
				{}

				// SURCHARGES D'OPERATEURS MEMBRES
				template< class Iter2 >
				map_rev_iter& operator=( const map_rev_iter< Iter2 >& other )
				{
					_current = other.base();
					return *this;
				}

				typename Iter::to_ref operator*() const
				{
					iterator_type index = _current;
					index--;
					return *( index.base() );
				}

				typename Iter::to_point operator->() const
				{ return &( operator*() ); }

				operator map_rev_iter< const iterator_type >() const
				{ return map_rev_iter< const iterator_type >( _current ); }

				map_rev_iter& operator++()
				{
					--_current;
					return *this;
				}

				map_rev_iter operator++( int )
				{
					map_rev_iter temp = *this;

					operator++();
					return temp;
				}

				map_rev_iter& operator--()
				{
					++_current;
					return *this;
				}

				map_rev_iter operator--( int )
				{
					map_rev_iter temp = *this;

					operator--();
					return temp;
				}

				// ELEMENTS D'ACCES
				iterator_type base() const
				{ return _current; }

			protected :

				// VARIABLES
				iterator_type _current;
		};

		// MAP REVERSE ITERATOR - SURCHARGES D'OPERATEURS NON-MEMBRES
		template< class Iter1, class Iter2 >
		bool operator==( const map_rev_iter< Iter1 >& lhs, const map_rev_iter< Iter2 >& rhs )
		{ return lhs.base() == rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator!=( const map_rev_iter< Iter1 >& lhs, const map_rev_iter< Iter2 >& rhs )
		{ return lhs.base() != rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator<( const map_rev_iter< Iter1 >& lhs, const map_rev_iter< Iter2 >& rhs )
		{ return lhs.base() > rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator<=( const map_rev_iter< Iter1 >& lhs, const map_rev_iter< Iter2 >& rhs )
		{ return lhs.base() >= rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator>( const map_rev_iter< Iter1 >& lhs, const map_rev_iter< Iter2 >& rhs )
		{ return lhs.base() < rhs.base(); }

		template< class Iter1, class Iter2 >
		bool operator>=( const map_rev_iter< Iter1 >& lhs, const map_rev_iter< Iter2 >& rhs )
		{ return lhs.base() <= rhs.base(); }
	}

#endif