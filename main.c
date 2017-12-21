/*main.c*/

//
// Searching for movies in a binary search tree.
//
// << Zakee Jabbar(zjabba2) >>
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #02
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int     BSTKey;
typedef int     BSTYear;
typedef char    BSTName[512];

typedef struct BSTNode
{
  BSTKey    ID;
  BSTYear  Year;
  BSTName   Name;
  struct BSTNode  *Left;
  struct BSTNode  *Right;
} BSTNode;

typedef struct BST
{
  BSTNode *Root;
  int      Count;
} BST;


//
// BSTCreate: dynamically creates and returns an empty
// binary search tree:
//
BST *BSTCreate()
{
  BST *tree;

  tree = (BST *)malloc(sizeof(BST));
  tree->Root  = NULL;
  tree->Count = 0;

  return tree;
}

//
// BSTCompareKeys: compares key1 and key2, returning
//   value < 0 if key1 <  key2
//   0         if key1 == key2
//   value > 0 if key1 >  key2
//
int BSTCompareKeys(BSTKey key1, BSTKey key2)
{
  if (key1 < key2)
    return -1;
  else if (key1 == key2)
    return 0;
  else
    return 1;
}


//
// BSTSearch: searches the binary search tree for a node containing the
// same key.  If a match is found, a pointer to the node is returned,
// otherwise NULL is returned.
//
BSTNode *BSTSearch(BST *tree, BSTKey key)
{
  BSTNode *cur;
  cur = tree->Root;

  while(cur != NULL)
  {
     if(BSTCompareKeys(key , cur->ID) == 0)
     {
        return cur;
     }
     else if(BSTCompareKeys(key , cur->ID) < 0)
     {
        cur = cur->Left;
        if(cur != NULL)
        {
            printf(">>Visiting %d: '%s'\n", cur->ID, cur->Name);
        }


     }
     else
     {

        cur = cur->Right;
        if(cur != NULL)
        {
            printf(">>Visiting %d: '%s'\n", cur->ID, cur->Name);
        }

     }

  }

  return NULL;
}

//
// BSTInsert: inserts the given (key, value) pair into the binary search
// tree.  Returns true (non-zero) if the insert was successful, returns
// false (0) if the given key is already in the tree -- in which case the
// given (key, value) pair is not inserted.
//
int BSTInsert(BST *tree, BSTKey key, BSTYear value, BSTName name)
{
  BSTNode *newNode;
   newNode = (BSTNode *) malloc(sizeof(BSTNode));
   newNode->ID = key;
   newNode->Year = value;
   strcpy(newNode->Name,name);
   newNode->Left = NULL;
   newNode->Right = NULL;
   BSTNode *cur;

   if(tree->Root == NULL)
   {
      tree->Root = newNode;
      tree->Count++;
      return 1;
   }
   else
   {
      cur = tree->Root;
      while(cur != NULL)
      {
         if(BSTCompareKeys(key, cur->ID) == 0)
         {
            return 0;
         }

         if(BSTCompareKeys(key, cur->ID) < 0)
         {
            if(cur->Left == NULL)
            {
               cur->Left = newNode;
               tree->Count++;
               return 1;
            }
            else
            {
               cur = cur->Left;
            }

         }
         else
         {
            if(cur->Right == NULL)
            {
               cur->Right = newNode;
               tree->Count++;
               return 1;
            }
            else
            {
               cur = cur->Right;
            }
         }
      }
   }

  return 0;
}

//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);

  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fclose(infile);

  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
  strcpy(s, filename);

  return s;
}


int main()
{

    int i = 0;
    char str[512];
    int   linesize = sizeof(str) / sizeof(str[0]);
    char *token;
    char *token2;
    char *token3;
    BST *tree = BSTCreate();

  // get movies filename from the user/stdin:
    char *MoviesFileName = getFileName();

  // opens the movies file:
    FILE *movieFile = fopen(MoviesFileName, "r");


    fgets(str, linesize, movieFile);  // input a line:

  while (!feof(movieFile))  // until the end of file:
  {
    str[strcspn(str, "\r\n")] = '\0';  // strip EOL char(s):

    token = strtok(str, ",");
    int m = atoi(token);
    token2 = strtok(NULL, ",");
    token3 = strtok(NULL, ",");
    int n = atoi(token3);

    BSTInsert(tree,m, n,token2); //creates the tree

    fgets(str, linesize, movieFile);
  }

  int s;

  scanf("%d", &s); //gets the movie to search for

  BSTNode *n = BSTSearch(tree, s); //searches the tree

  if(n != NULL)
  {
      printf("Movie %d: '%s'\n", s, n->Name); //if found prints the movie ID and name

  }
  else if(n == NULL)
  {
      printf("Movie %d: not found\n", s);  //if not found prints not movie ID and not found
  }




  return 0;
}
