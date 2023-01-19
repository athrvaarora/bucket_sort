
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LINE_LENGTH 1000
#define MAX_COURCES 30
#define MAX_FILENAME_CHARS 30
#define MAX_COURCENAME_CHARS 30

enum colors {GRAY, WHITE, BLACK};

int indexsearch(char elem_array[][MAX_COURCENAME_CHARS],char search_string[],int count)
{
  for(int i=0;i<count;i++)
    {
      if(strcmp(elem_array[i],search_string)==0)
      {
        return i;
      }
    }
  return -1;
  
}
void matrix_initialization(int matrix[100][100],int size)
{
  for(int i=0;i<size;i++)
    {
      for(int j=0;j<size;j++)
      {
        matrix[i][j]=0;
      }
    }
}
void addEdges(int matrix[100][100],int i,int j)
{
  matrix[i][j]=1;
}
void printMatrix(int matrix[100][100],int size)
{
  int count=0;
  printf("   |");
  for(int i=0;i<size;i++)
  {
     printf("%3d",i); 
  }
  printf("\n");
  for(int i=0;i<5*size-2;i++)
  {
    printf("-");    
  }
  printf("\n");
  for(int i=0;i<size;i++)
    {
      printf("%3d|",i);
      for(int j=0;j<size;j++)
        {
          printf("%3d",matrix[i][j]);
        }
      printf("\n");
    }
}
void adjacency_matrix(char elem_array[][MAX_COURCENAME_CHARS],int adjencencymatrix[100][100],int vertexes,char filename[MAX_FILENAME_CHARS])
{
  char *token;
  int found_index=0;
  char fileline[MAX_LINE_LENGTH];
  FILE *fptr = fopen(filename,"r");
  for(int i=0;i<vertexes;i++)
  {
    fgets(fileline, MAX_LINE_LENGTH, fptr);
    token = strtok(fileline," \n");
    token = strtok(NULL," \n");
    while(token!=NULL)
    {  
      found_index = indexsearch(elem_array,token,vertexes);
      if(found_index!=-1)
      {
        addEdges(adjencencymatrix,found_index,i);
      }
      token = strtok(NULL," \n");
    }
  }
  printMatrix(adjencencymatrix,vertexes);
  fclose(fptr);
}
void dfs_visit(int matrix[100][100],int num_cources,int i,enum colors *color,int *order, int* index,int  cycle[0])
{
  color[i] = GRAY;
  for(int j=0;j<num_cources;j++)
  {
    if(matrix[i][j]==1)
    {
      if(color[j]==WHITE)
      {
        dfs_visit(matrix,num_cources,j,color,order,index,cycle);
      }
      if(color[j]==GRAY)
      {
        cycle[0]= 1;
      }
    }
  }
  color[i] = BLACK;
  order[(*index)++]=i;
}
void dfs(int matrix[100][100],int num_cources,int *order,int cycle[0])
{
  int index =0;
  enum colors color[num_cources];
  for(int i=0;i<num_cources;i++)
  {
    color[i]=WHITE;
  }
  for(int i=0;i<num_cources;i++)
  {
    if(color[i]==WHITE)
    {
      dfs_visit(matrix,num_cources,i,color,order,&index,cycle); 
    }
  }
}
int main()
{
  char filename[MAX_FILENAME_CHARS];
  char *first_elements;
  char elem_array[MAX_LINE_LENGTH][MAX_COURCENAME_CHARS];
  char fileline[MAX_LINE_LENGTH];
  char elements[MAX_COURCES]={0};
  int cycle[2]={0};
  int count=0;
  printf("Enter filename: ");
  scanf("%s", filename);
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
  {
    printf("Could not open file %s. Exit\n",filename);
    printf("Failed to read from file. Program will terminate. \n");
    exit(0);
  }
  while(fgets(fileline, MAX_LINE_LENGTH, fp)!= NULL)
  {
    count++;
  }
  int  adjencency_matrix[100][100];
  matrix_initialization(adjencency_matrix,count);
  fseek(fp, 0, 0);
  printf("Number of vertices in built graph: %d\n", count);
  printf("Vertex - coursename currespondence\n");
  for(int i=0; i<count; i++)
  {
    fgets(fileline, MAX_LINE_LENGTH, fp);
    strcpy(elem_array[i],strtok(fileline, " \n"));
    printf("%d.  %s\n",i, elem_array[i]);
  }
  fclose(fp);
  int order_of_cources[MAX_COURCES]={0};
  printf("\n\nAdjacency matrix: \n");
  adjacency_matrix(elem_array, adjencency_matrix, count,filename);
  
  dfs(adjencency_matrix,count,order_of_cources,cycle);
  if (cycle[0]!=1)
  {
    printf("\nOrder in which to take courses: \n");
    int iter =1;
    for(int i=count-1;i>=0;i--)
    {
      printf("%d - %s (corresponds to graph vertex %d) \n",iter++, elem_array[order_of_cources[i]],order_of_cources[i]);
    
    }
  }
  else
  {
    printf("There was at least one cycle. There is no possible ordering of the courses. \n");
  }
  return 0;
   
}