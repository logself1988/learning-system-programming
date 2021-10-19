// clang -cc1 -dump-tokens min.c
// clang -fsyntax-only -Xclang -ast-dump min.c

// clang -fsyntax-only -Xclang -ast-view min.c
// Stmt::viewAST is only available in debug builds on systems with Graphviz or gv!


int min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}
