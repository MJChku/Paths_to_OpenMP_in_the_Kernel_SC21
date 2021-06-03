#!/usr/bin/perl -w

open(C,".config") or die "can't open config\n";

open(C2, ">.config.new") or die "cannot open output config\n";

$pwd = `pwd`; chomp($pwd);

while ($l=<C>) {
    $l =~ s/CCK_TOP_LEVEL/$pwd/g;
    print C2 $l;
}

`mv .config.new .config`;

    
	
