#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

        $variant[1] = "1-input";
        $variant[2] = "2-input";
        $variant[3] = "3-input";
        $variant[4] = "4-input";
        $variant[5] = "5-input";
        $variant[6] = "6-input";

################

for($k = 1; $k <= $#variant; $k++) {
	print "\n################## ($k) :: Cleaning $variant[$k] #####################\n";
	system( "rm -r  $variant[$k]/*  $variant[$k]-PLOTS/*" );
}

	system( "./run4-ALL-prepare-data.pl" );

################
exit;
################

