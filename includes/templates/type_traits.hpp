#ifndef TYPE_TRAITS
	#define TYPE_TRAITS

	namespace ft
	{
		// ENABLE_IF
		template< bool B, class T = void >
		struct enable_if
		{};

		template< class T >
		struct enable_if< true, T >
		{ typedef T type; };

		// INTEGRAL_CONSTANT
		template < class T, T v >
		struct integral_constant
		{
			// TYPES DE STRUCT
			typedef T									value_type;
			typedef integral_constant< value_type, v >	type;

			// SURCHARGES D'OPERATEURS MEMBRES
			operator T()
			{ return value; }

			// VARIABLES
			static const T value = v;
		};

		typedef integral_constant< bool, true >		true_type;
		typedef integral_constant< bool, false >	false_type;

		// IS_INTEGRAL
		template< typename T >
		struct is_integral : public false_type
		{};

		template<>
		struct is_integral< bool > : public true_type
		{};

		template<>
		struct is_integral< signed char > : public true_type
		{};

		template<>
		struct is_integral< unsigned char > : public true_type
		{};

		template<>
		struct is_integral< wchar_t > : public true_type
		{};

		template<>
		struct is_integral< signed short > : public true_type
		{};

		template<>
		struct is_integral< unsigned short > : public true_type
		{};

		template<>
		struct is_integral< signed int > : public true_type
		{};

		template<>
		struct is_integral< unsigned int > : public true_type
		{};

		template<>
		struct is_integral< signed long > : public true_type
		{};

		template<>
		struct is_integral< unsigned long > : public true_type
		{};

		template<>
		struct is_integral< signed long long > : public true_type
		{};

		template<>
		struct is_integral< unsigned long long > : public true_type
		{};
	}

#endif