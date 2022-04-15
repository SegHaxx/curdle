#!/usr/bin/perl
use strict;
use warnings;

my @curdlist=map{uc$_}<STDIN>;

print "static int curdlist_count=",scalar @curdlist,";\n";

print "static unsigned char curdlist[]={\n";
foreach(@curdlist){
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
	print "\t0x";
	print substr($base26,0,2).",0x";
	print substr($base26,2,2).",0x";
	print substr($base26,4,2).",\n";
}
print "};\n";
