#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

	
# (1) quit unless we have the correct number of command-line args
$num_args = $#ARGV + 1;
if ($num_args != 2) {
    print "\nUsage:  run2-load-X-sum01.pl  variant_name   what_to_plot\n";
    print "\t(Example:  run2-load-X-sum01.pl  0-UK-Variant  A-sum01-complete)\n";
    exit;
}

# (2) got two command line args such as:
        $strg = $ARGV[0];
$genome_sum01 = $ARGV[1];
	

############################################

$TMP = "tmp";
system( "rm -r $TMP/*" );
system( "ls -1 ./ > $TMP/tmp-files.$$" );

############################################

open (FILE_STRG, "> $TMP/tmp-$strg.$$");

open (FILE_VARIANT, "< $TMP/tmp-files.$$");
while ($variant_file = <FILE_VARIANT>) {
	chop($variant_file);

	if($variant_file =~ /$strg/ && $variant_file !~ /.pl$/ && $variant_file !~ /-PLOTS$/) {
		print ">>>>>>> \t$variant_file\n";

		##############################################
		system( "ls -1 $variant_file/ > $TMP/tmp-$strg.$$" );
		##############################################
	}

}
close(FILE_VARIANT);
close(FILE_STRG);

##############################################################################	

	$kfile = 0;
open (FILE_STRG, "< $TMP/tmp-$strg.$$");
while ($file = <FILE_STRG>) {
	chop($file);

	if($file !~ /.txt$/ && $file !~ /.png$/) {

	$kfile ++;
	##############################################
	##print "\t\t\t ...$file\n";
	$ff[$kfile] = $file;
	system( "cd $strg/$ff[$kfile] && ls -1 A-FASTA-GISAID-GenomeBits > ../../$TMP/$ff[$kfile]-GenomeBits.$$" );
	##############################################

	}

}
close(FILE_STRG);

##############################################################################
### 0-UK-Variant-Brazil/A-FASTA-GISAID-GenomeBits/11-gisaid_hcov-19_2021_03_04_20
## A-sum01-complete.dat
##############################################################################

	open (LOAD_1, "> $strg-PLOTS/ALL-$genome_sum01.txt");
	print LOAD_1 "set terminal pngcairo size 1600,600 font \',18\' enhanced\n";
	print LOAD_1 "set output \"$strg-PLOTS/ALL-$genome_sum01.png\"\n";  
	print LOAD_1 "set title \"$strg :: $genome_sum01 :: ALL\" font \"Times-Roman,18\" offset 0.5, 0\n";
	
require "./lines-stykes-LOAD.conf"; 

##############################################################################	
#### Increasing order   
for($k = 1; $k <= $kfile; $k++) {


	if($k <= 2) {
			print " ...$ff[$k]\n"; 
		} else {
			print " ...$ff[$k] (not considered) <-- WARNING: Up to 2 Countries\!\n"; 
	}

	##open (LOAD_0, "> $strg-PLOTS/$genome_sum01-$k-$ff[$k].txt");
	open (LOAD_0, "> $strg-PLOTS/$genome_sum01-$ff[$k].txt");

	print LOAD_0 "set terminal pngcairo size 1600,600 font \',18\' enhanced\n";

	##print LOAD_0 "set output \"$strg-PLOTS/$genome_sum01-$k-$ff[$k].png\"\n";
	print LOAD_0 "set output \"$strg-PLOTS/$genome_sum01-$ff[$k].png\"\n";
	  
	print LOAD_0 "set title \"$ff[$k] :: $genome_sum01\" font \"Times-Roman,18\" offset 0.5, 0\n";

	if($genome_sum01 =~ /^ACGT-sum01-complete/) {
		print LOAD_0 "set yrange[-5:320.0]\n";
		if($k == 1) { print LOAD_1 "set yrange[-5:320.0]\n"; }
	} else {
		print LOAD_0 "set yrange[-150.0:150.0]\n";
		if($k == 1) { print LOAD_1 "set yrange[-150.0:150.0]\n"; }
	}

	

## WARNING      ### ACCEPT up to 4 Fasta inputs for up to 2 Countries!!!!!!
	if($k <= 2) { print LOAD_0 "\tset label \'$strg\' at 4000, 120 font \',18\'\n"; }
	if($k == 1) { print LOAD_1 "\tset label \'$strg\' at 4000, 120 font \',18\'\n"; }


require "./lines-stykes-LOAD.conf";


## WARNING      ### ACCEPT up to 4 Fasta inputs for up to 2 Countries!!!!!!
        if($k <= 2) { print LOAD_0 "plot \\\n"; }
        if($k == 1) { print LOAD_1 "plot \\\n"; }


	$kk = 0;
	$kfasta = 0;
open (FILE_STRG, "< $TMP/$ff[$k]-GenomeBits.$$");
while ($file = <FILE_STRG>) {
	chop($file);
	$kk++;

if($kk > 4) { 
	$kfasta++; 
	if($kfasta == 1 && $k <= 2) { print "\tMore than 4 Fasta inputs found\! -plotted only 4 files\n"; }
}

	##if($kk == 1) { $title = $ff[$k]; } else { $title = ""; }
	$file_gisaid_0 = $file;
	##$file_gisaid_0 =~ s/\_/-/g; 
	@file_gisaid_1 = split(/\_/g, $file_gisaid_0);
	$file_gisaid = $file_gisaid_1[0];
	
	##$title = "$file_gisaid"; 
	$title = "$ff[$k]: $file_gisaid"; 
	##############################################
	#### Create Gnuplot Load files

## WARNING      ### ACCEPT up to 4 Fasta inputs for up to 2 Countries!!!!!!
		##print "-- $kk\n";
		if($kk <= 4 && $k <=2) { 


	  if($k == 1) { $kk2 = $kk; $wlp = "w l" } else { $kk2 = $kk + 4; $wlp = "every 200 w p"}

	  print LOAD_0 "\t\"$strg/$ff[$k]/A-FASTA-GISAID-GenomeBits/$file/$genome_sum01.dat\" $wlp ls $kk2 t \"$title\", \\\n";
	  print LOAD_1 "\t\"$strg/$ff[$k]/A-FASTA-GISAID-GenomeBits/$file/$genome_sum01.dat\" $wlp ls $kk2 t \"$title\", \\\n";

		}

	##print "$file\n";
	##############################################

}
close(FILE_STRG);

	print LOAD_1 "\\\n";

	##system( "gnuplot -p $strg-PLOTS/$genome_sum01-$k-$ff[$k].txt" );
	system( "gnuplot -p $strg-PLOTS/$genome_sum01-$ff[$k].txt" );

	##print "\n";
	close(LOAD_0);

}

	system( "gnuplot -p $strg-PLOTS/ALL-$genome_sum01.txt" );
	close(LOAD_1);

##############################################################################	
exit;
##############################################################################	

