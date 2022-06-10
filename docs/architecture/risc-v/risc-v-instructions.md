# Digrams of RISC-V Instructions


## 5 RV32FD

### Floating-Point Computation

$$
\underline{\textbf{f}} \texttt{loat}
\left\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{sub}} \texttt{tract} \\
 \underline{\textbf{mul}} \texttt{tiply} \\
 \underline{\textbf{div}} \texttt{ide} \\
 \underline{\textbf{sq}} \texttt{uare}  \underline{\textbf{r}} \texttt{oo} \underline{\textbf{t}} \\
 \underline{\textbf{min}} \texttt{imum} \\
 \underline{\textbf{max}} \texttt{imum} \\
\end{array} \right\}
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\}
\\
\underline{\textbf{f}} \texttt{loat}
\left\{ \begin{array}{l} \\
 \underline{} \\
 \underline{\textbf{n}} \texttt{egative} \\
\end{array} \right\}
\underline{\textbf{m}} \texttt{ultiply}
\left\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{sub}} \texttt{tract} \\
\end{array} \right\}
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{m}} \texttt{o} \underline{\textbf{v}} \texttt{e} \
\texttt{to} \
\underline{\textbf{.s}} \texttt{ingle} \
\texttt{from} \
\underline{\textbf{.x}} \ \texttt{register}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{m}} \texttt{o} \underline{\textbf{v}} \texttt{e} \
\texttt{to} \
\underline{\textbf{.x}} \ \texttt{register} \
\texttt{from} \
\underline{\textbf{.s}} \texttt{ingle}
$$

### Comparison

$$
\texttt{compare} \
\underline{\textbf{f}} \texttt{loat}
\left\{ \begin{array}{l}
 \underline{\textbf{eq}} \texttt{uals} \\
 \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han} \\
 \underline{\textbf{l}} \texttt{ess} \ \texttt{than} \ \texttt{or} \ \underline{\textbf{e}} \texttt{quals} \\
\end{array} \right\}
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\}
$$

### Load and Store

$$
\underline{\textbf{f}} \texttt{loat}
\left\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \\
 \underline{\textbf{s}} \texttt{tore} \\
\end{array} \right\}
\left\{ \begin{array}{l}
 \underline{\textbf{w}} \texttt{ord} \\
 \underline{\textbf{d}} \texttt{oubleword} \\
\end{array} \right\}
$$

### Conversion

$$
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\} \
\texttt{from} \
\underline{\textbf{.w}} \texttt{ord} \
\left\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\underline{\textbf{.w}} \texttt{ord} \
\left\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\} \
\texttt{from} \
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\underline{\textbf{.s}} \texttt{ingle} \
\texttt{from} \
\underline{\textbf{.d}} \texttt{ouble}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\underline{\textbf{.d}} \texttt{ouble} \
\texttt{from} \
\underline{\textbf{.s}} \texttt{ingle}
$$

### Other instructions

$$
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{s}} \texttt{i} \underline{\textbf{gn}} \
\texttt{in} \underline{\textbf{j}} \texttt{ection}  
\left\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{n}} \texttt{egative} \\
 \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \texttt{or} \\
\end{array} \right\}
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{class}} \texttt{ify}
\left\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\}
$$
