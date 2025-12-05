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

	std::sort( fresh.begin(), fresh.end() );

	uint64_t count{ 0 }, x{ 0 };
	for( auto i{ fresh.cbegin() }; i != fresh.cend(); )
	{
		count += i->second - i->first + 1;
		x = i->second;

		++i;

		while( ( i != fresh.cend() ) && ( i->first <= x ) )
		{
			if( x < i->second )
			{
				count += i->second - x;
				x = i->second;
			}

			++i;
		}
	}

	std::cout << "result = " << count << std::endl;

	return 0;
}