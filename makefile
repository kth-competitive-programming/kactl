# Makefile for building KACTL (KTH ACM Contest Template Library)
# Written by Håkan Terelius, 2008-11-24

LATEXCMD = pdflatex
LATEXFLAGS = 

.PHONY: help
help:
	@echo "This makefile builds KACTL (KTH ACM Contest Template Library)"
	@echo "Type"
	@echo "	> make kactl"
	@echo "to build the KACTL or"
	@echo "	> make clean"
	@echo "to clean up the build process."

.PHONY: kactl
kactl:
	$(LATEXCMD) kactl.tex $(LATEXFLAGS)


.PHONY: clean
clean: 
	rm -f kactl.aux kactl.log kactl.tmp

.PHONY: veryclean
veryclean: clean
	rm -f kactl.pdf