#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <float.h>

using namespace std;

void complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void complMatrix( double** pTabD, double** pTab, int nDim );


int CreateMatrix( double*** pTab, int nSize ) //Matrix allocating
{
    *pTab = (double**)malloc( nSize * sizeof(double*) );
    if( !pTab )
        return 0;
    memset( *pTab, 0, nSize * sizeof( double* ) );
    double** p = *pTab;
    for( int i = 0; i < nSize; i++, p++ ) {
        *p = (double*)malloc( nSize * sizeof( double ) ); //col allocate
        if( !*pTab )
            return 0;
        memset( *p, 0, nSize * sizeof( double ) );   //setting values to 0
    }
    return 1;
}
void freeMatrix( double*** pMatrix, int nDim )
{
    double** v = *pMatrix;
    for( int i = 0; i < nDim; i++ )
        free( *v++ );
    free( *pMatrix );
    *pMatrix = NULL;
}
void printMatrix( double** pMatrix, int nDim ) //print the matrix using standard exit with precission to 2 elements after point
{
        for( int i = 0; i < nDim; i++ ) 
        {
            double* ptr = *pMatrix++;
            for( int j = 0; j < nDim; j++ )
                printf( "%.2f ", *ptr++ );
            printf( "\n" );
        }
}
void complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )
{

    for( int i = 0; i < nDim; i++, pTabI++ )
    {
        if( i == nRow )
            continue;
        double* pO = *pTabO++;
        double* pT = *pTabI;
        for(int j = 0; j < nDim; j++, pT++) 
        {
            if( j == nCol )
                continue;
            *pO++ = *pT;
        }
    }
}
double Det( double** pTab, int nSize ) //recursion function
{
 
    if( nSize == 1 ) //if size of a Matrix equals to 1, the determinant is equal to the value of the only element
        return **pTab;
    if( nSize == 2 ) //if the size is two, we can use a well known formula to calculate it
        return **pTab * pTab[1][1] - pTab[0][1] * pTab[1][0];
     //otherwise we have to reduce the size of our Matrix (Using a recursion)
    double** temp = NULL; //A minor of our main Matrix

    if( !CreateMatrix( &temp, nSize - 1 ) )
    {
        perror( "ALLOCATION ERROR\n" );
        return DBL_MIN;
    }
    double sign = 1;
    double* ptr = *pTab;
    double det = 0;
     for( int i = 0; i<nSize; i++ )
     {
        complement( temp, pTab, 0, i, nSize ); //Complement to row with 0 index 
        det += sign * (*ptr++) * Det(temp, nSize - 1);
        sign = -sign; //we have to consider a sign
     }
     freeMatrix( &temp,nSize-1 );
    return det;
}
void TransMatrix( double** pTab, int nDim ) 
{
    double** ptr2 = pTab;
    for( int i = 0; i < nDim - 1; i++ ) 
    {
        double* ptr = *ptr2++ + i + 1;
        for( int j = i + 1; j < nDim; j++ )
        {
            double temp = *ptr;
            *ptr++ = pTab[j][i];
            pTab[j][i] = temp;
        }
    }
}
void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize )
{
    for( int i = 0; i < nSize; i++ )
    {
        double* p = pB;
        double* t = *pInv++;
        for( int j = 0; j < nSize; j++ )
        {
            *pRes += *t++ * *p++;
        }
        pRes++;
    }
}
void complMatrix( double** pTabD, double** pTab, int nDim )
{

    double** temp = NULL;
   if( !CreateMatrix(&temp, nDim - 1) )
    {
        perror( "ALLOCATION ERROR\n" );
        return;
    }
    for( int i = 0; i < nDim; i++ ) 
    {
        double* ptr = *pTabD++;
        double sign = (i%2) ? -1 : 1;

        for( int j = 0; j < nDim; j++ ) 
        {
            complement( temp, pTab, i, j, nDim );

            *ptr++ = sign * Det( temp, nDim - 1 );
            sign = -sign;
        }
    }
    freeMatrix( &temp, nDim - 1 );
}
void InverseMatrix( double** pInv, double** pTab, int nSize, double det )
{
    TransMatrix( pTab, nSize );
    complMatrix( pInv, pTab, nSize ); // Create Complement matrix
    for( int i = 0; i < nSize; i++ ) {
        double* v = *pInv++;
        for( int nCol = 0; nCol < nSize; nCol++, v++ )
        {
            *v /= det;
        }
    }
}
