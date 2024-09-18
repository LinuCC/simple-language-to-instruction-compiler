ostfalia-sud-latex-thesis
============================
Eine kleine Anregung für eine Bachelorthesis/Projektarbeit nach Richtlinien der Ostfalia.

 **Aktuelle Beispiel-PDF herunterladen:** [![Foo](https://img.shields.io/badge/Download-PDF-green)](https://git-fkb.ostfalia.de/jkleimann_admin/Ostfalia-Latex-Vorlage/-/jobs/artifacts/master/raw/Hauptdokument.pdf?job=build)
 

## Fakultät
Das Deckblatt kann sowohl für die Angewandte Informatik in Suderburg als auch für die Informatik in Wolfenbüttel verwendet werden.
Zwischen den verschiedenen Deckblättern kann mit einer Variable in der ```commands.tex``` gewechselt werden:
```
\setcounter{documentfakultaet}{0} % 0 = Bau Wasser Boden, 1 = Informatik
```

## Hinweis
Diese Vorlage ist abhängig von spezifischen LaTeX Schriftarten die nicht immer bei jedem LaTeX Editor automatisch dabei sind.
Darum sind nachfolgend einige getestete Empfehlungen für die jeweiligen Betriebssysteme die gut mit dieser Vorlage funktionieren:

*Linux:*\
Editor:\
[Texmaker](https://www.xm1math.net/texmaker/index.html)
\
Erweiterungen:\
[Miktex](https://miktex.org/download)
```
texlive-base
texlive-fonts-recommended
```

*Mac:*\
Editor:\
[Texmaker](https://www.xm1math.net/texmaker/index.html)
\
Erweiterungen:
\
[Miktex](https://miktex.org/download)

*Windows:*\
Editor:\
[TeXstudio](https://www.texstudio.org/)
\
[Texmaker](https://www.xm1math.net/texmaker/index.html)
\
Erweiterungen:
\
[Miktex](https://miktex.org/download)

### Rechtschreibüberprüfung
Die Rechtschreib- und Grammatiküberprüfung von den meisten Tex-Editoren kann nicht mit Word mithalten.
Es gibt ein Tool namens [TeXtidote](https://github.com/sylvainhalle/textidote), welches beides anlysieren kann und aus den Anmerkungen ein HTML Report generiert. Schaut es auch gerne mal an.

## Disclamer
Alle enthaltenen Schriftarten stammen von CTAN Comprehensive TeX Archive Network [www.ctan.org](https://www.ctan.org)
und sind nach [LaTeX Project Public License (LPPL)](https://www.ctan.org/license/lppl1.3c) Lizensiert.
Die Rechte verbleiben bei den jeweiligen Autoren.

## Fehler / Änderungen
Falls euch Fehler aufallen oder Ihr Änderungswünsche habt, einfach ein Issue erstellen.
