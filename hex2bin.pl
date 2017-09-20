#!/usr/bin/perl -w
use strict;
while (<>) {
	while (length $_ > 2) {
		print pack 'H2', substr $_, 0, 3;
		$_ = substr $_, 3;
	}
}

