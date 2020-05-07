// KalkulatorMacierzowy.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "matrix.h"
#define _DEBUG_
using namespace std;

void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );
void print( double* tab, int nDim );
int main(int argc, char** argv)
{
	if( argc != 2 ) {
		printf("Usage: %s <plik_we>",argv[0]);
		return -4;
	}
	FILE* fin;
	if( ( fin = fopen(argv[1], "r" ) ) == NULL ) {
		printf( "Couldn't find a %s file\n", argv[1] );
		return -3;
	}
	int nSize;
	fscanf( fin, "%d", &nSize );
	double** pTab = NULL;		// matrix NxN
	double* b = (double*)malloc( nSize * sizeof( double ) );
	if( !b || !CreateMatrix( &pTab, nSize ) )
	{
		perror( "ERROR: ALLOCATION(Main Matrix/bVector)" );
		return -1;
	}
	memset( b, 0, nSize * sizeof( double ) );
	ReadData( fin, pTab, b, nSize );
	fclose( fin );
#ifdef _DEBUG_
	printf( "======MATRIX CALCULATOR=====\n\n" );
	printf( "Matrix Size: %d\n", nSize );
	printf( "Matrix view: \n\n" );
	printMatrix( pTab, nSize );
	printf( "\nConstant Terms view:\n\n" );
	print( b, nSize );
	printf( "\n" );
#endif

	double Determinant = Det( pTab, nSize );
	if( Determinant < 1e-14 )
	{
		perror( "ERROR: The Determinant is equal to 0. Could not find solutions\n" );
		return -6;
	}
	double** inverse = NULL; //2d tab for inversed Matrix
	
	
		
	if( !CreateMatrix( &inverse, nSize ) )
	{
		perror("ERROR: ALLOCATION(inverseerted)");
		return -2;
	}
	InverseMatrix( inverse, pTab, nSize, Determinant );
	double* sol = (double*)malloc( nSize * sizeof( double ) );
	if( !sol )
	{
		perror("ERROR: ALLOCATION(Solutions Vector)");
		return -1;
	}
	memset( sol, 0, nSize * sizeof( double ) );
  //Set all vector values to 0
	LayoutEqu( inverse, b, sol, nSize ); //Find the solutions

#ifdef _DEBUG_
	printf( "\nDeterminant: %f\n", Determinant );
	printf( "\n inverse Matrix:\n\n" );
	printMatrix( inverse, nSize );
	printf( "\n" );
#endif 
	printf( "\nFound Solutions:\n" );
	print( sol, nSize );
	printf( "\n\n" );


	freeMatrix( &pTab, nSize );
	freeMatrix( &inverse, nSize );
	free( sol );
	free( b );
	return 0;
}
void ReadData( FILE* fin, double** pMatrix, double* b, int nDim )
{
	for( int i = 0; i < nDim; i++ )
	{
		double* p = *pMatrix++;
		for ( int j = 0; j < nDim; j++ )
			fscanf( fin, "%lf", p++ );
		fscanf( fin, "%lf", b++ );
	}
}
void print( double* tab, int nDim )
{
	for( int i = 0; i < nDim; i++ )
		printf( "%f ", *tab++ );
}