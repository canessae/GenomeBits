#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

	$dir = "x-inputs";

$TMP = "tmp";
system( "rm -r $TMP/*" );
system( "ls -1 $dir/ > $TMP/tmp-input-files.$$" );

##############################################################################	

open (FILE_INPUT, "< $TMP/tmp-input-files.$$");
while ($input_file = <FILE_INPUT>) {
	chop($input_file);

	if($input_file =~ /.txt$/) {
		##print ">>>>>>> $input_file\n";

		open (COUNTRY_IN, "< $dir/$input_file");
		while ($country = <COUNTRY_IN>) {
			chop($country);
			##print "$input_file -> $country\n";

		## Identify .fasta files 
	        	@file_fas = split(/\.txt/g, $input_file);
			##print "$file_fas[0] :: $file_fas[1]\n";

			system( "ls -1 $dir/$file_fas[0]*.fasta > $TMP/tmp-fasta-files.$$" );

			open (FILE_FASTA, "< $TMP/tmp-fasta-files.$$");
			while ($input_fasta = <FILE_FASTA>) {
				chop($input_fasta);
				##print "$input_fasta\n";

			## Fullfill X-INPUT Directories 
	       		@file_x = split(/\-/g, $input_file);
				print "$file_x[0] :: $country :: $input_fasta\n";

				$dir_input = $file_x[0] . "-input"; 
				system("mkdir -p $dir_input/$country");
				system("cp -r x-input-scripts/* $dir_input/$country");
				system("cp -f $input_fasta $dir_input/$country");
				system("cp -f $input_fasta $dir_input/$country/A-FASTA-GISAID");

			## Run Scripts to prepare data 
			system("cd $dir_input/$country; ./run1-separate-clean-gisaid-fasta-files.pl");
			system("cd $dir_input/$country; ./run2-run-canessa-all.pl");
			system("cd $dir_input/$country; ./run3-get-identifier-FastaFiles.pl");

			}
			close(FILE_FASTA);


		}
		close(COUNTRY_IN);

	}

}
close(FILE_INPUT);

##############################################################################	
exit;
##############################################################################	

