#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <iterator>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > m{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	auto count_adjacent = [ &m ]( int const x, int const y ) -> size_t
	{
		size_t c{ 0 };

		for( int dx{ -1 }; dx != 2; ++dx )
			for( int dy{ -1 }; dy != 2; ++dy )
				if( ( ( dx != 0 ) || ( dy != 0 ) )
					&& ( y + dy >= 0 ) && ( y + dy < m.size() )
					&& ( x + dx >= 0 ) && ( x + dx < m[ y ].size() ) )
				{
					if( m[ y + dy ][ x + dx ] == '@' )
						++c;
				}

		return c;
	};

	size_t count{ 0 };

	while( true )
	{
		std::vector< std::pair< size_t, size_t > > r;

		for( int y{ 0 }; y != m.size(); ++y )
			for( int x{ 0 }; x != m[ y ].size(); ++x )
				if( ( m[ y ][ x ] == '@' ) && ( count_adjacent( x, y ) < 4 ) )
					r.emplace_back( y, x );

		if( r.empty() )
			break;

		count += r.size();

		for( auto const & [ y, x ] : r )
			m[ y ][ x ] = 'x';
	}

	std::cout << "result = " << count << std::endl;

	return 0;
}