#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

void insert( char s[] , char add[] , int n ) ;
void del( char s[] , int length , int n ) ;

struct porcess{
	int operation ;
	int location ;
	char string[513] ;
	struct porcess *rlink ;
	struct porcess *llink ; 
};

typedef struct porcess process ;

int main(){
	process *head , *node , *p , *q ;
	int i , j , k , length ;
	int n , ope , loc ;
	char passage[513] , str[513] ;
	
	gets(passage) ;
	scanf("%d" , &n ) ;
	
	head = (process*)(malloc(sizeof(process))) ;
	head->llink = NULL ;
	head->rlink = NULL ;
	head->operation = 0 ;
	head->location = 0 ;
	head->string[0] = '\0' ;
	
	for( i = 1 , p = head ; i <= n ; i++ ){
		scanf("%d %d %s" , &ope , &loc , str ) ;
		node = (process*)(malloc(sizeof(process))) ;
		node->llink = p ;
		node->rlink = NULL ;
		node->operation = ope ;
		node->location = loc ;
		strcpy(node->string,str) ;
		p->rlink = node ;
		p = p->rlink ;
	} 
	ope = 0 ;
	while( ope != -1 ){
		scanf("%d" , &ope ) ;
		if( 1 == ope ){
			scanf("%d %s" , &loc , str ) ;
			node = (process*)(malloc(sizeof(process))) ;
			node->llink = p ;
			node->rlink = NULL ;
			node->operation = ope ;
			node->location = loc ;
			strcpy(node->string,str) ;
			p->rlink = node ;
			p = p->rlink ;
			insert( passage , str , loc ) ;
/*			puts(passage) ;/*                                         */
		}
		else if( 2 == ope ){
			scanf("%d %d" , &loc , &length ) ;
			for( i = loc , j = 0 ; i < loc+length ; i++ , j++ ){
				str[j] = passage[i] ;
			}
/*			puts(str) ;/*                                         */
			str[j] = '\0' ;
			node = (process*)(malloc(sizeof(process))) ;
			node->llink = p ;
			node->rlink = NULL ;
			node->operation = ope ;
			node->location = loc ;
			strcpy(node->string,str) ;
			p->rlink = node ;
			p = p->rlink ;
			del( passage , length , loc ) ;
/*			puts(passage) ;/*                                         */
		}
		else if( 3 == ope ){
			if( p != head ){
				if( p->operation == 1 ){
					length = strlen(p->string) ;
					del( passage , length , p->location ) ;
/*					puts(passage) ;/*                                         */
					q = p ;
					p = p->llink ;
					p->rlink = NULL ;
					free(q) ;
				}
				else if( p->operation == 2 ){
					insert( passage , p->string , p->location ) ;
/*					puts(passage) ;/*                                         */
					q = p ;
					p = p->llink ;
					p->rlink = NULL ;
					free(q) ;
				}
			}
		}
		else{
			break ;
		}
	}
	
	puts(passage) ;
	
	return 0;
}

void insert( char s[] , char add[] , int n ){
	strcat( add , &s[n] ) ;
	s[n] = '\0' ;
	strcat( s , add ) ;
}

void del( char s[] , int length , int n ){
	char div[513] ;
	int k , i ;
	for( i = 0 ; div[i] != 0 ; i++ ){
		div[i] = 0 ;
	}
	k = strlen(s) ;
	if( n+length >= k ){
		length = k - n ;
	}
	strcat( div , &s[n+length]) ;
	s[n] = '\0' ;
	strcat( s , div ) ;
}
