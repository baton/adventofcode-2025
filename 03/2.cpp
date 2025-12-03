#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


size_t constexpr max_len{ 12 };
static_assert( max_len > 1, "too obvoius" );


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t sum{ 0 };
	for( std::string s; std::getline( ifs, s ); )
	{
		std::vector< std::vector< uint64_t > > c( max_len + 1, std::vector< uint64_t >( s.length() + 1, 0ULL ) );

		uint64_t d{ 1 };
		for( size_t l{ 1 }; l != max_len + 1; ++l, d *= 10 )
		{
			uint64_t x{ 0 };
			for( size_t i{ l - 1 }; i != s.length(); ++i )
			{
				size_t const p{ s.length() - i - 1 };
				uint64_t y{ static_cast< uint64_t >( s[ p ] - '0' ) * d + c[ l - 1 ][ p + 1 ] };
				if( x < y )
					x = y;
				c[ l ][ p ] = x;
			}
		}

		sum += c[ max_len ][ 0 ];
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}