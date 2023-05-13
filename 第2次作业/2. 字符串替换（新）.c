#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define Pi 3.1415926535
#define eps 1e-8
#define ULL unsigned long long
#define LL long long
#define MAXLINE 1024

char a[MAXLINE] , b[MAXLINE] , check[MAXLINE] , again[MAXLINE] ; 

int main(){
	
	int i , j , k , length_a , length_b ;
	char c ;
	FILE *in , *out ;
	
	in = fopen("filein.txt" , "r") ;
	out = fopen("fileout.txt" , "w") ;
	
	scanf("%s%s" , a , b ) ;
	
	length_a = strlen(a) ;
	length_b = strlen(b) ;
	
	while( (c = fgetc(in)) != EOF ){
		if( tolower(c) != tolower(a[0]) ){
			fputc( c , out ) ;
		}
		else{
			for( i = 1 ; i < length_a ; i++ ){
				again[i] = fgetc(in) ;
				if( tolower(again[i]) != tolower(a[i]) ){
					break ;
				}
			}
			if( i == length_a ){
				for( j = 0 ; j < length_b ; j++ ){
					fputc( b[j] , out ) ;
				}

			}
			else{
				fputc( c , out ) ;
				for( j = 1 ; j <= i ; j++ ){
					fputc( again[j] , out ) ;
				}
			}
		}
	}
	
	fclose(in) ;
	fclose(out) ;
	
	return 0;
}
