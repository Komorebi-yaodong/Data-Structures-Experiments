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

int chess[20][20] ;
int p[3] = {0} ;

int line( int n , int x , int y ){
	int i , j , judge ;
	int a = 0 , b = 0 ;
	for( i = y , j = x , b = 0 ; chess[i][j] == n && j >=1 && j <= 19 ; j++ , b++ );//右加加// 
	if( b == 4 ){
		if(( chess[y][x-1] == 0 && x - 1>= 1 && x - 1 <= 19)||( chess[y][x + b] == 0 && x + b >= 1 && x + b <= 19 )){
			p[1] = x ;
			p[2] = y ;
			return n ;
		}
	}
	for( i = y , j = x , b = 0 ; chess[i][j] == n && i >=1 && i <= 19 ; i++ , b++ );//下加加 // 
	if( b == 4 ){
		if(( chess[y - 1][x] == 0 && y - 1 >= 1 && y - 1 <= 19)||( chess[y + b ][x] == 0 && y + b >= 1 && y + b <= 19 )){
			p[1] = x ;
			p[2] = y ;
			return n ;
		}
	}
	for( i = y , j = x , b = 0 ; chess[i][j] == n && i >=1 && i <= 19 ; i++ , j++ , b++ );//右下加加 // 
	if( b == 4 ){
		if(( chess[y - 1][x - 1] == 0 && y - 1 >= 1 && y - 1 <= 19 && x - 1  >= 1 && x - 1  <= 19) ||( chess[y + b ][x + b ] == 0 && y + b  >= 1 && y + b  <= 19 && x + b  >= 1 && x + b  <= 19)){
			p[1] = x ;
			p[2] = y ;
			return n ;
		}
	}
	for( i = y , j = x , b = 0 ; chess[i][j] == n && i >=1 && i <= 19 ; i++ , j-- , b++ );//左下加加// 
	if( b == 4 ){
		if(( chess[y - 1][x + 1] == 0 && y - 1 >= 1 && y - 1 <= 19 && x + 1 >= 1 && x + 1 <= 19)||( chess[y + b ][x - b ] == 0 && y + b  >= 1 && y + b  <= 19 && x - b  >= 1 && x - b  <= 19)){
			p[1] = x ;
			p[2] = y ;
			return n ;
		}
	}
	return 0 ;
}

int main(){
	
	int i , j , ans , judge ;
	for( i = 1 ; i <=19 ; i++ ){
		for( j = 1 ; j <= 19 ; j++ ){
			scanf("%d" , &chess[i][j]) ;
		}
	}
	
	for( i = 1 ; i <=19 ; i++ ){
		for( j = 1 ; j <= 19 ; j++ ){
			if( chess[i][j] != 0 ){
				ans = chess[i][j] ;
				judge = line( ans , j , i ) ;
				if( judge != 0 ){
					printf("%d:%d,%d" , judge , p[2] , p[1] ) ;
					return 0 ;
				}
			}
		}
	}
	
	if( 0 == judge ){
		printf("No") ;
	}
	
	return 0;
}
