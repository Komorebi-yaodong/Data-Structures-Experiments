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

struct codebook {
	char real ;
	struct codebook *next ;
};

typedef struct codebook code ;

int main() {

	code *head = NULL , *p = NULL , *node =NULL , *tool = NULL ;
	FILE *in , *out ;
	int i , j , count , length , flag ;
	char key_0[33] , key[33] , other[127] , book[2][127] , c , store ;
	//Ã÷Âëh Îª¡¾0¡¿ £¬ °µÂëw Îª¡¾1¡¿//

	gets(key_0) ;

	in = fopen("in.txt","r") ;/* in.txt */
	out = fopen("in_crpyt.txt","w") ;/* in_crpyt.txt */
	key[0] = key_0[0] ;
	key[1] = '\0' ;
	for( i = 1 , j = 1 ; key_0[i] != 0 ; i++ ) {
		if( NULL == strchr( key , key_0[i] ) ) {
			key[j++] = key_0[i] ;
			key[j] = '\0' ;
		}
	}

	for( i = 32 , j = 0 ; i <= 126 ; i++ ) {
		c = i ;
		if( NULL == strchr(key,c) ) {
			other[j++] = c ;
		}
	}
	other[j] = '\0' ;

	length = strlen(key) ;

	for( i = 32 , j = 0 ; i <= 126 ; i++ , j++ ) {
		if( j <= length - 1) {
			book[0][j] = key[j] ;
		} else {
			book[0][j] = other[j-length] ;
		}
	}
	book[0][j] = '\0' ;

	length = strlen(book[0]) ;

	head = (code*)(malloc(sizeof(code))) ;
	head->real = 0 ;
	head->next = NULL ;
	p = head ;
	for( i = 1 ; i <= length ; i++ ) {
		node = (code*)(malloc(sizeof(code))) ;
		memset( node , 0 , sizeof(code) ) ;
		node->real = book[0][i-1] ;
		node->next = NULL ;
		while( p->next != NULL ) {
			p = p->next ;
		}
		p->next = node ;
	}

	p = p->next ;
	p->next = head->next ;
	store = (head->next)->real ;

	while( p->next != p ) {
		tool = p->next ;
		c = tool->real ;
		p->next = tool->next ;
		free(tool) ;
		for( count = c ; count > 1 ; count-- ) {
			p = p->next ;
		}
		for( i = 0 ; book[0][i] != 0 && book[0][i] != c ; i++ ) ;
		book[1][i] = p->next->real ;
	}
	c = p->real ;
	for( i = 0 ; book[0][i] != 0 && book[0][i] != c ; i++ ) ;
	book[1][i] = store ;

	while( (c = fgetc(in)) != EOF ) {
		if( c >= 32 && c <= 126 ) {
			for( i = 0 ; book[0][i] != 0 && book[0][i] != c ; i++ ) ;
			fputc(book[1][i],out) ;
		} else {
			fputc(c,out) ;
		}
	}

	fclose(in) ;
	fclose(out) ;

	return 0;
}
