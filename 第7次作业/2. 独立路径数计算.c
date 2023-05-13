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

struct EDGE {
	int No ;
	int adjvex ;
	struct EDGE *next ;
};

struct VER {
	struct EDGE *link ;
};

typedef struct EDGE Edge ;
typedef struct VER Ver ;

Ver map[MAXSIZE] ;
int path[MAXSIZE] ;
int visited[MAXSIZE] ;
int tail = -1 ;
int n , e ;

void create( int e_number , int v1 , int v2 ) {
	Edge *point , *p ;
	point = (Edge*)(malloc(sizeof(Edge))) ;
	point->No = e_number ;
	point->adjvex = v2 ;
	point->next = NULL ;
	p = map[v1].link ;
	if( p == NULL ) {
		map[v1].link = point ;
	} else {
		while( p->next != NULL ) {
			p = p->next ;
		}
		p->next = point ;
	}
}

void DFS_side( int point ) {
	int i ;
	Edge *q ;
+
	q = map[point].link ;
	while( q != NULL && point != n-1 ) {
		if( visited[q->adjvex] == 0 ) {
			path[++tail] = q->No ;
			visited[q->adjvex] = 1 ;
			DFS_side( q->adjvex ) ;
		}
		q = q->next ;
	}
	if( point == n-1 ) {
		for( i = 0 ; i <= tail ; i++ ) {
			printf("%d " , path[i]) ;
		}
		puts("") ;
	}
	visited[point] = 0 ;
	tail-- ;
}

int main() {

	Edge *p ;
	int i , j , k ;
	int e_no , v1 , v2 ;

	scanf("%d%d" , &n , &e ) ;

	for( i = 0 ; i < e ; i++ ) {
		scanf("%d%d%d" , &e_no , &v1 , &v2 ) ;
		create( e_no , v1 , v2) ;
		create( e_no , v2 , v1 ) ;
	}
	visited[0] = 1 ;
	DFS_side( 0 ) ;

	return 0;
}
