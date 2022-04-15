#!/usr/bin/perl
use strict;
use warnings;

my @wordlist=map{uc$_}<STDIN>;

print "static const int curdlist_count=",scalar @wordlist,";\n";

foreach my $i (0,1,2){
	print "static const unsigned char curdlist$i\[]={";
	foreach(@wordlist){
		chomp;
		my $base26;
		$base26 =ord(substr($_,0,1))-ord('A');
		$base26*=26;
		$base26+=ord(substr($_,1,1))-ord('A');
		$base26*=26;
		$base26+=ord(substr($_,2,1))-ord('A');
		$base26*=26;
		$base26+=ord(substr($_,3,1))-ord('A');
		$base26*=26;
		$base26+=ord(substr($_,4,1))-ord('A');
		$base26=sprintf("%06x",$base26);
		print "0x".substr($base26,$i*2,2).",";
	}
	print "};\n";
}
