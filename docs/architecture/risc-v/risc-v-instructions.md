# Digrams of RISC-V Instructions

> Notes:
>
> 1. replace `\left\{` with `\left\\{`, `\right\}` with `\right\\}` when pushing to Github.
>
> 2. replace `\require{cancel}` with `%\require{cancel}` when pushing to Github..

## 2 RV32I

### Integer Computation

$$
\begin{array}{l}
\underline{\textbf{add}}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\underline{\textbf{sub}} \texttt{trace}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{and}} \\
 \underline{\textbf{or}} \\
 \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \underline{\textbf{or}} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{l}} \texttt{eft}\ \underline{\textbf{l}} \texttt{ogical} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{a}} \texttt{rithmetic} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{l}} \texttt{ogical} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\underline{\textbf{l}} \texttt{oad} \ \underline{\textbf{u}} \texttt{pper} \ \underline{\textbf{i}} \texttt{mmediate}
\\
\underline{\textbf{a}} \texttt{dd} \ \underline{\textbf{u}} \texttt{pper} \ \underline{\textbf{i}} \texttt{mmediate} \ \texttt{to} \ \underline{\textbf{pc}}
\\
\underline{\textbf{s}} \texttt{et} \ \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}     
\end{array}
$$

### Loads and Stores

$$
\begin{array}{l}
\left\\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \\
 \underline{\textbf{s}} \texttt{tore} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{b}} \texttt{yte} \\
 \underline{\textbf{h}} \texttt{alfword} \\
 \underline{\textbf{w}} \texttt{ord} \\
\end{array} \right\\}
\\
\underline{\textbf{l}} \texttt{oad}
\left\\{ \begin{array}{l}
 \underline{\textbf{b}} \texttt{yte} \\
 \underline{\textbf{h}} \texttt{alfword} \\
\end{array} \right\\}
\underline{\textbf{u}} \texttt{nsigned} \\
\end{array}
$$

### Control transfer

$$
\begin{array}{l}
\underline{\textbf{b}} \texttt{ranch}
\left\\{ \begin{array}{l}
 \underline{\textbf{eq}} \texttt{ual} \\
 \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
\end{array} \right\\}
\\
\underline{\textbf{b}} \texttt{ranch}
\left\\{ \begin{array}{l}
 \underline{\textbf{g}} \texttt{reater} \ \texttt{than} \ \texttt{or} \ \underline{\textbf{e}} \texttt{qual} \\
 \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\underline{\textbf{j}} \texttt{ump} \ \underline{\textbf{a}} \texttt{nd} \ \underline{\textbf{l}} \texttt{ink}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{r}} \texttt{egister} \\
\end{array} \right\\}
\end{array}
$$

### Miscellaneous instructions

$$
\begin{array}{l}
\underline{\textbf{fence}} \ \texttt{loads} \ \texttt{and} \ \texttt{stores}
\\
\underline{\textbf{fence.i}} \texttt{nstruction} \ \texttt{and} \ \texttt{data}
\\
\underline{\textbf{e}} \texttt{nvironment}
\left\\{ \begin{array}{l}
 \underline{\textbf{break}} \\
 \underline{\textbf{call}} \\
\end{array} \right\\}
\\
\underline{\textbf{c}} \texttt{ontrol} \ \underline{\textbf{s}} \texttt{tatus} \ \underline{\textbf{r}} \texttt{egister}
\left\\{ \begin{array}{l}
 \underline{\textbf{r}} \texttt{ual} \\
 \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{r}} \texttt{ead} \ \texttt{and} \ \underline{\textbf{c}} \texttt{lear} \ \texttt{bit} \\
 \underline{\textbf{r}} \texttt{ead} \ \texttt{and} \ \underline{\textbf{s}} \texttt{et} \ \texttt{bit} \\
 \underline{\textbf{r}} \texttt{ead} \ \texttt{and} \ \underline{\textbf{w}} \texttt{rite} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\end{array}
$$

## 4 RV32M

$$
\begin{array}{l}
\underline{\textbf{mul}} \texttt{tiply}
\\
\underline{\textbf{mul}} \texttt{tiply} \ \underline{\textbf{h}} \texttt{igh}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
 \underline{\textbf{s}} \texttt{igned} \ \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{div}} \texttt{ide} \\
 \underline{\textbf{rem}} \texttt{ainder} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\end{array}
$$

## 5 RV32FD

### Floating-Point Computation

$$
\begin{array}{l}
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{sub}} \texttt{tract} \\
 \underline{\textbf{mul}} \texttt{tiply} \\
 \underline{\textbf{div}} \texttt{ide} \\
 \underline{\textbf{sq}} \texttt{uare}  \underline{\textbf{r}} \texttt{oo} \underline{\textbf{t}} \\
 \underline{\textbf{min}} \texttt{imum} \\
 \underline{\textbf{max}} \texttt{imum} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l} \\
 \underline{} \\
 \underline{\textbf{n}} \texttt{egative} \\
\end{array} \right\\}
\underline{\textbf{m}} \texttt{ultiply}
\left\\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{sub}} \texttt{tract} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{m}} \texttt{o} \underline{\textbf{v}} \texttt{e} \
\texttt{to} \
\underline{\textbf{.w}} \texttt{ord} \
\texttt{from} \
\underline{\textbf{.x}} \ \texttt{register}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{m}} \texttt{o} \underline{\textbf{v}} \texttt{e} \
\texttt{to} \
\underline{\textbf{.x}} \ \texttt{register} \
\texttt{from} \
\underline{\textbf{.w}} \texttt{ord}
\end{array}
$$

### Comparison

$$
\texttt{compare} \
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l}
 \underline{\textbf{eq}} \texttt{uals} \\
 \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han} \\
 \underline{\textbf{l}} \texttt{ess} \ \texttt{than} \ \texttt{or} \ \underline{\textbf{e}} \texttt{quals} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
$$

### Load and Store

$$
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \\
 \underline{\textbf{s}} \texttt{tore} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{w}} \texttt{ord} \\
 \underline{\textbf{d}} \texttt{oubleword} \\
\end{array} \right\\}
$$

### Conversion

$$
\begin{array}{l}
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\} \
\texttt{from} \
\underline{\textbf{.w}} \texttt{ord} \
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\underline{\textbf{.w}} \texttt{ord} \
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\} \
\texttt{from} \
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
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
\end{array}
$$

### Other instructions

$$
\begin{array}{l}
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{s}} \texttt{i} \underline{\textbf{gn}} \
\texttt{in} \underline{\textbf{j}} \texttt{ection}  
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{n}} \texttt{egative} \\
 \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \texttt{or} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{class}} \texttt{ify}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\end{array}
$$

## 6 RV32A

$$
\begin{array}{l}
\underline{\textbf{a}} \texttt{tomic} \
\underline{\textbf{m}} \texttt{emory} \
\underline{\textbf{o}} \texttt{peration}
\left\\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{and}} \\
 \underline{\textbf{or}} \\
 \underline{\textbf{swap}} \\
 \underline{\textbf{xor}} \\
 \underline{\textbf{max}} \texttt{imum} \\
 \underline{\textbf{max}} \texttt{imum} \ \underline{\textbf{u}} \texttt{nsigned} \\
 \underline{\textbf{min}} \texttt{imum} \\
 \underline{\textbf{min}} \texttt{imum} \ \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\underline{\textbf{.w}} \texttt{ord}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \ \underline{\textbf{r}} \texttt{eserved} \\
 \underline{\textbf{s}} \texttt{tore} \ \underline{\textbf{c}} \texttt{onditional} \\
\end{array} \right\\}
\underline{\textbf{.w}} \texttt{ord}
\end{array}
$$

## 7 RV32C

### Integer Computation

$$
\begin{array}{l}
\underline{\textbf{c.add}}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\underline{\textbf{c.add}} \ \underline{\textbf{i}} \texttt{mmediate} ^{\star} \ \underline{\textbf{16}} \ \texttt{to} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer}
\\
\underline{\textbf{c.add}} \ \underline{\textbf{i}} \texttt{mmediate} ^{\star} \ \underline{\textbf{4}} \ \texttt{to} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer} \ \underline{\textbf{n}} \texttt{ondestructive}
\\
\underline{\textbf{c.sub}} \texttt{tract}
\\
\underline{\textbf{c.}}
\left\\{ \begin{array}{l}
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{l}} \texttt{eft}\ \underline{\textbf{l}} \texttt{ogical} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{a}} \texttt{rithmetic} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{l}} \texttt{ogical} \\
\end{array} \right\\}
\underline{\textbf{i}} \texttt{mmediate}
\\
\underline{\textbf{c.and}}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\underline{\textbf{c.or}}
\\
\underline{\textbf{c.m}} \texttt{o} \underline{\textbf{v}} \texttt{e}
\\
\underline{\textbf{c.}} \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \underline{\textbf{or}}
\\
\underline{\textbf{c.l}} \texttt{oad}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{pper} \\
\end{array} \right\\}
 \underline{\textbf{i}} \texttt{mmediate}
\end{array}
$$

### Load and Store

$$
\begin{array}{l}
  \underline{\textbf{c.}}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \underline{\textbf{f}} \texttt{loat} \\
  \end{array} \right\\}
  \left\\{ \begin{array}{l}
   \underline{\textbf{l}} \texttt{oad} \\
   \underline{\textbf{s}} \texttt{tore} \\
  \end{array} \right\\}
  \underline{\textbf{w}} \texttt{ord}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \texttt{using} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer} \\
  \end{array} \right\\}
\\
  \underline{\textbf{c.f}} \texttt{loat}
  \left\\{ \begin{array}{l}
   \underline{\textbf{l}} \texttt{oad} \\
   \underline{\textbf{s}} \texttt{tore} \\
  \end{array} \right\\}
  \underline{\textbf{d}} \texttt{oubleword}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \texttt{using} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer} \\
  \end{array} \right\\}
\end{array}
$$

### Control transfer

$$
\begin{array}{l}
  \underline{\textbf{c.b}} \texttt{ranch}
  \left\\{ \begin{array}{l}
   \underline{\textbf{eq}} \texttt{ual} \\
   \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
  \end{array} \right\\}
  \texttt{to} \
  \underline{\textbf{z}} \texttt{ero}
\\
  \underline{\textbf{c.j}} \texttt{ump}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \underline{\textbf{a}} \texttt{nd} \ \underline{\textbf{l}} \texttt{ink} \\
  \end{array} \right\\}
\\
  \underline{\textbf{c.j}} \texttt{ump}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \underline{\textbf{a}} \texttt{nd} \ \underline{\textbf{l}} \texttt{ink} \\
  \end{array} \right\\}
  \underline{\textbf{r}} \texttt{egister}
\end{array}
$$

### Other instructions

$$
\underline{\textbf{c.e}} \texttt{nvironment} \ \underline{\textbf{break}}
$$

## ~~RV32V~~

- `.vv`, `.vs`, `.sv`, `.vvv`, `.vvs`, `.vsv`, `.vss`: `v` for vector, `s` for scalar.

### Computation

$$
\begin{array}{l}
 \underline{\textbf{v}} \texttt{ector}
 \left\\{ \begin{array}{l}
  \underline{\textbf{add}} \\
  \underline{\textbf{mul}} \texttt{tiply} \\
  \underline{\textbf{mul}} \texttt{tiply} \ \underline{\textbf{h}} \texttt{igh} \\
  \underline{\textbf{and}} \\
  \underline{\textbf{or}} \\
  \underline{\textbf{xor}} \\
  \underline{\textbf{min}} \texttt{mum} \\
  \underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
 \end{array} \right\\}
 \left\\{ \begin{array}{l}
  \underline{\textbf{.vv}} \\
  \underline{\textbf{.vs}} \\
 \end{array} \right\\}
\\
 \underline{\textbf{v}} \texttt{ector}
 \left\\{ \begin{array}{l}
  \underline{\textbf{sub}} \texttt{tract} \\
  \underline{\textbf{div}} \texttt{ide} \\
  \underline{\textbf{rem}} \texttt{ainder} \\
  \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{l}} \texttt{eft}\ \underline{\textbf{l}} \texttt{ogical} \\
  \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{a}} \texttt{rithmetic} \\
  \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{l}} \texttt{ogical} \\
 \end{array} \right\\}
 \left\\{ \begin{array}{l}
  \underline{\textbf{.vv}} \\
  \underline{\textbf{.vs}} \\
  \underline{\textbf{.sv}} \\
 \end{array} \right\\}
\\
 \underline{\textbf{v}} \texttt{ector} \ \underline{\textbf{f}} \texttt{used}
 \left\\{ \begin{array}{l} \\
  \underline{} \\
  \underline{\textbf{n}} \texttt{egative} \\
 \end{array} \right\\}
 \underline{\textbf{m}} \texttt{ultiply}
 \left\\{ \begin{array}{l}
  \underline{\textbf{add}} \\
  \underline{\textbf{sub}} \texttt{tract} \\
 \end{array} \right\\}
 \left\\{ \begin{array}{l}
  \underline{\textbf{.vvv}} \\
  \underline{\textbf{.vvs}} \\
  \underline{\textbf{.vsv}} \\
  \underline{\textbf{.vss}} \\
 \end{array} \right\\}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{s}} \texttt{i} \underline{\textbf{gn}} \
 \texttt{in} \underline{\textbf{j}} \texttt{ection}  
 \left\\{ \begin{array}{l}
  \underline{} \\
  \underline{\textbf{n}} \texttt{egative} \\
  \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \texttt{or} \\
 \end{array} \right\\}
 \underline{\textbf{.vv}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{class.v}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{mov}} \texttt{e} \
 \underline{\textbf{.vv}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{sq}} \texttt{uare} \
 \underline{\textbf{r}} \texttt{oo} \
 \underline{\textbf{t.v}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{a}} \texttt{tomic} \
 \underline{\textbf{m}} \texttt{emory} \
 \underline{\textbf{o}} \texttt{peration}
 \left\\{ \begin{array}{l}
  \underline{\textbf{add}} \\
  \underline{\textbf{and}} \\
  \underline{\textbf{or}} \\
  \underline{\textbf{swap}} \\
  \underline{\textbf{xor}} \\
  \underline{\textbf{max}} \texttt{imum} \\
  \underline{\textbf{min}} \texttt{imum} \\
 \end{array} \right\\}
 \left\\{ \begin{array}{l}
  \underline{\textbf{.vv}} \\
  \underline{\textbf{.vs}} \\
 \end{array} \right\\}
\end{array}
$$

### Load and Store

$$
\begin{array}{l}
 \underline{\textbf{v}} \texttt{ector}
 \left\\{ \begin{array}{l}
  \underline{\textbf{l}} \texttt{oa} \underline{\textbf{d}} \\
  \underline{\textbf{st}} \texttt{ore} \\
 \end{array} \right\\}
 \left\\{ \begin{array}{l}
  \underline{} \\
  \underline{\textbf{s}} \texttt{trided} \\
  \texttt{inde} \underline{\textbf{x}}\texttt{ed} \\
 \end{array} \right\\}
\end{array}
$$

### Comparison

$$
\begin{array}{l}
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{p}} \texttt{redicate}
 \left\\{ \begin{array}{l}
  \underline{\textbf{eq}} \texttt{ual} \\
  \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
  \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han} \\
  \underline{\textbf{g}} \texttt{reater} \ \texttt{than} \ \texttt{or} \ \underline{\textbf{e}} \texttt{qual} \\
 \end{array} \right\\}
 \left\\{ \begin{array}{l}
  \underline{\textbf{.vv}} \\
  \underline{\textbf{.vs}} \\
 \end{array} \right\\}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{p}} \texttt{redicate}
 \left\\{ \begin{array}{l}
  \underline{\textbf{and}} \\
  \underline{\textbf{and}} \ \underline{\textbf{n}} \texttt{ot} \\
  \underline{\textbf{or}} \\
  \underline{\textbf{xor}} \\
  \underline{\textbf{n}} \texttt{ot} \\
 \end{array} \right\\}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{p}} \texttt{redicate} \
 \underline{\textbf{swap}}
\end{array}
$$

### Miscellaneous instructions

$$
\begin{array}{l}
 \underline{\textbf{set}} \
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{l}} \texttt{ength}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{extract.vs}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{merge.vv}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{select.vv}}
\\
 \underline{\textbf{v}} \texttt{ector} \
 \underline{\textbf{set}} \
 \underline{\textbf{d}} \texttt{ata} \
 \underline{\textbf{c}} \texttt{on} \underline{\textbf{f}} \texttt{i} \underline{\textbf{g}} \texttt{uration}
\end{array}
$$

## RV64

### RV64I

#### Integer Computation

$$
\begin{array}{l}
\underline{\textbf{add}}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\underline{\textbf{mul}} \texttt{tiply} \ \underline{\textbf{h}} \texttt{igh}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
 \underline{\textbf{s}} \texttt{igned} \ \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{div}} \texttt{ide} \\
 \underline{\textbf{rem}} \texttt{ainder} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\underline{\textbf{sub}} \texttt{trace}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{and}} \\
 \underline{\textbf{or}} \\
 \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \underline{\textbf{or}} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{l}} \texttt{eft}\ \underline{\textbf{l}} \texttt{ogical} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{a}} \texttt{rithmetic} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{l}} \texttt{ogical} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\underline{\textbf{l}} \texttt{oad} \ \underline{\textbf{u}} \texttt{pper} \ \underline{\textbf{i}} \texttt{mmediate}
\\
\underline{\textbf{a}} \texttt{dd} \ \underline{\textbf{u}} \texttt{pper} \ \underline{\textbf{i}} \texttt{mmediate} \ \texttt{to} \ \underline{\textbf{pc}}
\\
\underline{\textbf{s}} \texttt{et} \ \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}     
\end{array}
$$

#### Loads and Stores

$$
\begin{array}{l}
\left\\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \\
 \underline{\textbf{s}} \texttt{tore} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{b}} \texttt{yte} \\
 \underline{\textbf{h}} \texttt{alfword} \\
 \underline{\textbf{w}} \texttt{ord} \\
 \begin{array}{l}
 \color{red}{\underline{\textbf{d}} \texttt{oubleword}} \\
\end{array}
\end{array} \right\\}
\\
\underline{\textbf{l}} \texttt{oad}
\left\\{ \begin{array}{l}
 \underline{\textbf{b}} \texttt{yte} \\
 \underline{\textbf{h}} \texttt{alfword} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\underline{\textbf{u}} \texttt{nsigned} \\
\end{array}
$$

#### Control transfer

$$
\begin{array}{l}
\underline{\textbf{b}} \texttt{ranch}
\left\\{ \begin{array}{l}
 \underline{\textbf{eq}} \texttt{ual} \\
 \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
\end{array} \right\\}
\\
\underline{\textbf{b}} \texttt{ranch}
\left\\{ \begin{array}{l}
 \underline{\textbf{g}} \texttt{reater} \ \texttt{than} \ \texttt{or} \ \underline{\textbf{e}} \texttt{qual} \\
 \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\underline{\textbf{j}} \texttt{ump} \ \underline{\textbf{a}} \texttt{nd} \ \underline{\textbf{l}} \texttt{ink}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{r}} \texttt{egister} \\
\end{array} \right\\}
\end{array}
$$

#### Miscellaneous instructions

$$
\begin{array}{l}
\underline{\textbf{fence}} \ \texttt{loads} \ \texttt{and} \ \texttt{stores}
\\
\underline{\textbf{fence.i}} \texttt{nstruction} \ \texttt{and} \ \texttt{data}
\\
\underline{\textbf{e}} \texttt{nvironment}
\left\\{ \begin{array}{l}
 \underline{\textbf{break}} \\
 \underline{\textbf{call}} \\
\end{array} \right\\}
\\
\underline{\textbf{c}} \texttt{ontrol} \ \underline{\textbf{s}} \texttt{tatus} \ \underline{\textbf{r}} \texttt{egister}
\left\\{ \begin{array}{l}
 \underline{\textbf{r}} \texttt{ual} \\
 \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{r}} \texttt{ead} \ \texttt{and} \ \underline{\textbf{c}} \texttt{lear} \ \texttt{bit} \\
 \underline{\textbf{r}} \texttt{ead} \ \texttt{and} \ \underline{\textbf{s}} \texttt{et} \ \texttt{bit} \\
 \underline{\textbf{r}} \texttt{ead} \ \texttt{and} \ \underline{\textbf{w}} \texttt{rite} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\end{array}
$$

### RV64M

$$
\begin{array}{l}
\underline{\textbf{mul}} \texttt{tiply}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\underline{\textbf{mul}} \texttt{tiply} \ \underline{\textbf{h}} \texttt{igh}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
 \underline{\textbf{s}} \texttt{igned} \ \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{div}} \texttt{ide} \\
 \underline{\textbf{rem}} \texttt{ainder} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\end{array}
$$

### RV64A

$$
\begin{array}{l}
\underline{\textbf{a}} \texttt{tomic} \
\underline{\textbf{m}} \texttt{emory} \
\underline{\textbf{o}} \texttt{peration}
\left\\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{and}} \\
 \underline{\textbf{or}} \\
 \underline{\textbf{swap}} \\
 \underline{\textbf{xor}} \\
 \underline{\textbf{max}} \texttt{imum} \\
 \underline{\textbf{max}} \texttt{imum} \ \underline{\textbf{u}} \texttt{nsigned} \\
 \underline{\textbf{min}} \texttt{imum} \\
 \underline{\textbf{min}} \texttt{imum} \ \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.w}} \texttt{ord} \\
 \color{red}{\underline{\textbf{d}} \texttt{oubleword}} \\
\end{array} \right\\}
\\
\left\\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \ \underline{\textbf{r}} \texttt{eserved} \\
 \underline{\textbf{s}} \texttt{tore} \ \underline{\textbf{c}} \texttt{onditional} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.w}} \texttt{ord} \\
 \color{red}{\underline{\textbf{d}} \texttt{oubleword}} \\
\end{array} \right\\}
\end{array}
$$

### RV64FD

#### Floating-Point Computation

$$
\begin{array}{l}
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{sub}} \texttt{tract} \\
 \underline{\textbf{mul}} \texttt{tiply} \\
 \underline{\textbf{div}} \texttt{ide} \\
 \underline{\textbf{sq}} \texttt{uare}  \underline{\textbf{r}} \texttt{oo} \underline{\textbf{t}} \\
 \underline{\textbf{min}} \texttt{imum} \\
 \underline{\textbf{max}} \texttt{imum} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l} \\
 \underline{} \\
 \underline{\textbf{n}} \texttt{egative} \\
\end{array} \right\\}
\underline{\textbf{m}} \texttt{ultiply}
\left\\{ \begin{array}{l}
 \underline{\textbf{add}} \\
 \underline{\textbf{sub}} \texttt{tract} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{m}} \texttt{o} \underline{\textbf{v}} \texttt{e} \
\texttt{to} \
\left\\{ \begin{array}{l}
 \underline{\textbf{.w}} \texttt{ord} \\
 \color{red}{\underline{\textbf{.d}} \texttt{ouble}} \\
\end{array} \right\\}
\texttt{from} \
\underline{\textbf{.x}} \ \texttt{register}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{m}} \texttt{o} \underline{\textbf{v}} \texttt{e} \
\texttt{to} \
\underline{\textbf{.x}} \ \texttt{register} \
\texttt{from}
\left\\{ \begin{array}{l}
 \underline{\textbf{.w}} \texttt{ord} \\
 \color{red}{\underline{\textbf{.d}} \texttt{ouble}} \\
\end{array} \right\\}
\end{array}
$$

#### Comparison

$$
\texttt{compare} \
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l}
 \underline{\textbf{eq}} \texttt{uals} \\
 \underline{\textbf{l}} \texttt{ess} \ \underline{\textbf{t}} \texttt{han} \\
 \underline{\textbf{l}} \texttt{ess} \ \texttt{than} \ \texttt{or} \ \underline{\textbf{e}} \texttt{quals} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
$$

#### Load and Store

$$
\underline{\textbf{f}} \texttt{loat}
\left\\{ \begin{array}{l}
 \underline{\textbf{l}} \texttt{oad} \\
 \underline{\textbf{s}} \texttt{tore} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{w}} \texttt{ord} \\
 \underline{\textbf{d}} \texttt{oubleword} \\
\end{array} \right\\}
$$

#### Conversion

$$
\begin{array}{l}
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\} \
\texttt{from}
\left\\{ \begin{array}{l}
 \underline{\textbf{.w}} \texttt{ord} \\
 \color{red}{\underline{\textbf{.l}} \texttt{ong}} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{c}} \texttt{on} \underline{\textbf{v}} \texttt{er} \underline{\textbf{t}} \
\texttt{to} \
\left\\{ \begin{array}{l}
 \underline{\textbf{.w}} \texttt{ord} \\
 \color{red}{\underline{\textbf{.l}} \texttt{ong}} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{nsigned} \\
\end{array} \right\\} \
\texttt{from} \
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
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
\end{array}
$$

#### Other instructions

$$
\begin{array}{l}
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{s}} \texttt{i} \underline{\textbf{gn}} \
\texttt{in} \underline{\textbf{j}} \texttt{ection}  
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{n}} \texttt{egative} \\
 \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \texttt{or} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\\
\underline{\textbf{f}} \texttt{loat} \
\underline{\textbf{class}} \texttt{ify}
\left\\{ \begin{array}{l}
 \underline{\textbf{.s}} \texttt{ingle} \\
 \underline{\textbf{.d}} \texttt{ouble} \\
\end{array} \right\\}
\end{array}
$$

### RV64C

#### Integer Computation

$$
\begin{array}{l}
\underline{\textbf{c.add}}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\underline{\textbf{c.add}} \ \underline{\textbf{i}} \texttt{mmediate} ^{\star} \ \underline{\textbf{16}} \ \texttt{to} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer}
\\
\underline{\textbf{c.add}} \ \underline{\textbf{i}} \texttt{mmediate} ^{\star} \ \underline{\textbf{4}} \ \texttt{to} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer} \ \underline{\textbf{n}} \texttt{ondestructive}
\\
\underline{\textbf{c.sub}} \texttt{tract}
\left\\{ \begin{array}{l}
 \color{red}{\underline{}} \\
 \color{red}{\underline{\textbf{w}} \texttt{ord}} \\
\end{array} \right\\}
\\
\underline{\textbf{c.}}
\left\\{ \begin{array}{l}
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{l}} \texttt{eft}\ \underline{\textbf{l}} \texttt{ogical} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{a}} \texttt{rithmetic} \\
 \underline{\textbf{s}} \texttt{hift} \ \underline{\textbf{r}} \texttt{ight}\ \underline{\textbf{l}} \texttt{ogical} \\
\end{array} \right\\}
\underline{\textbf{i}} \texttt{mmediate}
\\
\underline{\textbf{c.and}}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{i}} \texttt{mmediate} \\
\end{array} \right\\}
\\
\underline{\textbf{c.or}}
\\
\underline{\textbf{c.m}} \texttt{o} \underline{\textbf{v}} \texttt{e}
\\
\underline{\textbf{c.}} \texttt{e} \underline{\textbf{x}} \texttt{clusive} \ \underline{\textbf{or}}
\\
\underline{\textbf{c.l}} \texttt{oad}
\left\\{ \begin{array}{l}
 \underline{} \\
 \underline{\textbf{u}} \texttt{pper} \\
\end{array} \right\\}
 \underline{\textbf{i}} \texttt{mmediate}
\end{array}
$$

#### Load and Store

$$
%\require{cancel}
\begin{array}{l}
  \underline{\textbf{c.}}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \color{red}{\xcancel{\underline{\textbf{f}} \texttt{loat}}} \\
  \end{array} \right\\}
  \left\\{ \begin{array}{l}
   \underline{\textbf{l}} \texttt{oad} \\
   \underline{\textbf{s}} \texttt{tore} \\
  \end{array} \right\\}
  \left\\{ \begin{array}{l}
   \color{red}{\xcancel{\underline{\textbf{w}} \texttt{ord}}} \\
   \color{red}{\underline{\textbf{d}} \texttt{oubleword}} \\
  \end{array} \right\\}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \texttt{using} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer} \\
  \end{array} \right\\}
\\
  \underline{\textbf{c.f}} \texttt{loat}
  \left\\{ \begin{array}{l}
   \underline{\textbf{l}} \texttt{oad} \\
   \underline{\textbf{s}} \texttt{tore} \\
  \end{array} \right\\}
  \underline{\textbf{d}} \texttt{oubleword}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \texttt{using} \ \underline{\textbf{s}} \texttt{tack} \ \underline{\textbf{p}} \texttt{ointer} \\
  \end{array} \right\\}
\end{array}
$$

#### Control transfer

$$
%\require{cancel}
\begin{array}{l}
  \underline{\textbf{c.b}} \texttt{ranch}
  \left\\{ \begin{array}{l}
   \underline{\textbf{eq}} \texttt{ual} \\
   \underline{\textbf{n}} \texttt{ot} \ \underline{\textbf{e}} \texttt{qual} \\
  \end{array} \right\\}
  \texttt{to} \
  \underline{\textbf{z}} \texttt{ero}
\\
  \underline{\textbf{c.j}} \texttt{ump}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \color{red}{ \xcancel{\underline{\textbf{a}} \texttt{nd} \ \underline{\textbf{l}} \texttt{ink}}} \\
  \end{array} \right\\}
\\
  \underline{\textbf{c.j}} \texttt{ump}
  \left\\{ \begin{array}{l}
   \underline{} \\
   \underline{\textbf{a}} \texttt{nd} \ \underline{\textbf{l}} \texttt{ink} \\
  \end{array} \right\\}
  \underline{\textbf{r}} \texttt{egister}
\end{array}
$$

#### Other instructions

$$
\underline{\textbf{c.e}} \texttt{nvironment} \ \underline{\textbf{break}}
$$

## RV32/64 Privileged Instructions

$$
\begin{array}{l}
 \left\\{ \begin{array}{l}
  \underline{\textbf{m}} \texttt{achine-mode} \\
  \underline{\textbf{s}} \texttt{upervisor-mode} \\
 \end{array} \right\\}
 \texttt{trap} \
 \underline{\textbf{ret}} \texttt{urn}
\\
 \underline{\textbf{s}} \texttt{upervisor-mode} \
 \underline{\textbf{fence.}} \
 \underline{\textbf{v}} \texttt{irtual} \
 \underline{\textbf{m}} \texttt{emory} \
 \underline{\textbf{a}} \texttt{ddress}
\\
 \underline{\textbf{w}} \texttt{ait} \
 \underline{\textbf{f}} \texttt{or} \
 \underline{\textbf{i}} \texttt{nterrupt}
\end{array}
$$
