#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################


$TMP = "tmp";
##system( "rm -r $TMP/*" );
##system( "ls -1 A-FASTA-GISAID-GenomeBits/ > $TMP/tmp-files.$$" );
system( "ls -1v A-FASTA-GISAID-GenomeBits/ > $TMP/tmp-files.$$" );

############################################

open (FILE_OUT, "> ID-AllFastaFiles.txt");

open (FILE_VARIANT, "< $TMP/tmp-files.$$");
while ($variant_file = <FILE_VARIANT>) {
	chop($variant_file);
        ##print "$variant_file";


	open (FILE_VARIANT2, "< A-FASTA-GISAID-GenomeBits/$variant_file/$variant_file.fasta");
	while ($variant_file2 = <FILE_VARIANT2>) {
              	##print "$variant_file2";

	##if($variant_file2 =~ /$\>hCoV-19/ ) {	
	if($variant_file2 =~ /$\>/ ) {	

              	print "$variant_file2";
              	print FILE_OUT "$variant_file2";

		####@input = split(/\|/, $variant_file3);
		##print "$input[1], "; 
		####print "$input[1], \n"; 

	}

		##print "\n";

	}
	close(FILE_VARIANT2);

}
close(FILE_VARIANT);

close(FILE_OUT);

##############################################################################	
exit;
##############################################################################	
