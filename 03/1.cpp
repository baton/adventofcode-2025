#include <iostream>
#include <fstream>
#include <string>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t sum{ 0 };
	for( std::string s; std::getline( ifs, s ); )
	{
		uint64_t n{ 0 };
		for( size_t i{ 0 }; i != s.length() - 1; ++i )
		{
			uint64_t const u{ s[ i ] - '0' };
			for( size_t j{ i + 1 }; j != s.length(); ++j )
			{
				uint64_t const v{ s[ j ] - '0' };
				if( n < ( u * 10 + v ) )
					n = ( u * 10 + v );
			}
		}

		sum += n;
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}