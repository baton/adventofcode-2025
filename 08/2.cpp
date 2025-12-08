#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <map>
#include <set>


using jb_t = std::array< int64_t, 3 >;

int64_t d2( jb_t const & a, jb_t const & b ) noexcept
{
	return ( a[ 0 ] - b[ 0 ] ) * ( a[ 0 ] - b[ 0 ] )
		+  ( a[ 1 ] - b[ 1 ] ) * ( a[ 1 ] - b[ 1 ] )
		+  ( a[ 2 ] - b[ 2 ] ) * ( a[ 2 ] - b[ 2 ] );
}

int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< jb_t, size_t > circuits;
	std::set< std::tuple< int64_t, jb_t, jb_t > > closest;
	size_t splits{ 0 };
	for( std::string s; std::getline( ifs, s ); )
	{
		jb_t jb;
		std::sscanf( s.c_str(), "%lld,%lld,%lld", &jb[ 0 ], &jb[ 1 ], &jb[ 2 ] );

		for( auto const & [ x, c ] : circuits )
			closest.emplace( d2( jb, x ), jb, x );
		circuits.emplace( jb, 0 );
	}

	size_t last_circuit{ 0 };
	size_t steps{ circuits.size() > 20 ? 1000ULL : 10ULL };
	int64_t m{ 0 };
	for( auto const & [ d, a, b ] : closest )
	{
		size_t & ca{ circuits[ a ] };
		size_t & cb{ circuits[ b ] };

		if( ca == cb )
		{
			if( ca == 0 )
			{
				ca = cb = ++last_circuit;

				m = a[ 0 ] * b[ 0 ];
			}
		}
		else
		{
			if( ca == 0 )
				ca = cb;
			else if( cb == 0 )
				cb = ca;
			else
			{
				size_t t{ cb };
				for( auto & [ x, c ] : circuits )
					if( c == t )
						c = ca;
			}

			m = a[ 0 ] * b[ 0 ];
		}
	}

	std::cout << "result = " << m << std::endl;

	return 0;
}