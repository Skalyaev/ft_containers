#ifndef MAP
	#define MAP

	#include "algorithm.hpp"
	#include "type_traits.hpp"
	#include "iterator.hpp"

	namespace ft
	{
		template < class Key, class T, class Compare = std::less< Key >, class Allocator = std::allocator< pair< const Key, T > > >
		class map
		{
			private :

				// DECLARATIONS ANTICIPEES PRIVEES
				class tree;

			public :

				// TYPES DE CLASSE
				typedef	Key 														key_type;
				typedef	T 															mapped_type;
				typedef	pair< const key_type, mapped_type >							value_type;
				typedef	std::size_t													size_type;
				typedef Compare														key_compare;
				typedef Allocator													allocator_type;
				typedef typename allocator_type::reference							reference;
				typedef typename allocator_type::const_reference					const_reference;
				typedef typename allocator_type::pointer							pointer;
				typedef typename allocator_type::const_pointer						const_pointer;
				typedef map_iterator< tree, pointer, reference >					iterator;
				typedef map_iterator< const tree, const_pointer, const_reference >	const_iterator;
				typedef	map_rev_iter< iterator >									reverse_iterator;
				typedef	map_rev_iter< const_iterator >								const_reverse_iterator;
				typedef typename iterator_traits< iterator >::difference_type		difference_type;

				// ELEMENTS DE COMPARAISON
				class value_compare
				{
					friend class map;

					protected :

						// VARIABLE
						key_compare	_comp;

						// CONSTRUCTEUR
						value_compare( key_compare c ) : _comp( c ) {}

					public :

						// TYPES DE CLASSE
						typedef bool		result_type;
						typedef value_type	first_argument_type;
						typedef value_type	second_argument_type;

						// SURCHARGES D'OPERATEURS MEMBRES
						result_type operator()( const first_argument_type& lhs , const second_argument_type& rhs ) const
						{ return _comp( lhs.first, rhs.first ); }
				};

				key_compare key_comp() const
				{ return _comp; }

				value_compare value_comp() const
				{ return value_compare( key_comp() ); }

				// CONSTRUCTEURS + DESTRUCTEUR
				map() :
				_comp( key_compare() ),
				_allocator( allocator_type() ),
				_size( 0 ),
				_end( _tree_alloc.allocate( sizeof( tree ) ) ),
				_begin( _end ),
				_root( NULL )
				{ _tree_alloc.construct( _end, tree() ); }

				explicit map( const key_compare& comp, const allocator_type& alloc = allocator_type() ) :
				_comp( comp ),
				_allocator( alloc ),
				_size( 0 ),
				_end( _tree_alloc.allocate( sizeof( tree ) ) ),
				_begin( _end ),
				_root( NULL )
				{ _tree_alloc.construct( _end, tree() ); }

				template< class Iter >
				map( Iter first, Iter last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
				typename enable_if< !is_integral< Iter >::value, Iter >::type* = 0 ) :
				_comp( comp ),
				_allocator( alloc ),
				_size( 0 ),
				_end( _tree_alloc.allocate( sizeof( tree ) ) ),
				_begin( _end ),
				_root( NULL )
				{
					_tree_alloc.construct( _end, tree() );
					insert( first, last );
				}

				map( const map& other ) :
				_comp( other.key_comp() ),
				_allocator( other.get_allocator() ),
				_size( 0 ),
				_end( _tree_alloc.allocate( sizeof( tree ) ) ),
				_begin( _end ),
				_root( NULL )
				{
					_tree_alloc.construct( _end, tree() );
					*this = other;
				}

				~map()
				{ destroy_content( _root ); }

				// SURCHARGES D'OPERATEURS MEMBRES
				map& operator=( const map& other )
				{
					clear();
					copy_my_tree( other._root, other._end );
					return *this;
				}

				mapped_type& operator[]( const key_type& key )
				{ return insert( ft::make_pair( key, mapped_type() ) ).first->second; }

				// SURCHARGES D'OPERATEURS NON-MEMBRES
				friend bool operator==( const map& lhs, const map& rhs )
				{ return lhs.size() == rhs.size() && ft::equal( lhs.begin(), lhs.end(), rhs.begin() ); }

				friend bool operator!=( const map& lhs, const map& rhs )
				{ return !( lhs == rhs ); }

				friend bool operator<( const map& lhs, const map& rhs )
				{
					const_iterator it1 = lhs.begin();
					const_iterator it2 = rhs.begin();

					for ( ; it1 != lhs.end() && it2 != rhs.end() ; it1++, it2++ )
					{
						if ( it1->first < it2->first )
							return true;
						if ( it1->first > it2->first )
							return false;
						if ( it1->second < it2->second )
							return true;
						if ( it1->second > it2->second )
							return false;
					}
					return lhs.size() < rhs.size();
				}

				friend bool operator<=( const map& lhs, const map& rhs )
				{
					const_iterator it1 = lhs.begin();
					const_iterator it2 = rhs.begin();

					for ( ; it1 != lhs.end() && it2 != rhs.end() ; it1++, it2++ )
					{
						if ( it1->first < it2->first )
							return true;
						if ( it1->first > it2->first )
							return false;
						if ( it1->second < it2->second )
							return true;
						if ( it1->second > it2->second )
							return false;
					}
					return lhs.size() <= rhs.size();
				}

				friend bool operator>( const map& lhs, const map& rhs )
				{
					const_iterator it1 = lhs.begin();
					const_iterator it2 = rhs.begin();

					for ( ; it1 != lhs.end() && it2 != rhs.end() ; it1++, it2++ )
					{
						if ( it1->first < it2->first )
							return false;
						if ( it1->first > it2->first )
							return true;
						if ( it1->second < it2->second )
							return false;
						if ( it1->second > it2->second )
							return true;
					}
					return lhs.size() > rhs.size();
				}

				friend bool operator>=( const map& lhs, const map& rhs )
				{
					const_iterator it1 = lhs.begin();
					const_iterator it2 = rhs.begin();

					for ( ; it1 != lhs.end() && it2 != rhs.end() ; it1++, it2++ )
					{
						if ( it1->first < it2->first )
							return false;
						if ( it1->first > it2->first )
							return true;
						if ( it1->second < it2->second )
							return false;
						if ( it1->second > it2->second )
							return true;
					}
					return lhs.size() >= rhs.size();
				}

				// ELEMENTS D'ACCES
				allocator_type get_allocator() const
				{ return _allocator; }

				mapped_type& at( const key_type& key )
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( ref.second == -1 )
						return ref.first->_pair->second;
					throw std::out_of_range( "map::at" );
				}

				const mapped_type& at( const key_type& key ) const
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( ref.second == -1 )
						return ref.first->_pair->second;
					throw std::out_of_range( "map::at" );
				}

				// ITERATEURS
				iterator begin()
				{ return iterator( _begin ); }

				const_iterator begin() const
				{ return const_iterator( _begin ); }

				iterator end()
				{ return iterator( _end ); }

				const_iterator end() const
				{ return const_iterator( _end ); }

				reverse_iterator rbegin()
				{ return reverse_iterator( end() ); }

				const_reverse_iterator rbegin() const
				{ return const_reverse_iterator( end() ); }

				reverse_iterator rend()
				{ return reverse_iterator( begin() ); }

				const_reverse_iterator rend() const
				{ return const_reverse_iterator( begin() ); }

				// CAPACITE
				bool empty( void ) const
				{ return _size == 0; }

				size_type size( void ) const
				{ return _size; }

				size_type max_size( void ) const
				{ return ( _tree_alloc.max_size() + _allocator.max_size() ) / 2; }

				// MODIFIEURS
				void clear( void )
				{
					if ( !_size )
						return;

					destroy_content( _root );
					_size = 0;
					_end = _tree_alloc.allocate( sizeof( tree ) );
					_tree_alloc.construct( _end, tree() );
					_begin = _end;
					_root = NULL;
				}

				pair< iterator, bool > insert( const_reference value )
				{
					if ( !_root )
					{
						_root = _tree_alloc.allocate( sizeof( tree ) );
						_tree_alloc.construct( _root, tree( value, NULL, NULL, _end, 0, _allocator ) );
						_begin = _root;
						_end->_parent = _root;
						_size++;
						return pair< iterator, bool >( begin(), true );
					}
					else
					{
						ft::pair< tree*, const long long > ref = tree_search( value.first );
						if ( ref.second == -1 )
							return pair< iterator, bool >( iterator( ref.first ), false );

						if ( _comp( value.first, ref.first->_pair->first ) )
						{
							ref.first->_child1 = _tree_alloc.allocate( sizeof( tree ) );
							_tree_alloc.construct( ref.first->_child1, tree( value, ref.first, NULL, NULL, ref.second + 1, _allocator ) );
							_size++;
							if ( _comp( value.first, _begin->_pair->first ) )
								_begin = ref.first->_child1;
							return pair< iterator, bool >( iterator( ref.first->_child1 ), true );
						}
						else
						{
							short x = 0;
							if ( ref.first->_child2 == _end )
								++x;
							ref.first->_child2 = _tree_alloc.allocate( sizeof( tree ) );
							_tree_alloc.construct( ref.first->_child2, tree( value, ref.first, NULL, NULL, ref.second + 1, _allocator ) );
							_size++;
							if ( x )
							{
								_end->_parent = ref.first->_child2;
								ref.first->_child2->_child2 = _end;
							}
							return pair< iterator, bool >( iterator( ref.first->_child2 ), true );
						}
					}
				}

				iterator insert( iterator position, const_reference value )
				{
					if ( !_root )
					{
						_root = _tree_alloc.allocate( sizeof( tree ) );
						_tree_alloc.construct( _root, tree( value, NULL, NULL, _end, 0, _allocator ) );
						_begin = _root;
						_end->_parent = _root;
						_size++;
						return begin();
					}

					if ( position == end() )
						--position;

					iterator it = position;
					if ( _comp( value.first, it->first ) && ( it == begin() || _comp( ( --it )->first, value.first ) ) )
					{
						if ( it != begin() )
							++it;
						if ( !( it.data()->_child1 ) )
						{
							it.data()->_child1 = _tree_alloc.allocate( sizeof( tree ) );
							_tree_alloc.construct( it.data()->_child1, tree( value, it.data(), NULL, NULL, it.data()->_level + 1, _allocator ) );
							_size++;
							if ( _comp( value.first, _begin->_pair->first ) )
								_begin = it.data()->_child1;
							return iterator( it.data()->_child1 );
						}
					}

					if ( _comp( position->first, value.first ) && ( position == --end() || _comp( value.first, ( ++position )->first ) ) )
					{
						if ( it != --end() )
							--position;
						if ( !( position.data()->_child2 ) )
						{
							short x = 0;
							if ( position.data()->_child2 == _end )
								++x;
							position.data()->_child2 = _tree_alloc.allocate( sizeof( tree ) );
							_tree_alloc.construct( position.data()->_child2, tree( value, position.data(), NULL, NULL, position.data()->_level + 1, _allocator ) );
							++_size;
							if ( x )
							{
								_end->_parent = position.data()->_child2;
								position.data()->_child2->_child2 = _end;
							}
							return iterator( position.data()->_child2 );
						}
					}
					return insert( value ).first;
				}

				template < class Iter >
				void insert( Iter first, Iter last,
				typename enable_if< !is_integral< Iter >::value, Iter >::type* = 0 )
				{
					for ( ; first != last ; first++ )
						insert( *first );
				}

				void erase( iterator position )
				{
					tree* ref = position.data();

					if ( position == end() )
						return ;
					if ( !ref->_child1 && ( !ref->_child2 || ref->_child2 == _end ) )
					{
						if ( ref == _begin )
							_begin = ( ++begin() ).data();
						if ( ref == _root )
						{
							clear();
							return ;
						}
						else if ( ref == ref->_parent->_child1 )
							ref->_parent->_child1 = NULL;
						else if ( ref->_child2 == _end )
						{
							ref->_parent->_child2 = _end;
							_end->_parent = ref->_parent;
						}
						else
							ref->_parent->_child2 = NULL;
						_tree_alloc.destroy( ref );
						_tree_alloc.deallocate( ref, sizeof( tree ) );
						--_size;
					}
					else if ( !ref->_child1 || !ref->_child2 )
					{
						tree* index;
						if ( !ref->_child1 )
							index = ref->_child2;
						else
							index = ref->_child1;
						index->_parent = ref->_parent;
						if ( index != _end)
							index->_level--;
						if ( ref == _begin )
							_begin = ( ++begin() ).data();
						if ( !index->_parent )
							_root = index;
						else
						{
							if ( ref == ref->_parent->_child1 )
								ref->_parent->_child1 = index;
							else
								ref->_parent->_child2 = index;
						}
						if ( _root == _end )
							_root = NULL;
						_tree_alloc.destroy( ref );
						_tree_alloc.deallocate( ref, sizeof( tree ) );
						--_size;
					}
					else if ( ref->_child2 == _end )
					{
						iterator it = end();
						--it;
						--it;
						_end->_parent = it.data();
						it.data()->_child2 = _end;
						if ( ref->_parent )
							ref->_parent->_child2 = ref->_child1;
						else
							_root = ref->_child1;
						ref->_child1->_parent = ref->_parent;
						ref->_child1->_level--;
						_tree_alloc.destroy( ref );
						_tree_alloc.deallocate( ref, sizeof( tree ) );
						--_size;
					}
					else
						replace_here( ref, true );
				}

				size_type erase( const key_type& key )
				{
					ft::pair< tree*, const long long > ref = tree_search( key );

					if ( ref.second == -1 )
					{
						if ( !ref.first->_child1 && ( !ref.first->_child2 || ref.first->_child2 == _end ) )
						{
							if ( ref.first == _begin )
								_begin = ( ++begin() ).data();
							if ( ref.first == _root )
							{
								clear();
								return 1;
							}
							else if ( ref.first == ref.first->_parent->_child1 )
								ref.first->_parent->_child1 = NULL;
							else if ( ref.first->_child2 == _end )
							{
								ref.first->_parent->_child2 = _end;
								_end->_parent = ref.first->_parent;
							}
							else
								ref.first->_parent->_child2 = NULL;
							_tree_alloc.destroy( ref.first );
							_tree_alloc.deallocate( ref.first, sizeof( tree ) );
							--_size;
						}
						else if ( !ref.first->_child1 || !ref.first->_child2 )
						{
							tree* index;
							if ( !ref.first->_child1 )
								index = ref.first->_child2;
							else
								index = ref.first->_child1;
							index->_parent = ref.first->_parent;
							if ( index != _end)
								index->_level--;
							if ( ref.first == _begin )
								_begin = ( ++begin() ).data();
							if ( !index->_parent )
								_root = index;
							else
							{
								if ( ref.first == ref.first->_parent->_child1 )
									ref.first->_parent->_child1 = index;
								else
									ref.first->_parent->_child2 = index;
							}
							if ( _root == _end )
								_root = NULL;
							_tree_alloc.destroy( ref.first );
							_tree_alloc.deallocate( ref.first, sizeof( tree ) );
							--_size;
						}
						else if ( ref.first->_child2 == _end )
						{
							iterator it = end();
							--it;
							--it;
							_end->_parent = it.data();
							it.data()->_child2 = _end;
							if ( ref.first->_parent )
								ref.first->_parent->_child2 = ref.first->_child1;
							else
								_root = ref.first->_child1;
							ref.first->_child1->_parent = ref.first->_parent;
							ref.first->_child1->_level--;
							_tree_alloc.destroy( ref.first );
							_tree_alloc.deallocate( ref.first, sizeof( tree ) );
							--_size;
						}
						else
							replace_here( ref.first, true );
						return 1;
					}
					return 0;
				}

				void erase( iterator first, iterator last )
				{
					iterator old;

					for ( ; _size && first != last ; )
					{
						old = first;
						first++;
						erase( old );
					}
				}

	 			void swap( map& other )
				{
					size_type	temp_size = other._size;
					tree*		temp_begin = other._begin;
					tree*		temp_end = other._end;
					tree*		temp_root = other._root;

					other._size = _size;
					other._begin = _begin;
					other._end = _end;
					other._root = _root;
					_size = temp_size;
					_begin = temp_begin;
					_end = temp_end;
					_root = temp_root;
				}

				// OPERATIONS
				size_type count( const key_type& key ) const
				{
					try
					{ at( key ); }
					catch ( const std::exception& e )
					{ return 0; }
					return 1;
				}

				iterator find( const key_type& key )
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( ref.second == -1 )
						return iterator( ref.first );
					return end();
				}

				const_iterator find( const key_type& key ) const
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( ref.second == -1 )
						return const_iterator( ref.first );
					return end();
				}

				ft::pair< iterator, iterator > equal_range( const key_type& key )
				{ return ft::make_pair( lower_bound( key ), upper_bound( key ) ); }

				ft::pair< const_iterator, const_iterator > equal_range( const key_type& key ) const
				{ return ft::make_pair( lower_bound( key ), upper_bound( key ) ); }

				iterator lower_bound( const key_type& key )
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( ref.second == -1 )
						return iterator( ref.first );
					if ( !ref.first || ref.first == _end )
						return end();
					if ( _comp( key, ref.first->_pair->first ) )
						return iterator( ref.first );
					return ++( iterator( ref.first ) );
				}

				const_iterator lower_bound( const key_type& key ) const
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( ref.second == -1 )
						return const_iterator( ref.first );
					if ( !ref.first || ref.first == _end )
						return end();
					if ( _comp( key, ref.first->_pair->first ) )
						return const_iterator( ref.first );
					return ++( const_iterator( ref.first ) );
				}

				iterator upper_bound( const key_type& key )
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( !ref.first || ref.first == _end )
						return end();
					if ( _comp( key, ref.first->_pair->first ) )
						return iterator( ref.first );
					return ++( iterator( ref.first ) );
				}

				const_iterator upper_bound( const key_type& key ) const
				{
					ft::pair< tree*, const long long > ref = tree_search( key );
					if ( !ref.first || ref.first == _end )
						return end();
					if ( _comp( key, ref.first->_pair->first ) )
						return const_iterator( ref.first );
					return ++( const_iterator( ref.first ) );
				}

			private :

				typedef typename Allocator::template rebind< tree >::other tree_alloc;

				class tree
				{
					public :

						// CONSTRUCTEURS + DESTRUCTEUR
						tree( const allocator_type& alloc = allocator_type() ) :
						_allocator( alloc ),
						_pair( _allocator.allocate( sizeof( value_type ) ) ),
						_parent( NULL ),
						_child1( NULL ),
						_child2( NULL ),
						_level( 0 )
						{ _allocator.construct( _pair, value_type() ); }

						tree( const_reference new_pair, tree* parent, tree* child1, tree* child2, const size_type level, const allocator_type& alloc = allocator_type() ) :
						_allocator( alloc ),
						_pair( _allocator.allocate( sizeof( value_type ) ) ),
						_parent( parent ),
						_child1( child1 ),
						_child2( child2 ),
						_level( level )
						{ _allocator.construct( _pair, new_pair ); }

						tree( const tree& other ) :
						_allocator( other._allocator ),
						_pair( _allocator.allocate( sizeof( value_type ) ) ),
						_parent( other._parent ),
						_child1( other._child1 ),
						_child2( other._child2 ),
						_level( other._level )
						{ _allocator.construct( _pair, *( other._pair ) ); }

						~tree()
						{
							_allocator.destroy( _pair );
							_allocator.deallocate( _pair, sizeof( value_type ) );
						}

						// SURCHARGES D'OPERATEURS MEMBRES
						tree& operator=( const tree& other )
						{
							_allocator.destroy( _pair );
							_allocator.deallocate( _pair, sizeof( value_type ) );
							_pair = _allocator.allocate( sizeof( value_type ) );
							_allocator.construct( _pair, *( other._pair ) );
							_parent = other._parent;
							_child1 = other._child1;
							_child2 = other._child2;
							_level = other._level;
							return *this;
						}

						// VARIABLES
						allocator_type	_allocator;
						pointer			_pair;
						tree*			_parent;
						tree*			_child1;
						tree*			_child2;
						size_type		_level;
				};

				ft::pair< tree*, const long long > tree_search( const key_type key ) const
				{
					tree*		index = _root;
					size_type	level = 0;

					while ( index && index != _end )
					{
						if ( _comp( index->_pair->first, key ) )
						{
							if ( index->_child2 && index->_child2 != _end )
								index = index->_child2;
							else
								return make_pair( index, level );
						}
						else if ( _comp( key, index->_pair->first ) )
						{
							if ( index->_child1 )
								index = index->_child1;
							else
								return make_pair( index, level );
						}
						else
							return make_pair( index, -1 );
						level++;
					}
					return make_pair( index, level );
				}

				tree* find_replacement( tree* pos )
				{
					tree*		index;
					iterator	it( pos );
					it--;
					iterator	itl( it );
					it++;
					it++;
					iterator	itm( it );
					it--;

					if ( _comp( it.data()->_child1->_pair->first, itl->first ) && _comp( itl->first, it.data()->_child2->_pair->first ) )
					{
						if ( _comp( it.data()->_child1->_pair->first, itm->first ) && _comp( itm->first, it.data()->_child2->_pair->first ) )
							it = itm.data()->_level > itl.data()->_level ? itm : itl ;
						else
							it = itl;
					}
					else if ( _comp( it.data()->_child1->_pair->first, itm->first ) && _comp( itm->first, it.data()->_child2->_pair->first ) )
						it = itm;
					else
					{
						index = pos;
						index = index->_child1;
						while ( index->_child2 )
							index = index->_child2;
						index->_child2 = pos->_child2;
						pos->_child2->_parent = index;
						pos->_child1->_parent = pos->_parent;
						if ( pos == _root )
							_root = pos->_child1;
						else if ( pos == pos->_parent->_child1 )
							pos->_parent->_child1 = pos->_child1;
						else
							pos->_parent->_child2 = pos->_child1;
						return NULL;
					}
					if ( it.data()->_child1 && it.data()->_child2 )
					{
						replace_here( it.data(), 0 );
						return it.data();
					}
					if ( !( it.data()->_child1 ) && !( it.data()->_child2 ) )
					{
						if ( it.data() == it.data()->_parent->_child1 )
							it.data()->_parent->_child1 = NULL;
						else
							it.data()->_parent->_child2 = NULL;
						return it.data();
					}
					if ( it.data()->_child1 )
						index = it.data()->_child1;
					else
						index = it.data()->_child2;
					index->_parent = it.data()->_parent;
					if ( it.data() == it.data()->_parent->_child1 )
						it.data()->_parent->_child1 = index;
					else
						it.data()->_parent->_child2 = index;
					return it.data();
				}

				void replace_here( tree* to_replace, bool deleting )
				{
					tree* index = find_replacement( to_replace );

					if ( index )
					{
						index->_parent = to_replace->_parent;
						index->_child1 = to_replace->_child1;
						index->_child2 = to_replace->_child2;
						if ( to_replace == _root )
							_root = index;
						else if ( to_replace == to_replace->_parent->_child1 )
							to_replace->_parent->_child1 = index;
						else
							to_replace->_parent->_child2 = index;
						to_replace->_child1->_parent = index;
						to_replace->_child2->_parent = index;
					}
					if ( !deleting )
						return ;
					_tree_alloc.destroy( to_replace );
					_tree_alloc.deallocate( to_replace, sizeof( tree ) );
					_size--;
				}

				void destroy_content( tree* member )
				{
					if ( !member && _end )
					{
						_tree_alloc.destroy( _end );
						_tree_alloc.deallocate( _end, sizeof( tree ) );
						return ;
					}
					if ( member->_child1 )
						destroy_content( member->_child1 );
					if ( member->_child2 )
					{
						if ( member->_child2 == _end )
							_end = NULL;
						destroy_content( member->_child2 );
					}
					_tree_alloc.destroy( member );
					_tree_alloc.deallocate( member, sizeof( tree ) );
				}

				void copy_my_tree( tree* actual, tree* end )
				{
					if ( !actual )
						return ;

					insert( *( actual->_pair ) );
					copy_my_tree( actual->_child1, end );
					if ( actual->_child2 != end )
						copy_my_tree( actual->_child2, end );
				}

				// VARIABLES
				const key_compare	_comp;
				tree_alloc			_tree_alloc;
				allocator_type		_allocator;
				size_type			_size;
				tree*				_end;
				tree*				_begin;
				tree*				_root;
		};

		// FONCTIONS NON-MEMBRES
		template < class Key, class T, class Compare, class Alloc >
		void swap( map< Key, T, Compare, Alloc >& lhs, map< Key, T, Compare, Alloc >& rhs )
		{ lhs.swap( rhs ); }
	}

#endif
