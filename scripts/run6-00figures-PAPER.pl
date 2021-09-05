#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

if (!$ARGV[0]) {
    print "\nUsage:  zrun7-ALLfigures-PAPER.pl  variant_name-PLOTS\n";
    print "\t(Example:  zrun7-ALLfigures-PAPER.pl  0-UK-Variant-PLOTS)\n";
    exit;
}

    $strg = $ARGV[0];
	

##############################################

$TMP = "tmp";
system( "rm -r $TMP/*" );
system( "ls -1 $strg > $TMP/tmp-files.$$" );

############################################
## create 00-FIGURES-PAPER

	$kk = 0;
open (ALL_VARIANT, "< $TMP/tmp-files.$$");
while ($_ = <ALL_VARIANT>) {
	chop($_);
	##print "$_\n";

	if($_ =~ /^ALL-/ && $_ =~ /.txt$/) {
	$kk++;
		##print "$kk\t$_\n";


		open(FILE_PT, "> $strg/00-FIGURES-PAPER/multi$_");
		open(FILE_PLOT, "< $strg/$_");
		while ($multi_plot = <FILE_PLOT>) {
			##print "$multi_plot"; 


   if($multi_plot =~ /^set terminal/ || $multi_plot =~ /^set output/) { $multi_plot = ""; }
   if($multi_plot =~ /^set title/) {

##----
	if($_ =~ /-sum01-complete.txt$/) { 
     		$multi_plot = "set label \' ' at 4000, 120 font \',20\'\n"; 
	}
	
##----
   }

##-----------------------------------------------------------------------------------------------

		#### File to Plot
		print FILE_PT "$multi_plot"; 


		}
		close(FILE_PLOT);
		close(FILE_PT);
	}

}
close(ALL_VARIANT);

##############################################################################	
exit;
##############################################################################	

