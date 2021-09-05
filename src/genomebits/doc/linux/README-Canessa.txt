
TEXI
====

cd texi

tex  genomebits_manual.texi
tex  genomebits_manual.texi

dvipdf genomebits_manual


HTML
====

texi2html -menu -split chapter -subdir . -toc_file index.html genomebits_manual.texi



