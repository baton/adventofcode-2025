#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <numeric>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< size_t, size_t > beams;
	for( std::string s; std::getline( ifs, s ); )
	{
		if( beams.empty() )
		{
			beams.emplace( s.find( 'S' ), 1 );

			continue;
		}

		std::map< size_t, size_t > b;
		size_t splits{ 0 };
		for( auto const [ beam, times ] : beams )
		{
			if( s[ beam ] == '.' )
				b[ beam ] += times;
			else
			{
				b[ beam - 1 ] += times;
				b[ beam + 1 ] += times;
			}
		}

		beams = std::move( b );
	}

	size_t const timelines{
		std::transform_reduce(
			beams.begin(), beams.end(),
			0ULL,
			std::plus< size_t >(),
			[]( auto const v ) -> size_t
			{
				return v.second;
			}
		)
	};

	std::cout << "result = " << timelines << std::endl;

	return 0;
}