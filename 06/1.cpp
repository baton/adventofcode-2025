#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iterator>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );
	std::vector< std::vector< std::string > > v;
	for( std::string s; std::getline( ifs, s ); )
	{
		std::istringstream iss( s );
		v.emplace_back( std::istream_iterator< std::string >( iss ), std::istream_iterator< std::string >() );
	}

	uint64_t sum{ 0 };
	for( size_t i{ 0 }; i != v[ 0 ].size(); ++i )
	{
		bool const op{ v[ v.size() - 1 ][ i ] == "+" };
		uint64_t r{ op ? 0ULL : 1ULL };
		for( size_t j{ 0 }; j != v.size() - 1; ++j )
		{
			uint64_t const x{ std::stoull( v[ j ][ i ] ) };
			if( op )
				r += x;
			else
				r *= x;
		}

		sum += r;
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}