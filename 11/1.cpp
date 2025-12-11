#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <iterator>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::map< std::string, std::list< std::string > > devices;
	for( std::string s; std::getline( ifs, s ); )
	{
		std::istringstream iss( s );
		std::list< std::string > const d{ std::istream_iterator< std::string >( iss ), std::istream_iterator< std::string >() };
		devices[ d.front().substr( 0, 3 ) ].assign( std::next( d.cbegin() ), d.cend() );
	}
	
	std::set< std::list< std::string > > paths;
	std::list< std::list< std::string > > front;
	front.push_back( { "you" } );
	while( !front.empty() )
	{
		std::list< std::string > const p{ front.front() };
		front.pop_front();

		if( p.back() == "out" )
		{
			paths.insert( p );

			continue;
		}
		
		for( auto const & o : devices[ p.back() ] )
		{
			std::list< std::string > q{ p };
			q.push_back( o );
			front.push_back( q );
		}
	}

	std::cout << "result = " << paths.size() << std::endl;

	return 0;
}