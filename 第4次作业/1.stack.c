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

int stack[101] ;

int main(){
	
	int ope = 1 , elem , top = -1 ;
	int i , j , k ;
	
	while( ope != -1 ){
		scanf("%d" , &ope ) ;
		if( 1 == ope ){
			scanf("%d" , &elem ) ;
			stack[++top] = elem ;
		}
		else if( 0 == ope ){
			if( -1 == top ){
				printf("error ") ;
			}
			else{
				printf("%d " , stack[top--] ) ;
			}
		}
	}
	
	return 0 ; 
}
