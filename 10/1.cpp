#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iterator>
#include <memory>


size_t process( std::string const & data )
{
	std::istringstream iss( data );

	std::list< std::string > sbuttons{ std::istream_iterator< std::string >( iss ), std::istream_iterator< std::string >() };

	std::string const starget{ sbuttons.front() };
	sbuttons.pop_front();

	// That's all about bits!

	uint64_t target{ 0 };
	for( char c : std::string( starget.crbegin(), starget.crend() ) )
		switch( c )
		{
			case '#' : target = ( target << 1 ) | 1; break;
			case '.' : target = ( target << 1 ) | 0; break;
			default: break;
		}

	sbuttons.pop_back(); // joltage

	std::vector< uint64_t > buttons;
	for( std::string const & s : sbuttons )
	{
		std::istringstream isss( s.substr( 1, s.length() - 2 ) );

		uint64_t & button_mask{ buttons.emplace_back() };
		for( std::string ns; std::getline( isss, ns, ',' ); )
			button_mask |= 1 << std::stoul( ns );
	}

	std::map< uint64_t, size_t > lengths;
	lengths.emplace( 0, 0 );

	std::list< std::pair< uint64_t, uint64_t > > front;
	for( uint64_t const btn : buttons )
		front.emplace_back( btn, 1 );

	while( !front.empty() )
	{
		auto const [ val, len ] = front.front();
		front.pop_front();

		auto il{ lengths.find( val ) };
		if( il == lengths.end() )
			lengths.emplace( val, len );
		else if( il->second <= len )
			continue;

		for( uint64_t const btn : buttons )
			front.emplace_back( val ^ btn, len + 1 );
	}

	return lengths[ target ];
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	size_t sum{ 0 };
	for( std::string s; std::getline( ifs, s ); )
		sum += process( s );

	std::cout << "result = " << sum << std::endl;

	return 0;
}