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

void sub( char s1[] , char s2[] );

char A[100] , B[100] , a[100] , b[100] , ans[100] ; 

int main(){
	
	int i , j , k , judge = 0 , flag ;
	
	gets(A) ;
	gets(B) ;
	
	j = strlen(A) ;
	k = strlen(B) ;
	
	if(j >= k ){
		for( i = 0 ; A[i] != 0 ; i++ ){
			a[i] = A[i] ;
		}
		for( i = 0 ; i < j - k ; i++ ){
			b[i] = '0' ;
		}
		for( i = j - k ; i < j ; i++ ){
			b[i] = B[ i + k - j ] ;
		}
	}
	else{
		for( i = 0 ; B[i] != 0 ; i++ ){
			b[i] = B[i] ;
		}
		for( i = 0 ; i < k - j ; i++ ){
			a[i] = '0' ;
		}
		for( i = k - j ; i < k  ; i++ ){
			a[i] = A[ i + j - k ] ;
		}
	}
	
	flag = strcmp( a , b ) ;
	
	if( flag > 0 ){
		sub( a , b ) ;
		for( i = 0 ; ans[i] != 0 ; i++ ){
			if( ans[i] != '0' ){
				judge = 1 ;
			}
			if( judge == 1 ){
				printf("%c" , ans[i] ) ;
			}
		}
	}
	else if ( flag < 0 ){
		sub( b , a ) ;
		printf("-") ;
		for( i = 0 ; ans[i] != 0 ; i++ ){
			if( ans[i] != '0' ){
				judge = 1 ;
			}
			if( judge == 1 ){
				printf("%c" , ans[i] ) ;
			}
		}
	}
	else{
		printf("0") ;
		return 0 ;
	}
	
	return 0;
}

void sub( char s1[] , char s2[] ){
	int j ;
	j = strlen(s1) - 1 ;
	for( ; j >= 0 ; j-- ){
		if(!( s1[j] >= '0' && s1[j] <= '9' )){
			s1[j] += 10 ;
			s1[j-1]-- ;
		}
		if( s1[j] < s2[j] ) {
			ans[j] = '0' + s1[j] - s2[j] + 10 ;
			s1[j-1]-- ;
		}
		else{
			ans[j] = '0' + s1[j] - s2[j] ;
		}
	}
}
