bldcmd=R CMD Sweave

default:
	make makesweavevignette.pdf
	make clean

enhanced:
	make draft bldcmd=makesweave

draft:
	make makesweavevignette.pdf

makesweavevignette.pdf: makesweavevignette.tex trivial1.tex trivial2.tex
	pdflatex makesweavevignette.tex

makesweavevignette.tex: makesweavevignette.rnw
	$(bldcmd) makesweavevignette.rnw

trivial1.tex: ext/trivial1.rnw
	$(bldcmd) ext/trivial1.rnw

trivial2.tex: ext/trivial2.rnw
	$(bldcmd) ext/trivial2.rnw

init:
	rm -f /tmp/makesweavepipe
	mkfifo /tmp/makesweavepipe
	makesweave -i &

clean:
	rm *.tex
	rm *.aux
	rm *.log


