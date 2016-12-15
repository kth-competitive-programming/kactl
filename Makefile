LATEXCMD = pdflatex -shell-escape
export max_print_line = 1048576

.PHONY: help
help:
	@echo "This makefile builds KACTL (KTH ACM Contest Template Library)"
	@echo ""
	@echo "Available commands are:"
	@echo "	make fast	- to build the KACTL, quickly (only runs LaTeX once)"
	@echo "	make kactl	- to build the KACTL"
	@echo "	make clean	- to clean up the build process"
	@echo "	make veryclean	- to clean up and remove kactl.pdf"
	@echo "	make help	- to show this information"
	@echo ""
	@echo "For more information see the file 'doc/README'"

.PHONY: fast
fast:
	cd build && $(LATEXCMD) kactl.tex </dev/null
	cp build/kactl.pdf kactl.pdf

.PHONY: kactl
kactl: test-session.pdf
	cd build && $(LATEXCMD) kactl.tex && $(LATEXCMD) kactl.tex
	cp build/kactl.pdf kactl.pdf

.PHONY: clean
clean: 
	cd build && rm -f kactl.aux kactl.log kactl.tmp kactl.toc kactl.pdf kactl.ptc

.PHONY: veryclean
veryclean: clean
	rm -f kactl.pdf test-session.pdf

test-session.pdf: content/test-session/chapter.tex
	cd build && $(LATEXCMD) test-session.tex
	cp build/test-session.pdf test-session.pdf
