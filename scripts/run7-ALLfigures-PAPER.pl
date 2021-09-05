#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

	
if (!$ARGV[0]) {
    print "\nUsage:  zrun77-ALLfigures-PAPER.pl  variant_name-PLOTS\n";
    print "\t(Example:  zrun77-ALLfigures-PAPER.pl  0-UK-Variant-PLOTS)\n";
    exit;
}

    $strg = $ARGV[0];
	

##############################################
## Copy multiALL- files 

system( "mkdir -p $strg/00-FIGURES-PAPER/old_multiALL" );
system( "cp -f $strg/00-FIGURES-PAPER/multiALL-*.txt $strg/00-FIGURES-PAPER/old_multiALL" );

##############################################

$TMP = "tmp";
system( "rm -r $TMP/*" );
system( "ls -1 $strg/00-FIGURES-PAPER/old_multiALL > $TMP/tmp-files.$$" );

############################################
## Find Numbers of curves for each Variant 

open (ALL_VARIANT, "< $TMP/tmp-files.$$");
while ($_ = <ALL_VARIANT>) {
	chop($_);

	if($_ =~ /^multiALL-/ && $_ =~ /.txt$/) {

		$kkpp = 1;
		$kount = 0;

		open(FILE_PLOT, "< $strg/00-FIGURES-PAPER/old_multiALL/$_");
		while ($multi_plot = <FILE_PLOT>) {
		##print "$multi_plot"; 
##----
		$key0 = " sample in ";
		if($multi_plot =~ /$key0/) { $kount++; $kkpp = 1; }
		if($multi_plot =~ /t \"\",/) { $kkpp++; }
##----

if($kount > 0 && $multi_plot !~/^\\$/) {
$kp[$kount] = $kkpp;
##print "$kkpp :: $kount :: $kp[$kount] <<<<<< $multi_plot :::: $_\n"; 
}
##print "$kount :::: $kp[$kount] :::: $_\n"; 

		}
		close(FILE_PLOT);

##------------
	for($k = 1; $k <= $#kp; $k++) { 
		##print "$k\t$kp[$k] <<<<<< $_\n"; 
	}
##------------
## Modify xxx by Numbers in mutiFiles...

                $k = 0;

		open(FILE_PT, "> $strg/00-FIGURES-PAPER/$_");
                open(FILE_PLOT, "< $strg/00-FIGURES-PAPER/old_multiALL/$_");
                while ($multi_plot = <FILE_PLOT>) {
                ##print "$multi_plot";

                $key0 = " sample in ";
                if($multi_plot =~ /$key0/) {
                	$k++;
                        ##print "$k :::: $kp[$k]";

                        $multi_plot =~ s/xxx/$kp[$k]/;
                        ##print "$k :::: $kp[$k] :::: $multi_plot";
                }


		#### File to Plot
		print FILE_PT "$multi_plot"; 


                }
                close(FILE_PLOT);
                close(FILE_PT);

##------------

	}


}
close(FILE_VARIANT);

##############################################################################	
exit;
##############################################################################	

