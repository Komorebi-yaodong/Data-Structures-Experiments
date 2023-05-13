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
#define MAXSIZE 512

struct EDGE{
	int No ;
	int weight ;
	int adjvex ;
	struct EDGE *next ;
};

struct VER{
	struct EDGE *link ;
};

typedef struct EDGE Edge ;
typedef struct VER Ver ;

Ver map[MAXSIZE] ;
int visited[MAXSIZE] ;
int side[MAXSIZE] ;
int n , e , total_weight = 0 ;
int plug = -1 ;
int tail = -1 ;

void create( int e_number , int weigh , int v1 , int v2 ){
	Edge *point , *p ;
	point = (Edge*)(malloc(sizeof(Edge))) ;
	point->No = e_number ;
	point->adjvex = v2 ;
	point->weight = weigh ;
	point->next = NULL ;
	p = map[v1].link ;
	if( p == NULL ){
		map[v1].link = point ;
	}
	else{
		while( p->next != NULL ){
			p = p->next ;
		}
		p->next = point ;
	}
}

int find( int p ){
	int i ;
	for( i = 0 ; i <= tail ; i++ ){
		if( p == visited[i] ){
			return 1 ;
		}
	}
	return 0 ;
}

void tree( int point ){
	int i = 0 ;
	Edge *p , *min ;
	
	for( i = 0 ; i < n ; i++ ){
		visited[i] = -1 ;
	}
	
	visited[++tail] = point ;
	while( tail < n-1 ){
		min = (Edge*)(malloc(sizeof(Edge))) ;
		min->weight = 500000 ;
		for( i = 0 ; i <= tail ; i++ ){
			p = map[visited[i]].link ;
			while( p != NULL ){
				if(  find(p->adjvex) == 0 ){
					if( p->weight <= min->weight ){
						min = p ;
					}
				}
				p = p->next ;
			}
		}
		visited[++tail] = min->adjvex ;
		total_weight += min->weight ;
		side[++plug] = min->No ;
	}
}

void select_sort(){
	int i , j ;
	int min , temp ;;
	for( i = 0 ; i <= plug ; i++ ){
		for( j = i , min = i ; j <= plug ; j++ ){
			if( side[min] > side[j] ){
				min = j ;
			}
		}
		temp = side[i] ;
		side[i] = side[min] ;
		side[min] = temp ;
	}
}

int main(){
	
    int i ;
    int id , v1 , v2 , weigh ;
    Edge *p ;
    
    scanf("%d%d" , &n , &e ) ;
    
    for( i = 0 ; i < e ; i++ ){
    	scanf("%d%d%d%d" , &id , &v1 , &v2 , &weigh ) ;
    	create( id , weigh , v1 , v2 ) ;
    	create( id , weigh , v2 , v1 ) ;
	}
		
	tree( 0 ) ;
	
	printf("%d\n" , total_weight ) ;
	
	select_sort() ;
	
	for( i = 0 ; i <= plug ; i++ ){
		printf("%d " , side[i] ) ;
	}
	
	return 0;
}
