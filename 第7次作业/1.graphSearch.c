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

int visited[102]; 
int map[102][102] ;
int pop[100000] ;
int head = 0 , tail = -1 ;
int delet_node ;

void clearing( int n ){//清除访问路径 
	int i = 0 ;
	for( i = 0 ; i < n ; i++ ){
		visited[i] = 0 ;
	}
}

void visit_deep( int point , int n ){//深度优先 
	int i ;
	printf("%d " , point ) ;
	visited[point] = 1 ;
	for( i = 0 ; i < n ; i++ ){
		if( map[point][i] != 0 && visited[i] != 1 ){
			visit_deep( i , n ) ;
		}
	}
}

void BFS( int point , int n ){
	int i ;
	int temp ;
	pop[++tail] = point ;
	visited[point] = 1 ;
	while( tail - head > -1 ){
		temp = pop[head] ;
		printf("%d " , pop[head++] ) ;
		for( i = 0 ; i < n ; i++ ){
			if( map[temp][i] != 0 && visited[i] == 0 ){
				pop[++tail] = i ;
				visited[i] = 1 ;
			}
		}
	}
}

void visit_wide( int n ){//广度优先（使用了BFS） 
	int i ;
	head = 0 ;
	tail = -1 ;
	for( i = 0 ; i < n ; i++ ){
		if( visited[i] == 0 ){
			BFS( i , n ) ;
		}
	}
}

int main(){

    int i ;
	int n_point , n_side ;
	int side1 , side2 ;
	
	scanf("%d%d" , &n_point , &n_side ) ;
	
	for( i = 0 ; i < n_side ; i++ ){
		
		scanf("%d%d" , &side1 , &side2 ) ;
		map[side1][side2] = 1 ;
		map[side2][side1] = 1 ;
		
	} 
	scanf("%d" , &delet_node ) ;
	
	clearing( n_point ) ;
	visit_deep( 0 , n_point ) ;
	puts(""); 
	
	clearing( n_point ) ;
	visit_wide( n_point ) ;
	puts("") ;
/*	
	for( i = 0 ; i < n_point ; i++ ){
		map[delet_node][i] = 0 ;
		map[i][delet_node] = 0 ;
	}
*/	
	clearing( n_point ) ;
	visited[delet_node] = 1 ;
	visit_deep( 0 , n_point ) ;
	puts("") ;
	
	clearing( n_point ) ;
	visited[delet_node] = 1 ; 
	visit_wide( n_point ) ;
	
	return 0;
}
