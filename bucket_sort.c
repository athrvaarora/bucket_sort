#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "list.h"


/* 
compile with -g to collect debugging info needed for Valgrind ( -lm links the math library): 
gcc -g bucket_sort.c list.c -lm

run with Valgrind:
valgrind --leak-check=full ./a.out

On some systems, but not all, you can also use the --show-leak-kinds=all flag:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/


/* // recommended helper functions:
// function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP);
//  function to sort an array sing bucket sort
void bucket_sort(int arr[], int N)
*/
int array_min(int arr[], int N)
{
    int min=arr[0];
    for (int i = 0; i < N; i++)
    {
        if (arr[i]<min)
        {
            min=arr[i];
        }
        
    }
    return min;
    
}

int array_max(int arr[], int N)
{
    int max=arr[0];
    for (int i = 0; i < N; i++)
    {
        if (arr[i]>max)
        {
            max=arr[i];
        }
    }
    return max;
}  

void print_array(int arr[], int N)
{
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}


void bucket_sort(int bucket[],int N)
{
    nodePT *L = malloc(N * sizeof(nodePT));
    for(int i=0; i<N; i++)
    {
        L[i]=NULL;
    }
    double min=(double)array_min(bucket,N);
    double max=(double)array_max(bucket,N);
    double index;
    int idx=0;
    // double K;
    printf("Bucketsort :min = %d, max = %d, N=%d buckets\n",(int)min,(int)max,N);
    for (int i = 0; i < N; i++)
    {
        index = floor(((bucket[i]-min)*N)/(max-min+1));
        idx = (int)index;
        printf("arr[%d] = %d, index = %d\n",i,bucket[i],idx);
        if(L[idx]==NULL)
        {
            L[idx] = new_node(bucket[i]);
        }
        else if(L[idx]->data>=bucket[i])
        {
          insert_front(&L[idx],bucket[i]);

        }
        else
        {
          nodePT previous = L[idx];
          nodePT nextPointer = L[idx]->next;
          while(nextPointer !=NULL && bucket[i]>nextPointer->data)
            {
              previous=nextPointer;
              nextPointer = nextPointer->next;
            }
          nodePT new = new_node(bucket[i]);
          insert_node_after(previous, new);
        }
    }
    for(int j=0;j<N;j++)
      {
        print_list_horiz(L[j]);
      }
    int sorted_arr[N];
    int index_sorted=0;
    for(int k = 0;k<N;k++)
      {
        nodePT node = L[k];
        while(node!=NULL)
          {
            sorted_arr[index_sorted]=node->data;
            index_sorted++;
            node= node->next;
          }
      }
    print_array(sorted_arr, N);
    //printf("%d",N);
    // for(int iter = 0;iter< N;iter++)
    //   {
    //    nodePT temp=L[iter];
    //    nodePT next;
    //    while(temp!=NULL){
    //    next = temp->next;
    //    free(temp);
    //    temp=next;
    //    }
    //   }

    for(int i = 0; i < N; i++)
    {
      destroy_list(L[i]);
      L[i] = NULL;
    }
    free(L);
}

//-------------------------------------------------------------


void run1()
{
	// Fill in your code here. You should not write everything in this function.  
	// Write some helper functions to separate the work.	
	/*printf("\n-------run1 - this is a place holder. You need to edit this function.------ \n");*/
    char filename[50];
    printf("Enter the name of your file : ");
    scanf("%s", filename);
    FILE *fp = fopen(filename,"r+");
    if (fp == NULL)
    {
        printf("File not found");
    }
    else
    {
        int N=0;
        fscanf(fp,"%d\n",&N);
        int *bucket = malloc(N * sizeof(int));
        for(int i=0; i<N; i++)
        {
            fscanf(fp,"%d",&bucket[i]);
        }
        fclose(fp);
        print_array(bucket,N);
        bucket_sort(bucket,N);
        free(bucket);





    }

     
}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		char ch;
		scanf("%d%c",&option, &ch);  // ch is used to remove the Enter from the input buffer
 	} while (option == 1);

   return 0;
}