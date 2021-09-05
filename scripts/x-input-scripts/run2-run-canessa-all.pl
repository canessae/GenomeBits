#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################


	$dir = "tmp-sums";
	$dir2 = "A-FASTA-GISAID";
	$dir3 = "A-FASTA-GISAID-GenomeBits";

############################################

$TMP = "tmp";
system( "ls -1 $dir2/ > $TMP/tmp-$dir2.$$" );

system( "mkdir -p $dir3" );


	$kfasta = 0;
open (FILE_FASTA, "< $TMP/tmp-$dir2.$$");
while ($fasta_file = <FILE_FASTA>) {
	chop($fasta_file);

	$kfasta++;
	system( "cp $dir2/$fasta_file  $dir/$fasta_file" );

	$fasta_file2 = $fasta_file;
	$fasta_file2  =~ s/.fasta//; 

	system( "mkdir -p $dir3/$fasta_file2" );
	system( "mkdir -p $dir3/$fasta_file2/$TMP" );

	print "\t...($kfasta) Analysis FASTA file: $fasta_file\n"; 


##################################################################################################
## Canessa's SUM for Complete Genoma

	system( "./zz0-4pairs-run2-0-1.pl" );
	system( "./zz0ACGT-plot.py" );
	system( "./zz0AT-plot.py" );
	system( "./zz0CG-plot.py" );

##################################################################################################

        system( "mv $dir/* $dir3/$fasta_file2/" );
        system( "mv $TMP/* $dir3/$fasta_file2/$TMP" );

##################################################################################################

	print "\n######################################################\n";


}
close(FILE_FASTA);

##################################################################################################
exit;
##################################################################################################

