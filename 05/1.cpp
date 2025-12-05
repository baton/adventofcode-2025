#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <memory>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::pair< uint64_t, uint64_t > > fresh;
	for( std::string s; std::getline( ifs, s ) && !s.empty(); )
	{
		size_t const d{ s.find( '-' ) };
		uint64_t const a{ std::stoull( s ) };
		uint64_t const b{ std::stoull( s.substr( d + 1 ) ) };

		fresh.emplace_back( a, b );
	}

	auto const count{
		std::count_if( std::istream_iterator< uint64_t >( ifs ), std::istream_iterator< uint64_t >(),
			[ &fresh ]( uint64_t const x ) -> bool
			{
				return std::find_if( fresh.begin(), fresh.end(),
					[ &x ]( std::pair< uint64_t, uint64_t > const & f ) -> bool
					{
						return ( f.first <= x ) && ( x <= f.second );
					}
				) != fresh.end();
			}
		)
	};

	std::cout << "result = " << count << std::endl;

	return 0;
}