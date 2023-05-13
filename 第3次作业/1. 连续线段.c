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

struct site{
	int x1 ;
	int y1 ;
	int x2 ;
	int y2 ;
};

int main(){
	
	struct site a[102] ;
	int i , j ,  count , flag ;
	int n ;
	int mark[102][4] ;
	int x_2 , y_2 ;
	
	scanf("%d" , &n ) ;
	
	for( i = 0 ; i < n ; i++ ){/*存入数据*/ 
		scanf("%d %d %d %d" , &a[i].x1 , &a[i].y1 , &a[i].x2 , &a[i].y2 ) ;
	}
	
	for( i = 0 ; i < n ; i++ ){/*遍历向右连接（不管左侧）*/ 
		mark[i][1] = a[i].x1 ;
		mark[i][2] = a[i].y1 ;
		x_2 = a[i].x2 ;
		y_2 = a[i].y2 ;
		for( j = 0 , count = 1 ; j < n ; j++ ){
			if( x_2 == a[j].x1 && y_2 == a[j].y1 ){
				count++ ;
				x_2 = a[j].x2 ;
				y_2 = a[j].y2 ;
				j = -1 ;
			}
		}
		mark[i][0] = count ;
	}
	
	for( flag = 0 , i = 0 ; i < n ; i++ ){/*找最大项*/ 
		if( mark[i][0] > mark[flag][0] ){
			flag = i ;
		}
	}

	printf("%d %d %d" , mark[flag][0] , mark[flag][1] , mark[flag][2] ) ;/*输出*/ 
	
	return 0;
}
