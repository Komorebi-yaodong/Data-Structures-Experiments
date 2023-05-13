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

struct elect_king{
	int num ;
	struct elect_king *next ;
}; 

typedef struct elect_king king ;

int main(){
	
	king *head = NULL , *p = NULL , *pre = NULL , *node = NULL ;
	int n , m , q ;
	int i , k ;
	
	scanf("%d%d%d" , &n , &m , &q ) ; 
	
	head = (king*)(malloc(sizeof(king))) ;
	memset( head , 0 , sizeof(king) ) ;
	head->num = 0 ;
	head->next = NULL ;
	
	for( i = 1 ; i <= n ; i++ ){
		node = (king*)(malloc(sizeof(king))) ;
		memset( node , 0 , sizeof(king) ) ;
		node->num = i ;
		node->next = NULL ;
		if( NULL == head->next ){
			head->next = p = node ; 
		}
		else{
			p->next = node ;
			p = p->next ;
		}
	} 
	p->next = (head->next) ;
	
	p = head ;
	for( i = 0 ; i <= q - 1 ; i++ , p = p->next ) ;
	while( p->next != p ){
		if( 1 == m ){
			pre = p ;
			while( p->next != pre ){
				p = p->next ;
			}
			printf("%d" , p->num ) ;
			return 0 ;
		}
		else{
			for( i = 1 ; i < m - 1 ; i++ , p = p->next ) ;
			pre = p->next ;
			p->next = pre->next ;
			free(pre) ; 
			p = p->next ;
		}
	}
	printf("%d" , p->num ) ;
	return 0 ;
}
