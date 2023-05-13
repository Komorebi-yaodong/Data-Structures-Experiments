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

struct WORDS {
	char words[200] ;
	int num ;
	struct WORDS *left ;
	struct WORDS *right ;
};
typedef struct WORDS Words ;

struct TREE {
	Words *root ;
};
typedef struct TREE Tree ;

void bst_insert( Tree *tree , char a[] ) {
	Words *node , *tem = tree->root ;
	node = (Words*)(malloc(sizeof(Words))) ;
	node->num = 1 ;
	node->left = NULL ;
	node->right = NULL ;
	strcpy( node->words , a ) ;
	if( tree->root == NULL ) {
		tree->root = node ;
		/*	printf("%s " , tree->root->words ) ;	*/
	} else {
		while( tem != NULL ) {
			if( strcmp(node->words,tem->words) == 0 ) {
				/*					printf("%s " , tem->right->words ) ; */
				tem->num++ ;
				break ;
			} else if( strcmp(node->words,tem->words) > 0 ) {
				if( tem->right == NULL ) {
					tem->right = node ;
					/*					printf("%s " , tem->right->words ) ; */
					break ;
				} else {
					tem = tem->right ;
				}
			} else {
				if( tem->left == NULL ) {
					tem->left = node ;
					/*					printf("%s " , tem->right->words ) ; */
					break ;
				} else {
					tem = tem->left ;
				}
			}
		}
	}
}

void mid_visit( Words *node ) {
	if( node != NULL ) {
		mid_visit( node->left ) ;
		printf("%s %d\n" , node->words , node->num );
		mid_visit( node->right ) ;
	}
}

int main() {
	Tree tree ;
	int k = 0 , judge = 0 ;
	char a[200] , c ;
	FILE *in ;

	tree.root = NULL ;
	in = fopen("article.txt","r");
	while( ( c = fgetc(in)) != EOF ) {
		if( judge == 0 && isalpha(c) ) {
			c = tolower(c) ;
			k = 0 ;
			a[k] = c ;
			k++ ;
			/*			printf("%c" , a[k-1] ) ;	*/
			judge = 1 ;
		} else if( judge == 1 && isalpha(c) ) {
			c = tolower(c) ;
			a[k] = c ;
			k++ ;
			/*			printf("%c" , a[k-1] ) ;	*/
		} else if( judge == 1 && !isalpha(c) ) {
			a[k] = 0 ;
			bst_insert( &tree , a ) ;
			/*		printf("%s\n" , a ) ;  */
			for( k = 0 ; a[k] != 0 ; k++ ) {
				a[k] = 0 ;
			}
			k = 0 ;
			judge = 0 ;
		}
	}
	if( judge == 1 ) {
		a[k] = 0 ;
		bst_insert( &tree , a ) ;
		judge = 0 ;
	}

	if( tree.root != NULL ) {
		printf("%s" , tree.root->words );
		if( tree.root->right != NULL ) {
			printf(" %s" , tree.root->right->words );
			if( tree.root->right->right != NULL ) {
				printf(" %s\n" , tree.root->right->right->words );
			} else {
				puts("") ;
			}
		} else {
			puts("") ;
		}
	}

	mid_visit( tree.root ) ;

	return 0;
}
