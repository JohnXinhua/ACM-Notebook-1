notebook.html: notebook.txt
	pandoc -s -S -N --toc -B header.html --highlight-style pygments notebook.txt -o notebook.html

notebook.pdf: notebook.txt
	pandoc -s -S -N --template=template.tex --variable fontsize=10pt --highlight-style pygments notebook.txt --latex-engine=xelatex -o notebook.pdf

notebook.tex: notebook.txt
	pandoc -s -S -N --template=template.tex --variable fontsize=10pt --highlight-style pygments notebook.txt --latex-engine=xelatex -o notebook.tex

clean:
	rm notebook.tex notebook.pdf notebook.html
