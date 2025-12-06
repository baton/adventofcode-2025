#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <numeric>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );
	std::vector< std::string > v;
	for( std::string s; std::getline( ifs, s ); )
		v.emplace_back( s );

	uint64_t sum{ 0 };
	std::vector< uint64_t > a;
	for( size_t i{ 0 }; i != v[ 0 ].size(); ++i )
	{
		size_t const n{ v[ 0 ].size() - i - 1 };

		std::string s;
		for( size_t j{ 0 }; j != v.size() - 1; ++j )
			s.push_back( v[ j ][ n ] );
		if( std::count_if( s.begin(), s.end(), []( char const c ) -> bool { return std::isdigit( c ); } ) == 0 )
			continue;

		a.emplace_back( std::stoull( s ) );
		if( v[ v.size() - 1 ][ n ] == ' ' )
			continue;

		bool const op{ v[ v.size() - 1 ][ n ] == '+' };
		sum += std::accumulate( a.begin(), a.end(),
			op ? 0ULL : 1ULL,
			[ &op ]( uint64_t const x, uint64_t const y ) -> uint64_t
			{
				return op ? x + y : x * y;
			}
		);

		a.clear();
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}