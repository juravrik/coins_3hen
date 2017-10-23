#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct node 
{
  int end_of_key;
  int value;
  struct node *next_char[26];
};

int numchar(char k)
{
  return k + 1 - 'a';
}

struct node *alloc_node()
{
  struct node *n = malloc(sizeof(struct node));
  n->end_of_key = 0;
  n->value = 0;
  for(int i = 0;i < 26;i++)
  {
    n->next_char[i] = NULL;
  }
  return n;
}

void insert_key(struct node *root, char *k, int v)
{
  struct node *n = root;
  int i, len = strlen(k);

  for(i = 0; i < len; i++)
  {
    if(n->next_char[numchar(k[i]) - 1] == NULL)
    {
      n->next_char[numchar(k[i]) - 1] = alloc_node();
    }
    n = n->next_char[numchar(k[i]) - 1];
  }

  n->end_of_key = 1;
  n->value = v;
}

int search_tree(struct node *root, char *key)
{
  int i, len;
  len = strlen(key);
  struct node *n = root;

  for(i = 0; i < len; i++)
  {
    if(n->next_char[numchar(key[i]) - 1] == NULL)
    {
      return -1;
    }
    else
    {
      /* (c) */
      n = n->next_char[numchar(key[i]) - 1];
    }
  }

  if(n->end_of_key == 1)
  {
    /* (d) */
    return n->value;
  }
  else
  {
    return -1;
  }
}

int main(void)
{
  /* 動作チェック */
  struct node *root = alloc_node();

  insert_key(root, "ant", 120);
  insert_key(root, "any", 260);
  insert_key(root, "anyway", 110);
  insert_key(root, "apart", 380);
  insert_key(root, "appear", 290);
  insert_key(root, "apple", 190);
  insert_key(root, "bad", 400);
  insert_key(root, "bag", 220);
  insert_key(root, "below", 310);

  printf("searth_tree(\"anyway\") -> %d\n",search_tree(root, "anyway"));
  printf("searth_tree(\"alice\") -> %d\n",search_tree(root, "alice"));
  return 0;
}