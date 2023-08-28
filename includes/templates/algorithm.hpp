#ifndef ALGORITHM
	#define ALGORITHM

	namespace ft
	{
		// EQUAL
		template< class Iter1, class Iter2 >
		bool equal( Iter1 first1, Iter1 last1, Iter2 first2 )
		{
			for ( ; first1 != last1 ; ++first1, ++first2 )
				if ( !( *first1 == *first2 ) )
					return false;
			return true;
		}

		template< class Iter1, class Iter2, class BinaryPredicate >
		bool equal( Iter1 first1, Iter1 last1, Iter2 first2, BinaryPredicate bp )
		{
			for ( ; first1 != last1 ; ++first1, ++first2 )
				if ( !bp( *first1, *first2 ) )
					return false;
			return true;
		}
	}

#endif