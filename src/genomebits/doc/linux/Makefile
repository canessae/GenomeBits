all: linux

linux: 
	cp -r texi tmp
	cp manual.qhp genomebits.qhcp tmp
	make -C tmp
	cd ..

clean:
	\rm -rf html openEyA_manual.pdf
	\rm -rf manual.qch genomebits.qhc
	\rm -rf tmp

install:
	cp -v tmp/manual.qch .
	cp -v tmp/genomebits.qhc . 
	cp -v tmp/genomebits_manual.pdf . 
	\rm -rf html
	mkdir html
	cp -v tmp/*.html html
	cp -v tmp/*.jpg html
	cp -v tmp/*.png html
