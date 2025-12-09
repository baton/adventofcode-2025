#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <list>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::list< std::pair< int64_t, int64_t > > tiles;
	size_t sqmax{ 0 };
	for( std::string s; std::getline( ifs, s ); )
	{
		int64_t x{ 0 }, y{ 0 };
		std::sscanf( s.c_str(), "%lld,%lld", &x, &y );

		for( auto const & [ u, v ] : tiles )
			if( int64_t const sq{ ( std::abs( x - u ) + 1 ) * ( std::abs( y - v ) + 1 ) }; sqmax < sq )
				sqmax = sq;

		tiles.emplace_back( x, y );
	}

	std::cout << "result = " << sqmax << std::endl;

	return 0;
}