# Խառը գրառումներ Plain TeX-ի մասին

Հայերեն տեքստեր պատրաստելու համար հիմնականում օգտագործում եմ
XeTeX-ը։ Դրան հասանելի են համակարգում տեղադրված տպատառերը
(font), ինչպես նաև հնարավորություն է տալիս տպատառերը բեռնել
որպես ֆայլ։ Աշխատում է UTF-8 կոդավորմամբ տեքստերի հետ։


## Լուսանցքում բացատրություններ գրելու համար

```tex
\hsize=0.70\hsize     % 75% of original width for main text
\newdimen\mainwidth   \mainwidth=\hsize
\newdimen\footwidth   \footwidth=0.28\hsize
%\advance\hsize by \footwidth % restore total line width for box building

\newbox\mainbox
\newbox\footbox

% Initialize footnote storage
\def\clearfootnotes{\global\setbox\footbox=\vbox{}}
\clearfootnotes

% Simple font setup for footnotes
\font\sevenrm=cmr7

% Vertical footnote macro
\newcount\footnum \footnum=0
\def\vfootnote#1{%
  \global\advance\footnum by1
  \setbox0=\vbox{\hsize=\footwidth \noindent{\sevenrm\the\footnum. }%
        {\tolerance=8000\baselineskip=9pt\sevenrm #1\par}\medskip}%
  \global\setbox\footbox=\vbox{\unvbox\footbox \box0}%
  \hbox{\raise.5ex\hbox{\sevenrm\the\footnum}}%
}

% Page output routine
\output={%
  \global\setbox\mainbox=\vbox{\makeheadline\pagebody\makefootline}%
  \shipout\vbox{%
    \hbox{%
      \vbox to\vsize{\box\mainbox\vfill}%
      \vrule width 8pt height 0pt depth 0pt%
      \vbox to\vsize{\hsize=\footwidth \unvbox\footbox \vfill}%
    }%
  }%
  \advancepageno
  \clearfootnotes
}
```


## Երկար վերնագիր

```tex
\font\titlefont="GHEAGrapalat/B" at 12pt

\def\chapter#1{
	\let\\=\cr
	\halign{\hbox to\hsize{\hss\titlefont##\hss}\cr#1\cr}}
```


## Մաթեմատիկայի վանդակներ

```tex
\newdimen\onerow \onerow5mm
\newdimen\freespace
\newbox\mathcell
\setbox\mathcell=\hbox{\vbox{\hrule width \onerow height 0pt}}
\def\cell{\vrule\copy\mathcell}
\def\mathgrid{%
  \freespace\vsize
  \advance\freespace by -\pagetotal
  \advance\freespace by -4\onerow
  \def\rows{\noalign{\hrule}}
  \loop
    \edef\rows{\rows &&&&&&&&&&&&&&&\cr\noalign{\hrule}}
    \advance\freespace by -\onerow
    \ifnum\freespace>0\repeat
  \bigskip\special{color push rgb 0.5 0.5 0.5}
  \centerline{\vbox{\halign{
    \cell##&\cell##&\cell##&\cell##&%
    \cell##&\cell##&\cell##&\cell##&%
    \cell##&\cell##&\cell##&\cell##&%
    \cell##&\cell##&\cell##&\cell##\vrule height\onerow\cr
    \rows}}}\medskip\special{color pop}}
```


## Փորձ ֆայլերի հետ

```tex
\def\insertqr#1{%
  \immediate\write18{python createqr.py #1}
  myau
}

\def\chess#1{%
\immediate\openout5="a.txt"
\immediate\write5{#1}
\immediate\closeout5
\input a.txt
}

% - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Here is:

\insertqr{ok bad}

End.

\chess{
etude one
  a 1 white pown
}

\bye
```


## Տողադարձի փորձարկում, LaTeX

```tex
\documentclass{report}

\usepackage{fontspec}
%\setmainfont[Ligatures=TeX,HyphenChar="058A]{GHEA Mariam}
%\setsansfont[Ligatures=TeX,HyphenChar="058A]{GHEA Grapalat}

\newfontfamily\armenianfont[Ligatures=TeX,HyphenChar="058A]{GHEA Mariam}
\newfontfamily\armenianfontsf[Ligatures=TeX,HyphenChar="058A]{GHEA Grapalat}
\newfontfamily\armenianfonttt{DejaVu Sans Mono}

\usepackage{polyglossia}
\setdefaultlanguage{english}
\setmainlanguage{armenian}

\begin{document}
\chapter{Երբեք խոսքի մի բռնվեք անծանոթ մարդկանց հետ}

Մի անգամ, գարնանը, անասելի շոգ մայրամուտին, Մոսկվայում, Պատրիարքական լճի մոտ երկու քաղաքացի հայտնվեցին։ Նրանցից առաջինը ամառային մոխրագույն զգեստով էր, կարճահասակ, գեր, ճաղատ, բարեձեւ շլյապան երկծալ բռնած ձեռքում, իսկ խնամքով սափրված դեմքի վրա անբնական չափերի, սեւ եղջյուրի շրջանակով ակնոց էր կրում։ Երկրորդը թիկնեղ, շեկ, գիսախռիվ, վանդականախշ կեպին ծոծրակին քաշած երիտասարդ էր՝ քառեկավոր վերնաշապիկով, ճմրթված սպիտակ շալվարով ու սեւ չստերով։
\end{document}
```


## LuaTeX-ում հայերեն տեքստ և տողադարձ

```tex
\input luaotfload.sty
\font\arm="GHEA Mariam:mode=node;script=latn;+liga;+kern" at 12pt
\arm
\baselineskip=16pt

%\hsize=12cm

\newlanguage\armenianlang
\language=\armenianlang

\input hyph-hy.tex


\lefthyphenmin=2
\righthyphenmin=2
\prehyphenchar="058A
\tolerance=2000

Բարեւ ա՜շխա՞րհ, վն, մն, եւ

\bye
```
