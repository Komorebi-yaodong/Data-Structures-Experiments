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

int n ;
int monkey[500] ;

int check(){//0 == n 
	int i ;
	int num = 0 ;
	for( i = 1 ; i <= n ; i++ ){
		if( monkey[i] == 0 ){
			num++ ;
		}
	}
	return num ;
}

int main(){

    int i , j , k ;
    int start , judge ;
    int count = 0 ;

	scanf("%d%d%d" , &n , &judge , &start ) ;
	
    memset(monkey,0,sizeof(monkey));
    
	for( i = start-1 , count == 0 ; check() != 1 ; i++ ){
		
		if( monkey[i%n+1] == 0 ){
			count++ ;
			if( count == judge ){
				monkey[i%n+1] = 1 ;
				printf("%d " , i%n+1 ) ;
				count = 0 ;
			}
		}
	}
	
	for( i = 1 ; i <= n ; i++ ){
		if( monkey[i%n+1] == 0 ){
			printf("\n%d" , i+1 ) ;
			break ;
		}
	}
	
	return 0;
}

