/*  mmsi.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define SIZE 180
#define FNAME "mmsi_list.txt"
char* file_name = "mmsi_list.txt";

typedef struct 
{
	FILE* fp;
	char** heap_arr;
	char lines[ SIZE ];
	char* fname;
	long f_length;
	int strings;
	int index;
} SDATA;

void file_open( SDATA* );
void mem_allocation( SDATA* );
void mem_reaper( SDATA* );
int search( SDATA* , char* );

int main( int argc, char* argv[] )
{
	SDATA sdat;
	//int index;
	
	sdat.fname = FNAME;
	
	if( argc < 2)
	{ 
		printf("Enter MMSI or NAME or CALLSIGN\n" );
		exit( 1 );
	}
	
	file_open( &sdat );
	mem_allocation( &sdat );
	//printf("argv[1] = %s\n", argv[1] );
	
	if( search( &sdat, argv[ 1 ] ) ) 
		printf( "   %s\n", sdat.heap_arr[ sdat.index ] );
	
	else		
		printf( "<%s> not found...\n" , argv[ 1 ] );
				
		mem_reaper( &sdat );
	
	return 0;
}

void file_open( SDATA* sdat )
{
	FILE* pfile;
	long f_siz;
	//int* index;
	
	//printf("Opening file %s\n", sdat->fname );
	
	if( (pfile = fopen( sdat->fname, "r")) == NULL )
	{
		fprintf(stderr, "Cant open file <%s>\n", sdat->fname );
		exit( -1 );
	} 
	//printf("The file %s has been opened!\n", sdat->fname );
	fseek( pfile, 0L, SEEK_END );
	f_siz = ftell( pfile );
	sdat->f_length = f_siz;
	rewind( pfile );
	/*
	printf( "The size of file %s is : %.3f Mbytes\n", sdat->fname, 
			(float)f_siz/1000/1000 );
	*/
	sdat->fp = pfile;
	
}

void mem_allocation( SDATA* hren )
{
	//const char;
	char** str_array = NULL;
	char line[ SIZE ];
	int strcount = 0;
//	int i = 0;
	
	while( (fgets( line, SIZE, hren->fp ) ) != NULL )
	{
		str_array = ( char** )realloc( str_array, ( strcount + 1 ) * sizeof( char* ) );
		str_array[ strcount++ ] = strdup( line );
	}	
	
	hren->heap_arr = str_array;
	hren->strings = strcount;
	
	//printf("strings = %d\n ", hren->strings );
	/*
	printf("The file is in the heap, press a key to print it\n");
	getchar();
	
	for( i = 0; i < strcount; i++ )
	printf( "%s" ,  str_array[ i ] );
	*/
}

void mem_reaper( SDATA* sd )
{
	int i;
	for( i = 0; i < sd->strings; i++ )
	free( sd->heap_arr[ i ] );
	
	free( sd->heap_arr );
}

int search( SDATA* sdat, char* arg )
{
	int indexx = sdat->index ;
	
	for( indexx = 0; indexx < sdat->strings; indexx++ )
	{
	
		if( strstr( sdat->heap_arr[ indexx ], arg) )
		{
			//if(1);
			sdat->index = indexx;
			return true;
			//exit( EXIT_SUCCESS );
		}
	}
	return false;
}




