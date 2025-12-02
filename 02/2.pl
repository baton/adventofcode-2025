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
		for( my $j = 1; $j != $l; ++$j )
		{
			next if( $l % $j != 0 );
			my @c = $t =~ /.{$j}/g;
			my $v = 0;
			foreach my $k ( @c )
			{
				++$v if( $k eq $c[ 0 ] );
			}
			if( $v == $#c + 1 )
			{
				$sum += $i;
				last;
			}
		}
	}
}

print "result = $sum\n";
