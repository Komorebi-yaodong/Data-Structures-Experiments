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

char ans[200][20] ;
char str[20] ;
int link = 0 ;

void integrate_sort( int k , int n , int a[] ){
	int i , tem ;
	if( k == n - 1 ){
		link++ ;
		for( i = 0 ; i < n ; i++ ){
			ans[link][i] = a[i] + '0' ;
		}
		
		ans[link][n] = 0 ;
	}
	else{
		for( i = k ; i< n ; i++ ){
			tem = a[k] ;
			a[k] = a[i] ;
			a[i] = tem ;
			integrate_sort( k + 1 , n , a ) ;
			tem = a[k] ;
			a[k] = a[i] ;
			a[i] = tem ;
		}
	}
}

int number( int n ){
	int i , num ;
	for( i = 1 , num = 1 ; i <= n ; i++ ){
		num *= i ;
	}
	return num ;
}

int main(){
	
	int a[20] , n ;
	int i , j , k , tem ;
	int judge ;
	scanf("%d" , &n ) ;
	for( i = 0 ; i < n ; i++ ){
		a[i] = i + 1 ;
	}
	integrate_sort( 0 , n , a ) ;
	
	k = number(n) ;
	
	for( i = 1 ; i <= k ; i++ ){
		for( j = 1 , tem = 1 ; j <= k - i + 1 ; j++ ){
			judge = strcmp( ans[tem] , ans[j] ) ;
			if( judge < 0 ){
				tem = j ;
			}
		}
		strcpy( str , ans[k - i + 1] ) ;
		str[n] = 0 ;
		strcpy( ans[k - i + 1] , ans[tem] ) ;
		ans[k - i + 1][n] = 0 ;
		strcpy( ans[tem] , str ) ;
		ans[tem][n] = 0 ;
	}
	
	for( i = 1 ; i <= k ; i++ ){
		for( j = 0 ; j < n ; j++ ){
			printf("%c" , ans[i][j]) ;
			if( j < n - 1 ){
				printf(" ") ;
			}
			else if( j == n - 1 ){
				puts("") ;
			}
		}
	}

	return 0;
}
