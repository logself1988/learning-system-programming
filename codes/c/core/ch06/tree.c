#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode
{
  char *word;
  int count;

  struct tnode *left; // self reference
  struct tnode *right;
};

struct tnode *addtree (struct tnode *, char *);
void printtree (struct tnode *);

int
main (int argc, char *argv[])
{
  struct tnode *root;
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

struct tnode *
addtree (struct tnode *p, char *word)
{
  int cond;

  if (p == NULL)
    {
      p = (struct tnode *)malloc (sizeof (struct tnode));
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
printtree (struct tnode *p)
{
  if (p != NULL)
    {
      printtree (p->left);
      printf ("%4d %s\n", p->count, p->word);
      printtree (p->right);
    }
}