#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <list>
#include <vector>
#include <set>
#include <algorithm>


int64_t sq( int64_t const a, int64_t const b, int64_t const c, int64_t const d )
{
	return ( std::abs( a - c ) + 1 ) * ( std::abs( b - d ) + 1 );
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::list< std::pair< int64_t, int64_t > > tiles;
	std::set< int64_t > sx, sy;
	for( std::string s; std::getline( ifs, s ); )
	{
		int64_t x{ 0 }, y{ 0 };
		std::sscanf( s.c_str(), "%lld,%lld", &x, &y );

		tiles.emplace_back( x, y );
		sx.emplace( x );
		sy.emplace( y );
	}

	std::vector< int64_t > const gx( sx.cbegin(), sx.cend() );
	std::vector< int64_t > const gy( sy.cbegin(), sy.cend() );

	std::set< std::pair< std::pair< int64_t, int64_t >, std::pair< int64_t, int64_t > > > edges;
	{
		auto [ a, b ] = *std::prev( tiles.cend() );
		for( auto k{ tiles.cbegin() }; k != tiles.cend(); ++k )
		{
			auto const [ c, d ] = *k;

			int64_t const aa{ std::min( a, c ) };
			int64_t const bb{ std::min( b, d ) };
			int64_t const cc{ std::max( a, c ) };
			int64_t const dd{ std::max( b, d ) };

			edges.insert( { { aa, bb }, { cc, dd } } );

			a = c;
			b = d;
		}
	}


	size_t sqmax{ 0 }, counter{ 0 };
	for( auto i{ tiles.cbegin() }; i != std::prev( tiles.cend() ); ++i )
	{
		auto const [ x, y ] = *i;

		for( auto j { std::next( i ) }; j != tiles.cend(); ++j )
		{
			auto const [ u, v ] = *j;

			if( int64_t const s{ sq( x, y, u, v ) }; sqmax < s )
			{
				int64_t const xx{ std::min( x, u ) };
				int64_t const yy{ std::min( y, v ) };
				int64_t const uu{ std::max( x, u ) };
				int64_t const vv{ std::max( y, v ) };

				if( std::find_if( tiles.cbegin(), tiles.cend(),
					[ & ]( auto const & t ) -> bool
					{
						auto const [ m, n ] = t;

						return ( xx < m ) && ( m < uu ) && ( yy < n ) && ( n < vv );
					} ) != tiles.cend() )
				{
					continue;
				}

				bool cross{ false };
				for( auto const & [ p, q ] : edges )
				{
					auto const [ aa, bb ] = p;
					auto const [ cc, dd ] = q;

					if( aa == cc )
					{
						if( ( xx < aa ) && ( aa < uu ) )
							cross = ( bb < yy ) && ( vv < dd );
					}
					else if( bb == dd )
					{
						if( ( yy < bb ) && ( bb < vv ) )
							cross = ( aa < xx ) && ( uu < cc );
					}

					if( cross )
						break;
				}

				if( cross )
					continue;

				bool inner{ true };
				for( auto iy{ std::lower_bound( gy.cbegin(), gy.cend(), yy + 1 ) }; ( iy != gy.cend() ) && inner; ++iy )
				{
					int64_t const ry{ *iy - 1 };
					if( ry >= vv )
						break;

					auto const r{
						std::count_if(
							std::lower_bound( gx.cbegin(), gx.cend(), xx + 1 ), gx.cend(),
							[ &edges, &ry ]( int64_t const rx ) -> bool
							{
								return std::find_if(
									edges.cbegin(), edges.cend(),
									[ &rx, &ry ]( auto const & e ) -> bool
									{
										auto const & [ p, q ] = e;
										if( p.first != q.first )
											return false;
										if( p.first != rx )
											return false;

										return ( p.second < ry ) && ( ry < q.second );
									} ) != edges.cend();
								}
						) };

					inner = ( r % 2 ) != 0;
				}
				if( !inner )
					continue;

				sqmax = s;
			}
		}
	}

	std::cout << "result = " << sqmax << std::endl;

	return 0;
}