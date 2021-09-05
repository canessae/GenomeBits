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
	print "\n################## ($k) :: $variant[$k] #####################\n";

####################################
	$var = $variant[$k];
####################################

system( "mkdir -p $var-PLOTS" );


system( "mkdir -p $var-PLOTS/A-sum01" );
system( "mkdir -p $var-PLOTS/C-sum01" );
system( "mkdir -p $var-PLOTS/G-sum01" );
system( "mkdir -p $var-PLOTS/T-sum01" );

system( "mkdir -p $var-PLOTS/00-FIGURES-PAPER" );


system( "

##-------------------------------------------
	
	./run5-load-X-sum01.pl      $var  A-sum01-complete; 
	./run5-load-X-sum01.pl      $var  C-sum01-complete; 
	./run5-load-X-sum01.pl      $var  G-sum01-complete; 
	./run5-load-X-sum01.pl      $var  T-sum01-complete; 
	
		mv $var-PLOTS/A-sum01-complete* $var-PLOTS/A-sum01;
		mv $var-PLOTS/C-sum01-complete* $var-PLOTS/C-sum01;
		mv $var-PLOTS/G-sum01-complete* $var-PLOTS/G-sum01;
		mv $var-PLOTS/T-sum01-complete* $var-PLOTS/T-sum01;
		
##------------

	./run6-00figures-PAPER.pl  $var-PLOTS
	./run7-ALLfigures-PAPER.pl  $var-PLOTS

##-------------------------------------------

" );

################

}

################
##-------------------------------------------

system( "

	## GENERATE FIGURES PLOTS 
	
	gnuplot -p gp-figures-PAPER-A-FINAL.gnu
	gnuplot -p gp-figures-PAPER-C-FINAL.gnu
	gnuplot -p gp-figures-PAPER-G-FINAL.gnu
	gnuplot -p gp-figures-PAPER-T-FINAL.gnu

" );

##-------------------------------------------
################
exit;
################

