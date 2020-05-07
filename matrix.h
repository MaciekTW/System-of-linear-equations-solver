#ifndef MATRIX_D123
#define MATRIX_D435

int CreateMatrix( double*** pTab, int nSize ); // kreowanie macierzy
void freeMatrix( double*** pMatrix, int nDim ); //delete the Matrix
void printMatrix( double** pMatrix, int nDim );
void InverseMatrix( double** pInv, double** pTab, int nSize, double det );
double Det( double** pTab, int nSize ); //rozwiniecie wzgl 0-go wiersza 
void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize );
void TransMatrix( double** pTab, int nDim );
#endif
