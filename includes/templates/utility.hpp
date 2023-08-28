#ifndef UTILITY
	#define UTILITY

	namespace ft
	{
		// PAIR
		template< class T1, class T2 >
		struct pair
		{
			// TYPES DE STRUCT
			typedef T1	first_type;
			typedef T2	second_type;

			// CONSTRUCTEURS + DESTRUCTEUR
			pair() :
			first( first_type() ),
			second( second_type() )
			{}

			template< class U, class V >
			pair( const pair< U, V >& pr ) :
			first( pr.first ),
			second( pr.second )
			{}

			pair( const first_type& a, const second_type& b ) :
			first( a ),
			second( b )
			{}

			~pair()
			{}

			// SURCHARGES D'OPERATEURS MEMBRES
			pair& operator=( const pair& other )
			{
				first = other.first;
				second = other.second;
				return *this;
			}

			operator pair< const first_type, const second_type >() const
			{ return pair< const first_type, const second_type >( first, second ); }

			// VARIABLES
			first_type	first;
			second_type	second;
		};

		// PAIR - FONCTIONS NON-MEMBRES
		template< class T1, class T2 >
		pair< T1, T2 > make_pair( T1 x, T2 y )
		{ return pair< T1, T2 >( x, y ); }

		// PAIR - SURCHARGES D'OPERATEURS NON-MEMBRES
		template< class T1, class T2 >
		bool operator==( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
		{
			if ( lhs.first != rhs.first || lhs.second != rhs.second )
				return false;
			return true;
		}

		template< class T1, class T2 >
		bool operator!=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
		{ return !( lhs == rhs ); }

		template< class T1, class T2 >
		bool operator<( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
		{
			if ( lhs.first < rhs.first )
				return true;
			if ( lhs.first > rhs.first )
				return false;
			if ( lhs.second < rhs.second )
				return true;
			if ( lhs.second > rhs.second )
				return false;
			return false;
		}

		template< class T1, class T2 >
		bool operator<=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
		{
			if ( lhs.first < rhs.first )
				return true;
			if ( lhs.first > rhs.first )
				return false;
			if ( lhs.second < rhs.second )
				return true;
			if ( lhs.second > rhs.second )
				return false;
			return true;
		}

		template< class T1, class T2 >
		bool operator>( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
		{
			if ( lhs.first < rhs.first )
				return false;
			if ( lhs.first > rhs.first )
				return true;
			if ( lhs.second < rhs.second )
				return false;
			if ( lhs.second > rhs.second )
				return true;
			return false;
		}

		template< class T1, class T2 >
		bool operator>=( const pair< T1, T2 >& lhs, const pair< T1, T2 >& rhs )
		{
			if ( lhs.first < rhs.first )
				return false;
			if ( lhs.first > rhs.first )
				return true;
			if ( lhs.second < rhs.second )
				return false;
			if ( lhs.second > rhs.second )
				return true;
			return true;
		}
	}

#endif