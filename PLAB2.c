#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

float Scalar( float vect1[N], float vect2[N] ) {
    float scalar = 0.0; 
    // Multipliquem cada element de vect1 per l'element corresponent de vect2 i ho emmagatzemem a scalar
    for (int i = 0; i < N; i++) {
        scalar += vect1[i] * vect2[i];
    }
    return scalar;
}

float Magnitude( float vect[N] ) {
    int i;
    int sumatori = 0;
    for ( i = 0; i < N; ++i) {
        sumatori += pow(vect[i],2);
    }
    float Magnitude = sqrt(sumatori);
    return Magnitude;
}

int Ortogonal( float vect1[N], float vect2[N] ) {
    float suma = 0.0;
// Calculem la suma dels productes dels vectors
    for (int i = 0; i < N; i++) {
        suma += vect1[i] * vect2[i];
    }
// Si el total de la suma és zero, la funció retorna 1, si no retorna 0
    if (suma == 0) {
        return 1;
    } else {
        return 0;
    }
}

void  Projection( float vect1[N], float vect2[N], float vectres[N] ) {
    float Scal_u_v = Scalar(vect1, vect2);
    float Magnitude_v = Magnitude(vect2);
    float Div_Scal_Magnitude = Scal_u_v / Magnitude_v;
    for (int i = 0; i < N; i++) {
        vectres[i] = Div_Scal_Magnitude * vect2[i];
    }
}

float Infininorm( float M[N][N] ) {
    float sumatori_max = 0.0;
    for (int i = 0; i < N; i++) {
        float sumatori = 0.0;
        for (int j = 0; j < N; j++) {
            sumatori += fabs(M[i][j]);
        }
        if (sumatori > sumatori_max) {
            sumatori_max = sumatori;
        }
    }
    return sumatori_max;
}

float Onenorm(float M[N][N]) {
    float max_sum = 0.0;  // Emmagatzema la màxima suma de les columnes
    // Recorrem cada columna
    for (int columna = 0; columna < N; columna++) {
        float columna_sum = 0.0;  // Inicialitzem la suma de la columna actual a 0

        // Sumar els valors absoluts de cada element de la columna
        for (int fila = 0; fila < N; fila++) {
            float valor = M[fila][columna];
            // Obtenim el valor absolut
            if (valor < 0) {
                valor = -valor;
            }
            columna_sum += valor;
        }
        // Actualitzem el màxim si la suma de la columna actual és més gran
        if (columna_sum > max_sum) {
            max_sum = columna_sum;
        }
    }
    return max_sum;  // Retornem la norma-ú de la matriu
}

float FrobeniusNorm(float M[N][N]) {
    float sum = 0.0;
    // Suma dels quadrats dels elements
    for (int fila = 0; fila < N; fila++) {
        for (int columna = 0; columna < N; columna++) {
            sum += M[fila][columna] * M[fila][columna];
        }
    }

    // Retornem l'arrel quadrada de la suma
    return sqrt(sum);
}

int DiagonalDom(float M[N][N]) {
    for (int fila = 0; fila < N; fila++) {
        float suma = 0.0;
        // Suma dels valors absoluts dels elements fora de la diagonal de la fila actual
        for (int columna = 0; columna < N; columna++) {
            if (columna != fila) {
                float valor = M[fila][columna];
                // Obtenim el valor absolut
                if (valor < 0) {
                    valor = -valor;  
                }
                suma += valor; //Sumem els valors
            }
        }
        float element_diagonal = M[fila][fila];
        // Valor absolut de l'element de la diagonal de la fila actual
        if (element_diagonal < 0) {
            element_diagonal = -element_diagonal;
        }
        // Comprovem si l'element de la diagonal és més gran o igual que la suma
        if (element_diagonal < suma) {
            return 0;  // No és diagonalment dominant
        }
    }
    return 1;  // L’element de la diagonal és més gran o igual que la suma dels valors absoluts dels altres elements de la fila, per a totes les files de la matriu. La matriu és diagonalment dominant
}

void Matriu_x_Vector( float M[N][N], float vect[N], float vectres[N] ) {
    for (int fila = 0; fila < N; fila++) {
        vectres[fila] = 0; //Inicialitzem els valors de la matriu
        //Calculem el punt de la fila de la matriu pel vector
        for (int columna = 0; columna < N; columna++) {
            vectres[fila] += M[fila][columna] * vect[columna] ; 
        }
    }
}

int Jacobi(float M[N][N], float vect[N], float vectres[N], unsigned iter) {
    // Comprovem si la matriu és diagonal dominant i si no ho és retornem 0
    if (!DiagonalDom(M)) {
        return 0;
    }


    // Establim el llindar que ha de complir la diferència entre dues solucions consecutives per a què el programa deixi d'iterar
    #define llindar 1e-6
    float sum;
    float new_vectres[N]; // Vector temporal per a guardar els nous valors
    // Inicialitzem vectres amb els valors inicials
    for (unsigned i = 0; i < N; i++) {
        vectres[i] = 0.0;
    }


    for (unsigned i = 0; i < iter; i++) {
        int convergencia = 1;
        
        for (unsigned j = 0; j < N; j++) {
            sum = 0.0;
            for (unsigned k = 0; k < N; k++) {
                if (j != k) {
                    sum += M[j][k] * vectres[k];
                }
            }
            float valor = (vect[j] - sum) / M[j][j];
            new_vectres[j] = valor;

            // Verifiquem la convergència comparant la diferència absoluta
            if ((valor - vectres[j] > llindar) || (vectres[j] - valor > llindar)) {
                convergencia = 0;
            }
        }

        // Actualitzem els valors de vectres amb els nous valors
        for (unsigned j = 0; j < N; j++) {
            vectres[j] = new_vectres[j];
        }

        // Si ha convergit, retornem 1 i finalitzem
        if (convergencia == 1) {
            return 1;
        }
    }
}

//Definim la funció 'precisió'. Volem calcular la precisió amb què x compleix la premissa Ax = B, per tant, la funció agafarà com a paràmetres la matriu A, el vector aproximació X (resultat de la funció Jacobi) i el vector B.
float precisió(float matA[N][N], float vectX[N], float vectB[N]){
    float vect_aprox_B[N];
    Matriu_x_Vector(matA,vectX, vect_aprox_B);
    float vect_diferencia[N];
    for (int i = 0; i < N; i++){
        vect_diferencia[i] = abs(vectB[i] - vect_aprox_B[i]);
    }
    float Magnitut_diferencia = Magnitude(vect_diferencia);
    return Magnitut_diferencia;
}

int main() {
InitData(); //Cridem la funció InitData per obtindre els vectors i les matrius

printf("A. \n");
printf("Els elements 0 al 9 de V1: \n");
PrintVect(V1, 0, 10);
printf("Els elements 256 al 265 de V1: \n");
PrintVect(V1, 256, 10);
printf("Els elements 0 al 9 de V2: \n");
PrintVect(V2, 0, 10);
printf("Els elements 256 al 265 de V2: \n");
PrintVect(V2, 256, 10);
printf("Els elements 0 al 9 de V3: \n");
PrintVect(V3, 0, 10);
printf("Els elements 256 al 265 de V3: \n");
PrintVect(V3, 256, 10);

printf("\nB. \n");
printf("Els elements 0 al 9 de la fila 0 de Mat: \n");
PrintRow(Mat, 0, 0, 10);
printf("Els elements 0 al 9 de la fila 0 de Mat: \n");
PrintRow(Mat, 100, 0, 10);

printf("\nC. Els elements 0 al 9 de la fila 0 i 90 a 99 de la fila 100 de la matriu MatDD. \n");
printf("Els elements 0 al 9 de la fila 0 de MatDD: \n");
PrintRow(MatDD, 0, 0, 10);
printf("Els elements 90 al 99 de la fila 100 de Mat: \n");
PrintRow(MatDD, 100, 90, 10);

printf("\nD. \n");
printf("Mat: \n");
float InfiMAT = Infininorm(Mat);
printf("La infini-norma de la matriu Mat és: %.6f\n", InfiMAT);

float norma_u1 = Onenorm( Mat );
printf("La norma-u de la matriu Mat és: %.3f \n", norma_u1);

float norma_Frobenius1 = FrobeniusNorm( Mat );
printf("La norma de Frobenius de la matriu Mat és: %.3f \n", norma_Frobenius1);

int diagonalment_dominant1 = DiagonalDom( Mat );
if (diagonalment_dominant1 == 0) {
    printf("La matriu Mat no és diagonal dominant \n");
}
else{
    printf("La matriu Mat és diagonal dominant \n");
}

printf("MatDD: \n");
float InfiMATDD = Infininorm(MatDD);
printf("La infini-norma de la matriu MatDD és: %.6f\n", InfiMATDD);

float norma_u2 = Onenorm( MatDD );
printf("La norma-u de la matriu MatDD és: %.3f \n", norma_u2);

float norma_Frobenius2 = FrobeniusNorm( MatDD );
printf("La norma de Frobenius de la matriu MatDD és: %.3f \n", norma_Frobenius2);

int diagonalment_dominant2 = DiagonalDom( MatDD );
if (diagonalment_dominant2 == 0) {
    printf("La matriu MatDD no és diagonal dominant \n");
}
else{
    printf("La matriu MatDD és diagonal dominant \n");
}

printf("\nE. \n");
float scalar1 = Scalar( V1, V2 );
printf("Escalar <V1,V2> = ");
printf("%.6f ", scalar1);
printf("\n"); 

float scalar2 = Scalar( V1, V3 );
printf("Escalar <V1,V3> = ");
printf("%.6f ", scalar2);
printf("\n");  

float scalar3 = Scalar( V2, V3 );
printf("Escalar <V2,V3> = ");
printf("%.6f ", scalar3);
printf("\n");  

printf("\nF. \n");
float Mag1 = Magnitude(V1);
float Mag2 = Magnitude(V2);
float Mag3 = Magnitude(V3);
printf("La magnitud de V1 és %.6f\n", Mag1);
printf("La magnitud de V2 és %.6f\n", Mag2);
printf("La magnitud de V3 és %.6f\n", Mag3);

printf("\nG. \n");
int ortV1V2 = Ortogonal(V1, V2);
if (ortV1V2 == 0) {
    printf("V1 i V2 no són ortogonals \n");
}
else{
    printf("V1 i V2 són ortogonals\n");
}
int ortV1V3 = Ortogonal(V1, V3);
if (ortV1V3 == 0) {
    printf("V1 i V3 no són ortogonals \n");
}
else{
    printf("V1 i V3 són ortogonals\n");
}
int ortV2V3 = Ortogonal(V2, V3);
if (ortV2V3 == 0) {
    printf("V2 i V3 no són ortogonals \n");
}
else{
    printf("V2 i V3 són ortogonals\n");
}

printf("\nH. \n");
float vectres[N];
MultEscalar( V3, vectres, 2.0);
printf("Elements 0 al 9 de la multiplicació del vector V3 amb l’escalar 2.0: \n");
PrintVect(vectres, 0, 10);
printf("Elements 256 al 265 de la multiplicació del vector V3 amb l’escalar 2.0: \n");
PrintVect(vectres, 256, 10);

printf("\nI. \n");
float proj_v2_v3[N];
Projection(V2, V3, proj_v2_v3);
printf("10 primers elements de la projecció de V2 sobre V3: \n");
PrintVect(proj_v2_v3, 0, 10);

float proj_v1_v2[N];
Projection(V1, V2, proj_v1_v2);
printf("10 primers elements de la projecció de V1 sobre V2: \n");
PrintVect(proj_v1_v2, 0, 9);

printf("\nJ. \n");
Matriu_x_Vector( Mat, V2, vectres );
printf("10 primers elements de la la multiplicació de la matriu Mat amb el vector v2: \n");
PrintVect(vectres, 0, 10);

printf("\nK. \n");
printf("Solució del sistema d’equacions MatDD*X = V3: \n");
unsigned iter1 = 1;
int res1 = Jacobi(MatDD, V3, vectres, iter1);
if (res1 == 1) {
    printf("Amb 1 iteració: \n");
    PrintVect(vectres, 0, 10);
}
else {
    printf("La matriu MatDD no és diagonal dominant, no es pot aplicar Jacobi");
}
unsigned iter1000 = 1000;
int res2 = Jacobi(MatDD, V3, vectres, iter1000);
if (res2 == 1) {
    printf("Amb 1000 iteracions: \n");
    PrintVect(vectres, 0, 10);
}
else {
    printf("La matriu MatDD no és diagonal dominant, no es pot aplicar Jacobi");
}
int res3 = Jacobi(Mat, V3, vectres, iter1);
if (res3 == 1) {
    printf("Amb 1 iteració: \n");
    PrintVect(vectres, 0, 10);
}
else {
    printf("La matriu Mat no és diagonal dominant, no es pot aplicar Jacobi \n");
}

printf("\nPunt Extra: \n");
float vectres_jacobi1[N];
Jacobi(MatDD, V3, vectres_jacobi1, 1);
printf("El vector X que cumpleix MatDD * X = V3 (després de una iteració) és aproximadament: ");
PrintVect(vectres_jacobi1, 0, 10);
float vectres_jacobi2[N];
Jacobi(MatDD, V3, vectres_jacobi2, 1000);
printf("El vector X que cumpleix MatDD * X = V3 (després de 1000 iteracións) és aproximadament: ");
PrintVect(vectres_jacobi2, 0, 10);

float precisió_x_1_iteració = precisió(MatDD, vectres_jacobi1, V3);
printf("La precisió de X després d'una iteració és %.10f\n",precisió_x_1_iteració);
float precisió_x_1000_iteracions = precisió(MatDD, vectres_jacobi2, V3);
printf("La precisió de X després de 1000 iteracions és %.10f\n",precisió_x_1000_iteracions);

}
