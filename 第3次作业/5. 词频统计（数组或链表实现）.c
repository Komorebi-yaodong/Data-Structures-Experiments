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

struct count_alp{
	char alph[50] ;
	int num  ; 
	struct count_alp *next ;
};
typedef struct count_alp alp ;

int main(){
	
	FILE *in ;
	int i , j , k , l , judge ;
	char a[50] , c ;
	alp *head , *tail , *p , *node , *pre , *end ;
	
	in = fopen("article.txt" , "r") ;/* article.txt */
	
	end = (alp*)(malloc(sizeof(alp))) ;
	memset( end , 0 , sizeof(alp) ) ; 
	end->num = 0 ;
	end->next = NULL ;
	
	head = (alp*)(malloc(sizeof(alp))) ;
	memset( head , 0 , sizeof(alp) ) ; 
	head->alph[0] = '0' ;
	head->num = 0 ;
	head->next = end ;
	
	i = 0 ;
	judge = 0 ;
	while( (c=fgetc(in)) != EOF ){
		if( ( c >= 'a' && c <= 'z') || ( c >= 'A' && c <= 'Z') ){
			a[i++] = tolower(c) ;
/*			printf("%c" , a[i-1] ) ;*/
			a[i] = '\0' ; 
			judge = 1 ;
		}
		else{
			if( 0 == judge ){
				continue ;
			}
			else{
				node = (alp*)(malloc(sizeof(alp))) ;
				memset( node , 0 , sizeof(alp) ) ;
				for( j = 0 ; a[j] != 0 ; j++ ){
					(node->alph)[j] = a[j] ;
				}
				(node->alph)[j] = '\0' ;
				node->num = 1 ;
				node->next = NULL ;
				pre = p = head ;
				while( p->next != NULL ){
					if( 0 == strcmp(p->alph , a)){
						p->num++ ;
						free(node) ;
						break ;
					}
					else if( strcmp(p->alph , a) < 0 ){
						pre = p ;
						p = p->next ;
						continue ;
					}
					else{
						pre->next = node ;
						node->next = p ;
						node->num = 1 ;
						break ; 
					}
				}
				if( p == end ){
					pre->next = node ;
					node->next = end ;
				}
				for( j = 0 ; a[j] != 0 ; j++ ){
					a[j] = '\0' ;
				}
				i = 0 ;
				judge = 0 ;
			}
		}
	}
	p = head->next ;
	while( p->next != NULL ){
		printf("%s %d\n" , p->alph , p->num ) ;
		p = p->next ;
	}
	
	return 0;
}
