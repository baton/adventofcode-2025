#include <iostream>
#include <fstream>
#include <string>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	int count{ 0 };
	int pos{ 50 };
	while( !ifs.eof() )
	{
		std::string s;
		ifs >> s;

		int const n{ std::stoi( s.substr( 1 ) ) % 100 };
		pos += ( s[ 0 ] == 'R' ? 1 : -1 ) * n;

		if( pos < 0 )
			pos += 100;
		pos %= 100;

		if( pos == 0 )
			++count;
	}

	std::cout << "result = " << count << std::endl;

	return 0;
}