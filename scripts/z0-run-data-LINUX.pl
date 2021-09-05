#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################


# (1) quit unless we have the correct number of input arg
$num_args = $#ARGV;
if ($num_args != 1 && $ARGV[0] == "0") {
    print "\nUsage:  z0-run-data-LINUX.pl   input_nr\n";
    print "\t(Example:  ./z0-run-data-LINUX.pl  1)\n"
;
    exit;
}


## $ARGV[0] corresponds to one input > 0, e.g.: "$ARGV[0] = 1"


        $variant[1] = "$ARGV[0]-input";
	$nr = "$ARGV[0]";


################

for($k = 1; $k <= $#variant; $k++) {
	print "\n################## ($k) :: Cleaning $variant[$k] #####################\n";
	system( "rm -r  $variant[$k]/*  $variant[$k]-PLOTS/*" );
}

	system( "./run4-prepare-data.pl $ARGV[0]" );

################
exit;
################

