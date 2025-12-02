#

use strict;

my $s = <>;
my $sum = 0;
foreach( split( ',', $s ) )
{
	my( $a, $b ) = split '-';
	for( my $i = int( $a ); $i != int( $b ) + 1; ++$i )
	{
		my $t = $i . "";
		my $l = length( $t );
		next if( $l % 2 != 0 );
		$sum += $i if( substr( $t, 0, $l / 2 ) eq substr( $t, -$l / 2 ) );
	}
}

print "result = $sum\n";
