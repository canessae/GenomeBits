all: index.html manual.qch genomebits.qhc genomebits_manual.pdf 

index.html:
	texi2html -menu -split chapter -subdir . -toc_file index.html genomebits_manual.texi

manual.qch:
	qhelpgenerator manual.qhp -o manual.qch	

genomebits.qhc:
	qhelpgenerator genomebits.qhcp -o genomebits.qhc

genomebits_manual.pdf:
	tex genomebits_manual.texi
	tex genomebits_manual.texi
	dvipdf genomebits_manual
