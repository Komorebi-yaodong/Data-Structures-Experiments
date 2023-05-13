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

int line[1000000] ;

int main() {
	int front = 0 , rear = 0 , n , length , num , windows = 3 ;
	int i , j , k , constant_windows ;

	scanf("%d" , &n ) ;

	for( i = 1 ; i <= n ; i++ ) {
		scanf("%d" , &num ) ;
		for( j = 1 ; j <= num ; j++ ) { //入队
			rear++ ;
		}
		length = rear - front ;
		if( length < 21 ) {
			windows = 3 ;
		} else if( length >= 21 && length < 28 ) {
			windows = 4 ;
		} else if( length > 28 ) {
			windows = 5 ;
		}
		for( j = 1 ; j <= windows && front < rear ; j++ , front++ ) { //出队
			printf("%d : %d\n" , front+1 , line[front+1] ) ;
		}
		if( front < rear ) {
			for( k = front + 1 ; k <= rear ; k++ ) {
				line[k]++ ;
			}
		}
	}
	constant_windows = windows ;
	while( front < rear ) {
		length = rear - front ;
		if( length >= 28 && length < 35 ) {
			constant_windows = 4 ;
		}
		if( length < 28 ) {
			constant_windows = 3 ;
		}
		for( j = 1 ; j <= constant_windows && front < rear ; j++ , front++ ) { //出队
			printf("%d : %d\n" , front+1 , line[front+1] ) ;
		}
		if( front < rear ) {
			for( k = front + 1 ; k <= rear ; k++ ) {
				line[k]++ ;
			}
		}
	}

	return 0;
}
