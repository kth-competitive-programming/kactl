# Makefile for building KACTL (KTH ACM Contest Template Library)
# Written by Håkan Terelius, 2008-11-24

LATEXCMD = pdflatex
LATEXFLAGS = -shell-escape

.PHONY: help
help:
	@echo "This makefile builds KACTL (KTH ACM Contest Template Library)"
	@echo "Type"
	@echo "	$ make kactl"
	@echo "to build the KACTL or"
	@echo "	$ make clean"
	@echo "to clean up the build process."

.PHONY: kactl
kactl:
	cd build && $(LATEXCMD) kactl.tex $(LATEXFLAGS) && $(LATEXCMD) kactl.tex $(LATEXFLAGS)
	cp build/kactl.pdf kactl.pdf


.PHONY: clean
clean: 
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.maf kactl.ptc
	cd build && rm -f kactlpkg.log
	cd build && rm -f *.mtc*
	cd build && rm -f kactl.pdf

.PHONY: veryclean
veryclean: clean
	rm -f kactl.pdf