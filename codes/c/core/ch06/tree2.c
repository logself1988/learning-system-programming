#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode *TreePtr; // typedef

typedef struct tnode
{
  char *word;
  int count;

  TreePtr left; // self reference
  TreePtr right;
} Treenode;

TreePtr addtree (TreePtr, char *);
void printtree (TreePtr);

int
main (int argc, char *argv[])
{
  TreePtr root;
  root = NULL;

  char *words[]
      = { "now", "is",   "the", "time", "for", "all", "good",  "men",
          "to",  "come", "to",  "the",  "aid", "of",  "their", "party" };
  int i;
  for (i = 0; i < 16; i++)
    root = addtree (root, words[i]);

  printtree (root);
  return 0;
}

TreePtr
addtree (TreePtr p, char *word)
{
  int cond;

  if (p == NULL)
    {
      p = (TreePtr)malloc (sizeof (Treenode));
      p->word = word;
      p->count = 1;
      p->left = p->right = NULL;
    }
  else if ((cond = strcmp (word, p->word)) == 0)
    p->count++;
  else if (cond < 0)
    p->left = addtree (p->left, word);
  else
    p->right = addtree (p->right, word);

  return p;
}

void
printtree (TreePtr p)
{
  if (p != NULL)
    {
      printtree (p->left);
      printf ("%4d %s\n", p->count, p->word);
      printtree (p->right);
    }
}