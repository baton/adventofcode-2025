#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <set>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::set< size_t > beams;
	size_t splits{ 0 };
	for( std::string s; std::getline( ifs, s ); )
	{
		if( beams.empty() )
		{
			beams.emplace( s.find( 'S' ) );

			continue;
		}

		std::set< size_t > b;
		for( auto const beam : beams )
		{
			if( s[ beam ] == '.' )
				b.emplace( beam );
			else
			{
				b.emplace( beam - 1 );
				b.emplace( beam + 1 );

				++splits;
			}
		}

		beams = std::move( b );
	}

	std::cout << "result = " << splits << std::endl;

	return 0;
}