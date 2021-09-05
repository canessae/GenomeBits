#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

	$dir = "A-FASTA-GISAID";

############################################

$TMP = "tmp";
##system( "rm -r $TMP/*" );
system( "ls -1 $dir/ > $TMP/tmp-$dir.$$" );

############################################

	$kount = 0;
	$gen_width_full[0] = 0;

open (FILE_TMP0, "< $TMP/tmp-$dir.$$");
while ($genome_file = <FILE_TMP0>) {
	chop($genome_file);
	if($genome_file =~ /.fasta$/) {

	$kount++;
	if($kount >= 2) { print "\n* * * Error: use only one FASTA file in $dir * * *\n\n"; exit; }

	$kline_full = 1;

open (FILE_CHAR, ">> $TMP/$genome_file-char");
open (pass, "< $dir/$genome_file");
while ($_=<pass>) {
	if ($_ !~ /^\>/) {
                $_ =~ s/A/ A /g;
                $_ =~ s/T/ T /g;
                $_ =~ s/C/ C /g;
                $_ =~ s/G/ G /g;

		print FILE_CHAR "$_"; 

                @input_full = split(/\s+/g, $_);
                $gen_width_full[$kline_full] = $#input_full;
                $gen_width_full[$kline_full] = $gen_width_full[$kline_full] + $gen_width_full[$kline_full - 1];
		$kline_full++;
	} 
}
close(pass);
close(FILE_CHAR);

}
}
close(FILE_TMP0);


	open (FILE_CHAR2, "> $TMP/0-Delete-NNNNN-YYYYY-etc-base_pairs.txt");
	print "\n\nLenght complete GISAID genome file: $genome_file --> \t$gen_width_full[$kline_full - 1]\n";


############################################
############################################
	
	$kfile = 0;

open (FILE_TMP, "< $TMP/tmp-$dir.$$");
while ($genome_file = <FILE_TMP>) {
	chop($genome_file);

if($genome_file =~ /.fasta$/) {


	$kline = 1;
	$kfasta = 0;

open (pass, "< $dir/$genome_file");
while ($_=<pass>) {

##################################################################################################

	if ($_ =~ /^\>/) { 
		$kfasta++;
		open (FILE02, "> $dir/$kfasta-$genome_file");
		print FILE02 "$_"; 
	}


        if ($_ !~ /^\>/) {

                $_ =~ s/A/ A /g;	
                $_ =~ s/T/ T /g;
                $_ =~ s/C/ C /g;
                $_ =~ s/G/ G /g;

                @input = split(/\s+/g, $_);

		if($kline == 1) {
			$gen_width[$kfile] = $#input;
			$gen_file[$kfile] = $genome_file;
			
			##print "$kfile --> \t$gen_width[$kfile]\n";
		}


#### Read Fasta Files ####

             	$kmixx = 0;
       
           for ($k = 1; $k <= $#input; $k++) {

                $value[$k] = $input[$k];

		############## Delete NNNNN, YYYYY, etc base pairs
		if($value[$k] !~ /A/ && $value[$k] !~ /C/ && $value[$k] !~ /G/ && $value[$k] !~ /T/) { 
			print " --> NOTE: $value[$k] !!!!\n";
			$value_delete = $value[$k];

			print "\t...Found (at line $k) $value_delete:\tMoved $kfasta-$genome_file to $TMP\n"; 
			print FILE_CHAR2 " Found (at line $k) $value_delete:\tMoved $kfasta-$genome_file to $TMP\n"; 
			close(FILE02);	
			system( "mv $dir/$kfasta-$genome_file $TMP/z-$value_delete-$kfasta-$genome_file" );
		} 
		###############

               print FILE02 "$value[$k]";			#### OK
		$kmixx++;
      		if($kmixx == $gen_width[$kfile]) { print FILE02 "\n"; $kmixx = 0; }
		if($kmixx < $gen_width[$kfile] && $k == $kfin) { print FILE02 "\n"; } 
                
           }    

    	}

##################################################################################################     


}	
	
close(pass);

		close(FILE02);	

##################################################################################################
	
}

		print "Separated complete GISAID ($genome_file) in --> \t$kfasta parts\n";
		system( "mv $dir/$genome_file $TMP/ORG-GISAID-$genome_file" );

}

close(FILE_TMP);
close(FILE_CHAR2);


##################################################################################################
exit;
##################################################################################################

