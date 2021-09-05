#!/usr/bin/perl
###############################################################
##  GENOMEBITS - Scripts based on the paper:
## Canessa E. "Uncovering Signals from the Coronavirus Genome"
## Genes 2021; 12(7):973. https://doi.org/10.3390/genes12070973
###############################################################

use List::Util qw(min max);

############################################

	$dir = "tmp-sums";

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

		#### print "Lenght complete genome file: $genome_file --> \t$gen_width_full[$kline_full - 1]\n";


############################################


open (FILE_TMP1, "< $TMP/tmp-$dir.$$");
while ($genome_file = <FILE_TMP1>) {
	chop($genome_file);
	if($genome_file =~ /.fasta$/) {

		print "Lenght complete genome file: $genome_file --> \t$gen_width_full[$kline_full - 1]\n";
		##print "$genome_file\n";
		system ( "wc -w < $TMP/$genome_file-char >> $TMP/character.txt" );
	}
}
close(FILE_TMP1);


############################################


open (FILE_TMP2, "< $TMP/character.txt");
while (@val = <FILE_TMP2>) {
	$min = min(@val);
	$max = max(@val);
	chop($min);
	chop($max);

	##print "MIN: $min   ::   Max: $max\n";
}
close(FILE_TMP2);


############################################
	
	$kfile = 0;

open (FILE_TMP, "< $TMP/tmp-$dir.$$");
while ($genome_file = <FILE_TMP>) {
	chop($genome_file);

if($genome_file =~ /.fasta$/) {

	##print "\t\t($kfile) -->\t\t$genome_file\n";

##====================================================== 

	#### open (FILE02, "> $dir/0-1-complete-$genome_file");
	open (pass, "< $dir/$genome_file");

	open (FILE_AA, "> $dir/A-01-complete.dat");
	open (FILE_CC, "> $dir/C-01-complete.dat");
	open (FILE_GG, "> $dir/G-01-complete.dat");
	open (FILE_TT, "> $dir/T-01-complete.dat");

	open (FILE_A, "> $dir/A-sum01-complete.dat");
	open (FILE_C, "> $dir/C-sum01-complete.dat");
	open (FILE_G, "> $dir/G-sum01-complete.dat");
	open (FILE_T, "> $dir/T-sum01-complete.dat");
	
	open (FILE_ACGT, "> $dir/ACGT-sum01-complete.dat");
##======================================================  

	$kline = 1;

while ($_=<pass>) {

	#### if ($_ =~ /^\>/) { 
		####print FILE02 "$_"; 
	#### }

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

##################################################################################################
#### Read Fasta Files ####
       
       for ($k = 1; $k <= $#input; $k++) {

                $value[$kline] = $input[$k];
                $kline++;
                
        }    
   
##################################################################################################     
        
    	}

}	
	
close(pass);

##################################################################################################
#### Prepare Fasta Files ####


	$kkline[$kfile] = $kline - 1;

	print "\t($kfile) --> Width: \t$gen_width[$kfile]\t Total Nr Base Pair: $kkline[$kfile]\n";


	##################################
	## (original fasta file)
	$kini = 1;
	$kfin = $kkline[$kfile];

             	#### $kmixx = 0;
       
       #### for ($k = $kini; $k <= $kfin; $k++) {
               #### print FILE02 "$value[$k]";			#### OK
		#### $kmixx++;
      		#### if($kmixx == $gen_width[$kfile]) { print FILE02 "\n"; $kmixx = 0; }
		####if($kmixx < $gen_width[$kfile] && $k == $kfin) { print FILE02 "\n"; } 
	#### }
	#### close(FILE02);	



	###########################################
	## (convert Genoma into 0 and 1 and sum up)

		$sumA[$kini-1] = 0;
		$sumC[$kini-1] = 0;
		$sumG[$kini-1] = 0;
		$sumT[$kini-1] = 0;
		
		$kk = 0;

		$kn = 0;

       for ($k = $kini; $k <= $kfin; $k++) {
               if($value[$k] =~ /A/) { $valueA[$k] = 1; } else { $valueA[$k] = 0; }
               if($value[$k] =~ /C/) { $valueC[$k] = 1; } else { $valueC[$k] = 0; }
               if($value[$k] =~ /G/) { $valueG[$k] = 1; } else { $valueG[$k] = 0; }
               if($value[$k] =~ /T/) { $valueT[$k] = 1; } else { $valueT[$k] = 0; }


		$valAA = $valueA[$k];
		$valCC = $valueC[$k];
		$valGG = $valueG[$k];
		$valTT = $valueT[$k];

               print FILE_AA "$k\t$valAA\n";                      
               print FILE_CC "$k\t$valCC\n";                      
               print FILE_GG "$k\t$valGG\n";                      
               print FILE_TT "$k\t$valTT\n";                      


                ##$kk++;
                $kk = $k;

		
                $valueAA = $valueA[$k]*(-1)**$kn;
                $valueCC = $valueC[$k]*(-1)**$kn;
                $valueGG = $valueG[$k]*(-1)**$kn;
                $valueTT = $valueT[$k]*(-1)**$kn;
		$kn++;
		if($kn > 1) { $kn = 0; }


                $sumA[$k] = $valueAA;
                $sumA[$k] = $sumA[$k] + $sumA[$k-1];

                $sumC[$k] = $valueCC;
                $sumC[$k] = $sumC[$k] + $sumC[$k-1];

                $sumG[$k] = $valueGG;
                $sumG[$k] = $sumG[$k] + $sumG[$k-1];

                $sumT[$k] = $valueTT;
                $sumT[$k] = $sumT[$k] + $sumT[$k-1];


               print FILE_A "$kk\t$sumA[$k]\n";
               print FILE_C "$kk\t$sumC[$k]\n";
               print FILE_G "$kk\t$sumG[$k]\n";
               print FILE_T "$kk\t$sumT[$k]\n";


		$sumACGT[$k] = $sumA[$k] + $sumC[$k] + $sumG[$k] + $sumT[$k];
		print FILE_ACGT "$kk\t$sumACGT[$k]\n";

        }
        close(FILE_AA);
        close(FILE_CC);
        close(FILE_GG);
        close(FILE_TT);

        close(FILE_A);
        close(FILE_C);
        close(FILE_G);
        close(FILE_T);

        close(FILE_ACGT);

##################################################################################################
	
}

	$kfile++;
}
close(FILE_TMP);



############################
## Get intersection point between A-genoma and T-spyke

##	system( "./zz0TA-intersection_ok.py > $dir/T-A-sum01-intersection.dat" ); 
##	system( "./zz0GC-intersection_ok.py > $dir/G-C-sum01-intersection.dat" ); 


##################################################################################################
exit;
##################################################################################################

