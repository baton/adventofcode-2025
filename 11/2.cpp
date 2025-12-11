#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include <iterator>
#include <algorithm>
#include <array>


using map_t = std::map< std::string, std::list< std::string > >;

enum index_t
{
	all, fft, dac, f_d
};
using counts_t = std::array< uint64_t, 4 >; // all, fft, dac, f_d
using cache_t = std::map< std::string, counts_t >;

counts_t lookup( std::string const & device, map_t & map, cache_t & cache )
{
	if( auto i{ cache.find( device ) }; i != cache.end() )
		return i->second;

	counts_t counts{ 0ULL, 0ULL, 0ULL, 0ULL };
	for( std::string const & d : map[ device ] )
	{
		counts_t const c{ lookup( d, map, cache ) };
		counts[ all ] += c[ all ];
		if( device == "fft" )
		{
			counts[ fft ] += c[ all ];
			counts[ dac ] += c[ dac ];
			counts[ f_d ] += c[ dac ];
		}
		else if( device == "dac" )
		{
			counts[ fft ] += c[ fft ];
			counts[ dac ] += c[ all ];
			counts[ f_d ] += c[ fft ];
		}
		else
		{
			counts[ fft ] += c[ fft ];
			counts[ dac ] += c[ dac ];
			counts[ f_d ] += c[ f_d ];
		}
	}

	cache.insert( { device, counts } );
	return counts;
}

uint64_t lookup( std::string const & device, map_t & devices )
{
	cache_t cache;
	cache.insert( { "out", { 1ULL, 0ULL, 0ULL, 0ULL } } );
	
	return lookup( "svr", devices, cache )[ f_d ];
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	map_t devices;
	for( std::string s; std::getline( ifs, s ); )
	{
		std::istringstream iss( s );
		std::list< std::string > const d{ std::istream_iterator< std::string >( iss ), std::istream_iterator< std::string >() };
		devices[ d.front().substr( 0, 3 ) ].assign( std::next( d.cbegin() ), d.cend() );
	}

	uint64_t const count{ lookup( "svr", devices ) };
	
	std::cout << "result = " << count << std::endl;

	return 0;
}