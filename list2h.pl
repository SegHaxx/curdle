#!/usr/bin/perl
use strict;
use warnings;

my @wordlist=map{uc$_}<STDIN>;

print "static int wordlist_count=",scalar @wordlist,";\n";

print "static char* wordlist={\n";
foreach(@wordlist){
	chomp;
	print qq(\t"$_"\n);
}
print "};\n";
