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

struct polynomial{
	int an ;
	int n ;
	struct polynomial *next ;
};

typedef struct polynomial line ;
/*
void print_line( line *a ){
	line *p = a->next ;
	while( p->next != NULL ){
		printf("%d %d\n" , p->an , p->n ) ;
		p = p->next; 
	}
	printf("%d %d\n" , p->an , p->n ) ;
}
*/
char string1[1000] , string2[1000] ;
int ans[1000][3] ;

int main(){
	
	line *str1 = NULL , *str2 = NULL , *p = NULL , *q = NULL , *node ;
	int i , j , k , tem1 , tem2 , length;
	
	str1 = (line*)(malloc(sizeof(line))) ;
	memset( str1 , 0 , sizeof(line) ) ;
	str1->an = 0 ;
	str1->n = 0 ;
	str1->next = NULL ;
	
	str2 = (line*)(malloc(sizeof(line))) ;
	memset( str2 , 0 , sizeof(line) ) ;
	str2->an = 0 ;
	str2->n = 0 ;
	str2->next = NULL ;
	
	gets(string1) ;
	gets(string2) ;
	
	for( i = 0 ; string1[i] != 0 ; i++ ){
		if( string1[i] >= '0' && string1[i] <= '9' ){
			tem1 = tem2 = 0 ;
			for( ; string1[i] != ' ' && string1[i] != 0 ; i++ ){
				tem1 = tem1 * 10 + (string1[i] - '0') ;
			} 
			i++ ;
			for( ; string1[i] != ' ' && string1[i] != 0 ; i++ ){
				tem2 = tem2 * 10 + (string1[i] - '0') ;
			} 
			p = str1 ;
			node = (line*)(malloc(sizeof(line))) ;
			memset( node , 0 , sizeof(line) ) ;
			node->an = tem1 ;
			node->n = tem2 ;
			node->next = NULL ;
			while( p->next != NULL ){
				p = p->next ;
			}
			p->next = node ;
		}
		if( i >= strlen(string1) - 1 ){
			break ;
		}
	}
	
	for( i = 0 ; string2[i] != 0 ; i++ ){
		if( string2[i] >= '0' && string2[i] <= '9' ){
			tem1 = tem2 = 0 ;
			for( ; string2[i] != ' ' && string2[i] != 0 ; i++ ){
				tem1 = tem1 * 10 + (string2[i] - '0') ;
			} 
			i++ ;
			for( ; string2[i] != ' ' && string2[i] != 0 ; i++ ){
				tem2 = tem2 * 10 + (string2[i] - '0') ;
			} 
			p = str2 ;
			node = (line*)(malloc(sizeof(line))) ;
			memset( node , 0 , sizeof(line) ) ;
			node->an = tem1 ;
			node->n = tem2 ;
			node->next = NULL ;
			while( p->next != NULL ){
				p = p->next ;
			}
			p->next = node ;
		}
		if( i >= strlen(string2) - 1 ){
			break ;
		}
	}
/*	print_line( str1 ) ;
		puts("") ;
		print_line( str2 ) ;
*/	
	p = str1->next ;
	i = 0 ;
	while( p->next != NULL ){
		q = str2->next ;
		while( q->next != NULL ){
			ans[i][0] = q->an * p->an ;
			ans[i][1] = q->n + p->n ;
			i++ ;
			q = q->next ;
		}
		ans[i][0] = q->an * p->an ;
		ans[i][1] = q->n  + p->n ;
		i++ ;
		p = p->next ;
	}
	q = str2->next ;
	while( q->next != NULL ){
		ans[i][0] = q->an * p->an ;
		ans[i][1] = q->n  + p->n ;
		i++ ;
		q = q->next ;
	}
	ans[i][0] = q->an * p->an ;
	ans[i][1] = q->n  + p->n ;
	length = i ;
	p = p->next ;
/*	
	for( i = 0 ; i <= length ; i++ ){
		printf("%d %d\n" , ans[i][0] , ans[i][1] ) ;
	}
*/	
	for( i = 0 ; i < length ; i++ ){
		for( j = i , k = i ; j < length ; j++ ){
			if( ans[k][1] < ans[j][1] ){
				k = j ;
			}
		}
		tem1 = ans[k][0] ;
		ans[k][0] = ans[i][0] ;
		ans[i][0] = tem1 ;
		
		tem1 = ans[k][1] ;
		ans[k][1] = ans[i][1] ;
		ans[i][1] = tem1 ;
	}
/*	
	for( i = 0 ; i <= length ; i++ ){
		printf("%d %d\n" , ans[i][0] , ans[i][1] ) ;
	}
*/	
	for( i = 0 ; i < length ; i++ ){
		if( ans[i][0] != 0 ){
			for( j = i+1 ; j < length && ans[i][1] == ans[j][1] ; j++ ){
				ans[i][0] += ans[j][0] ;
				ans[j][0] = 0 ;
			}
		}
	}
	
	for( i = 0 ; i <= length ; i++ ){
		if( ans[i][0] != 0 ){
			printf("%d %d " , ans[i][0] , ans[i][1] ) ;
		}
	}
	
	return 0;
}
