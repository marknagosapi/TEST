#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR printf("[ERROR] Oops! Something went wrong! :(");

typedef struct{
    int* neigh;
    int degree;
}Point;

void zero(int **, int);
int cmp(const void * , const void *);

int main() {
    FILE *f = fopen("knots.txt", "r");

    if(f==NULL){
        printf("A problem occured opening the file!\n");
        //ERROR;
        exit(1);
    }

    int n, elek;
    fscanf(f,"%d",&n);
    fscanf(f,"%d",&elek);

    //El-lista
    Point* graph;
    graph = (Point*)malloc(n*sizeof(Point));

    if(graph == NULL){
        ERROR;
        exit(1);
    }
    for (int i = 1; i <= n; ++i) {
        graph[i].neigh = (int*)malloc((n+1)*sizeof(int));
        graph[i].degree = 0;
    }

    int a, b;
    for(int i=0;i<elek;i++){
        fscanf(f,"%d",&a);
        fscanf(f,"%d",&b);
        graph[a].neigh[graph[a].degree] = b;
        // Iranyitotatlannal szedd ki a commentet!
        //graph[b].neigh[graph[b].degree] = a;
        graph[a].degree++;
        //Iranyitatlannal szedd ki a commentet!
        //graph[b].degree++;
    }

    for(int i=1;i<=n;i++){
        graph[i].neigh=realloc(graph[i].neigh,graph[i].degree*sizeof(int));
    }

    for(int i=1;i<=n;i++){

            qsort(graph[i].neigh,graph[i].degree,sizeof(int),cmp);

    }

    printf("Szomszedsagi lista: \n");

    for(int i=1;i<=n;i++){
        printf("%d: ",i);
        for(int j=0;j<graph[i].degree;j++){
            printf("%d ",graph[i].neigh[j]);
        }
        printf("\n");
    }
    //Szomszedsagi Matrix
    int** matrix;
    matrix = (int**)malloc(n*sizeof(int*));

    if(!matrix){
        ERROR;
        exit(1);
    }

    for(int i=1;i<=n;i++){
        matrix[i] = (int*)calloc(n,sizeof(int));
        if(!matrix[i]){
            ERROR;
            exit(1);
        }
    }

    //zero(matrix,n);
    int y =5;
    for(int i=1;i<=n;i++){
        for(int j=0;j<graph[i].degree;j++){
                matrix[i][graph[i].neigh[j]] = 1;
        }
    }
    printf("\n");
    printf("Szomszedsagi Matrix: \n");
    int teljese = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(matrix[i][j]==0){
                teljese ++;
            }
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    if(teljese <= 4){
        printf("A matrix teljes!\n");
    } else {
        printf("A matrix nem teljes!\n");
    }

    for (int i = 1; i <= n; ++i) {
        free(graph[i].neigh);
    }

    for (int i = 1; i <= n; ++i) {
        free(matrix[i]);
    }
    free(matrix);
    free(graph);
    fclose(f);
    return 0;
}

void zero(int ** m,int n){

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            m[i][j] = 0;
        }
    }

}

int cmp(const void *a,  const void *b){

    int c = *(const int*)a;
    int d = *(const int *)b;

    if(c > d){
        return 1;
    } else if(c == d){
        return 0;
    }
    return -1;
}