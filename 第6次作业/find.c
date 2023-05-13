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
#define MAXLINE 1024
#define NHASH  3001
#define MULT  37

struct Node {
	char alp[22] ;
	struct Node *next ;
};

struct Node *hash_tab[NHASH] , *node , *p ;
char words[3502][22];
int num ;
int index[30][2];//索引表内容

void order_find( char target[] ) ;
void half_find( char target[] , int left , int right ) ;
void index_find( char target[] ) ;
unsigned int hash(char *str) ;
void hash_find( char target[] ) ;

int main() {

	int i , k ;
	int length , way ;
	char word[22] ;
	char target[22] ;
	FILE *in ;

	in = fopen("dictionary3000.txt","r") ;
	i = -1 ;
	while( (fscanf( in , "%s\n" , words[++i] )) != EOF ) ;
	num = i ;

	for( i = 0 ; i < num ; i++ ){
		printf("%s" , words[i] ) ;
	}
	
	//建立 索引表
	for( i = 0 ; i < 30 ; i++ ) {
		index[i][0] = -1 ;
	}
	for( i = 0 ; i < num ; i++ ) {
		if( index[words[i][0]-'a'][0] == -1 ) {
			index[words[i][0]-'a'][0] = i ;
		}
		index[words[i][0]-'a'][1]++ ;
	}

	// 建立 hash表
	for( i = 0 ; i < num ; i++ ) {

		k = hash( words[i] ) ;

		if( hash_tab[k] == NULL ) {
			hash_tab[k] = (struct Node*)(malloc(sizeof(struct Node))) ;
			hash_tab[k]->next = NULL ;
		}

		node = ( struct Node*)(malloc(sizeof(struct Node))) ;
		strcpy( node->alp , words[i] ) ;
		node->next = NULL ;

		p = hash_tab[k] ;
		while( p->next != NULL ) {
			p = p->next ;
		}
		p->next = node ;
	}

	scanf("%s" , target ) ;
	scanf("%d" , &way ) ;

	switch(way) {
		case 1 :
			order_find( target ) ;
			break ;//顺序查找 √
		case 2 :
			half_find( target , 0 , num - 1 ) ;
			break ;//折半查找 √
		case 3 :
			index_find( target ) ;
			break ;//索引表查找 √
		case 4 :
			hash_find( target ) ;
			break ;//hash表查找
	}

	fclose(in) ;

	return 0;
}

void order_find( char target[] ) {
	int i , flag , count ;
	for( i = 0 , count = 0 , flag = 0 ; i < num ; i++ ) {
		count++ ;
		if(strcmp(target,words[i]) == 0) {
			flag = 1 ;
			break ;
		} else if( strcmp(target,words[i]) < 0 ) {
			flag = 0 ;
			break ;
		}
	}
	printf("%d %d" , flag , count ) ;
}

void half_find( char target[] , int left , int right ) {
	int flag = 0 , count = 0 ;
	int  mid = 0 ;
	while( left <= right ) {
		count++ ;
		mid = (left+right)/2 ;
		if( strcmp(target,words[mid]) < 0 ) {
			right= mid-1 ;
		} else if(strcmp(target,words[mid]) > 0) {
			left = mid+1 ;
		} else {
			break ;
		}
	}
	if( strcmp(target,words[mid]) == 0 ) {
		flag = 1 ;
	} else {
		flag = 0 ;
	}
	printf("%d %d" , flag , count ) ;
}

void index_find( char target[] ) {
	int left , right ;
	left = index[target[0]-'a'][0] ;
	right = left + index[target[0]-'a'][1] - 1 ;
	half_find( target , left , right ) ;
}

unsigned int hash(char *str) {
	unsigned int h=0;
	char *p;

	for(p=str; *p!='\0'; p++) {
		h = MULT*h + *p;
	}

	return h % NHASH;
}

void hash_find( char target[] ) {
	struct Node *q ;
	int count = 0 , flag = 0 ;
	int k = 0 ;

	k = hash( target ) ;
	if( hash_tab[k] == NULL ) {
		count++ ;
		flag = 0 ;
	} 
	else {
		q = hash_tab[k] ;
		do {
			count++ ;
			q = q->next ;
		} while( q->next != NULL && strcmp( target , q->alp ) > 0 ) ;
		if( q == NULL ) {
			flag = 0 ;
		} else if( strcmp( target , q->alp ) == 0 ) {
			flag = 1 ;
		} else if( strcmp( target , q->alp ) < 0 ) {
			flag = 0 ;
		}
	}
	printf("%d %d" , flag , count ) ;
}
