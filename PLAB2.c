#include <stdio.h>
#include <stdlib.h>

#define N 512
float Mat[N][N], MatDD[N][N], V1[N], V2[N], V3[N], V4[N];

void InitData(){ 
int i,j; 
srand(334411); 
for( i = 0; i < N; i++ ) 
    for( j = 0; j < N; j++ ){ 
        Mat[i][j]=(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX)));  
        if ( (abs(i - j) <= 3) && (i != j)) 
            MatDD[i][j] = (((i*j)%3) ? -1 : 1)*(rand()/(1.0*RAND_MAX)); 
            else if ( i == j ) 
                MatDD[i][j]=(((i*j)%3)?-1:1)*(10000.0*(rand()/(1.0*RAND_MAX))); 
                else MatDD[i][j] = 0.0; 
    } 
for( i = 0; i < N; i++ ){ 
    V1[i]=(i<N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0; 
    V2[i]=(i>=N/2)?(((i*j)%3)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))):0.0; 
    V3[i]=(((i*j)%5)?-1:1)*(100.0*(rand()/(1.0*RAND_MAX))); 
    } 
}

void PrintVect( float vect[N], int from, int numel ) {
int i;
printf("Els valors del vector són: ");
// Mostrem un nombre 'numel' d'elements des de l'element 'from'
for (i = 0; i < numel; ++i) {
    printf("%.6f", vect[from + i]); // Imprimim els elements amb 6 decimals
    if(i < numel-1) {
            printf(", ");
        }
    }
    printf("\n"); // Nova línia al final
}

void PrintRow( float mat[N][N], int row, int from, int numel ) {
     // Verifiquem que els paràmetres siguin vàlids
    if (row < 0 || row >= N) {
        printf("Error: La fila indicada està fora de límits.\n");
        return;
    }
    
    if (from < 0 || from >= N) {
        printf("Error: La posició inicial està fora de límits.\n");
        return;
    }

    // Mostrem els elements de la fila començant des de 'from' fins a 'from + numel'
    printf("Els valors de la matriu són: ");
    for (int i = from; i < from + numel && i < N; i++) {
        printf("%.6f ", mat[row][i]);  // Imprimim els elements amb 6 decimals
    }
    
    printf("\n");  // Nova línia al final
}

void MultEscalar( float vect[N], float vectres[N], float alfa ) {
    // Multipliquem cada element de vect per alfa i ho emmagatzemem a vectres
    for (int i = 0; i < N; i++) {
        vectres[i] = alfa * vect[i];
    }
}


int main() {
InitData();
PrintVect(V1, 0, 10);
PrintVect(V1, 256, 10);
PrintRow(Mat, 0, 0, 10);
float vectres[N];
MultEscalar( V1, vectres, 2.0);
PrintVect(vectres, 0, 10);
}
