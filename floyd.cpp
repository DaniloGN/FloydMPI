
// C Program for Floyd Warshall Algorithm 
#include <stdio.h>
#include <stdlib.h> 
#include "mpi.h"   
// Number of vertices in the graph 
#define V 4 
  
/* Define Infinite as a large enough value. This value will be used 
  for vertices not connected to each other */
#define INF 99999 
  
// A function to print the solution matrix 
void printSolution(int dist[][V]); 
  
// Solves the all-pairs shortest path problem using Floyd Warshall algorithm 
void floydWarshall (int graph[][V]) 
{ 
    
} 
  
/* A utility function to print solution */
void printSolution(int dist[][V]) 
{ 
} 

int main(int argc, char **argv) 
 {  

    int graph[V][V] = { {0, 5, INF, 10}, 
						{INF, 0, 3, INF}, 
						{INF, INF, 0, 1}, 
						{INF, INF, INF, 0} 
                      }; 
  
    int dist[V][V], i, j, k; 
    
    for (i = 0; i < V; i++) 
        for (j = 0; j < V; j++) 
            dist[i][j] = graph[i][j]; 
      
   int size, rank,teste,sendbuf[V],recbuf[V*V]; 
   MPI_Init(&argc,&argv); 
   MPI_Comm_size (MPI_COMM_WORLD, &size); 
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    for (k = 0; k < V; k++) 
    {
		MPI_Barrier(MPI_COMM_WORLD);
		int root = k % size;
		for(int x = 0; x<V;x++) sendbuf[x] = dist[k][x];
		MPI_Bcast(sendbuf, 1, MPI_INT, root, MPI_COMM_WORLD);
        // Pick all vertices as source one by one 
        for (i = 0; i < V; i++) 
        {	
			if(size == 1){
				teste = 0;
			}
			else{
			 teste = i % size;
			}
			 if(rank == teste){
            // Pick all vertices as destination for the 
            // above picked source 
				for (j = 0; j < V; j++) 
				{ 
					// If vertex k is on the shortest path from 
					// i to j, then update the value of dist[i][j] 
					if (dist[i][k] + sendbuf[j] < dist[i][j]) 
						dist[i][j] = dist[i][k] + sendbuf[j]; 
				}
				MPI_Gather(dist[i],size,MPI_INT,recbuf,size,MPI_INT,0,MPI_COMM_WORLD);
				if(rank == 0){
					int inicio=0;
					int fim = V;
					for(int u=0;u<V;u++){
						if(fim <= size*V){
							while(inicio<fim){
								dist[u][inicio] = recbuf[inicio];
								printf("%d %d %d \n",k,inicio,recbuf[inicio]);
								inicio++;
							}
							fim=inicio+V;
						}
					}
				}
			}
		}
	}
 
      
	MPI_Barrier(MPI_COMM_WORLD);
    // Print the shortest distance matrix 
       printf ("Matriz com menores caminhos \n");
    if(rank == 0){
    for (int i = 0; i < V; i++) 
    { 
        for (int j = 0; j < V; j++) 
        { 
            if (dist[i][j] == INF) 
                printf("%7s", "INF"); 
            else
                printf ("%7d", dist[i][j]); 
        } 
        printf("\n");
	} 
    } 
   MPI_Finalize();  
   return 0; 
 } 
