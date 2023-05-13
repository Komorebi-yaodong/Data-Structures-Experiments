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
int visited[100] , print[100] ;

void total_sort( int a[] , int k ) {
	int i ;

	if( k > n ) {
		for( i = 0 ; i < n ; i++ ) {
			printf("%d " , print[i] ) ;
		}
		puts("") ;
	} else {
		for( i = 0 ; i < n ; i++ ) {
			if( visited[a[i]] == 0 ) {
				print[k-1] = a[i] ;
				visited[a[i]] = 1 ;
				total_sort( a , k+1 ) ;
				visited[a[i]] = 0 ;
			}
		}
	}
}

int main() {

	int i , j , k ;
	int a[100] ;

	for( i = 0 ; i < 99 ; i++ ) {
		a[i] = i+1 ;
	}

	scanf("%d" , &n ) ;

	memset(visited,0,sizeof(visited)) ;

	total_sort( a , 1 ) ;

	return 0 ;

}
