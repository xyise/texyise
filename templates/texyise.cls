\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{texyise}[2013/01/01 v1.0 TeXyise class]

\LoadClass[]{article}

\usepackage{geometry}

\geometry{
    a4paper,
    textwidth=160mm,
    textheight=240mm,
    left=25mm,
    right=25mm,
    top=30mm,
    bottom=30mm
}

\usepackage{etoolbox}
\usepackage{fancyhdr}
\usepackage{xcolor}
\usepackage{parskip}
\usepackage{graphicx}

\RequirePackage{fancyhdr}

% basic formatting
\setlength\parindent{0pt}

%%%%%%%%%%%%%%%%%%%%%%%
%% Front-page items
%%%%%%%%%%%%%%%%%%%%%%%

\newcommand{\@documentTitle}{\colorbox{red!30}{Set document title by specifying \texttt{\textbackslash documentTitle}}}
\newcommand{\documentTitle}[1]{\edef\@documentTitle{#1}}

\newcommand{\@documentClassification}{\colorbox{red!30}{Set document classification by specifying \texttt{\textbackslash documentClassification}}}
\newcommand{\documentClassification}[1]{\edef\@documentClassification{#1}}

\newcommand{\@documentAuthor}{\colorbox{red!30}{Set document author by specifying \texttt{\textbackslash documentAuthor}}}
\newcommand{\documentAuthor}[1]{\edef\@documentAuthor{#1}}

\newcommand{\@documentDate}{\colorbox{red!30}{Set document date by specifying \texttt{\textbackslash documentDate}}}
\newcommand{\documentDate}[1]{\edef\@documentDate{#1}}

\newcommand{\@documentVersion}{\colorbox{red!30}{Set document version by specifying \texttt{\textbackslash documentVersion}}}
\newcommand{\documentVersion}[1]{\edef\@documentVersion{#1}}

\newcommand{\@documentStatus}{\colorbox{red!30}{Set document status by specifying \texttt{\textbackslash documentStatus}}}
\newcommand{\documentStatus}[1]{\edef\@documentStatus{#1}}

\fancypagestyle{coverpagestyle}
{
    \fancyhf{}
    \fancyhead[L]{LOGO}%\includegraphics[width=0.2\textwidth]{logo}}
    \fancyhead[R]{My Company}
    \fancyfoot[L]{\@documentClassification}
    \fancyfoot[R]{Page \thepage}
    \renewcommand{\headrulewidth}{4pt}
    \renewcommand{\footrulewidth}{4pt}
}

\fancypagestyle{mainpagestyle}
{
    \fancyhf{}
    \fancyhead[L]{LOGO}
    \fancyhead[R]{Section \thesection}
    \fancyfoot[L]{\@documentClassification}
    \fancyfoot[R]{Page \thepage}
    \renewcommand{\headrulewidth}{4pt}
    \renewcommand{\footrulewidth}{4pt}
}

\AtBeginDocument{

% START: Cover page
\thispagestyle{coverpagestyle}

\begin{center}
    {\large \@documentTitle}
    \vspace{0.5cm}

    \@documentAuthor, \@documentDate

\end{center}

% END Cover page

% START: Main page

\pagestyle{mainpagestyle}

}