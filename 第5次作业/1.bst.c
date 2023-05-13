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

struct NODE{
	int data ;
	struct NODE *left ;
	struct NODE *right ;
}; 

typedef struct NODE Node ;

struct TREE{
	Node *root;
};

typedef struct TREE Tree ;

void insert(Tree *tree , int num ){//¶þ²æËÑË÷Ê÷²åÈë 
	Node *node , *tem ;
	node = (Node*)(malloc(sizeof(Node))) ;
	if( node == NULL ){
		printf("memory error\n") ;
	}
	node->data = num ;
	node->left = NULL ;
	node->right = NULL ;
	tem = tree->root ;
	if( tree->root == NULL ){
		tree->root = node ;
	}
	else{
		while( tem != NULL ){
			if( tem->data > num ){
				if( tem->left == NULL ){
					tem->left = node ;
					break ;
				}
				else{
					tem = tem->left ;
				}
			}
			else{
				if( tem->right == NULL ){
					tem->right = node ;
					break ;
				}
				else{
					tem = tem->right ;
				}
			}
		}
	}
}

void leaf_visit( Node *node , int k ){
	if( node != NULL ){
		if (node->left == NULL && node->right == NULL ){
			printf("%d %d\n" , node->data , k ) ;
		}
		leaf_visit( node->left , k+1 ) ;
		leaf_visit( node->right , k+1 ) ;
	}
} 

int main(){
	Tree tree ;
	int n , num ;
	int i ;
	
	tree.root = NULL ;
	scanf("%d" , &n ) ;
	
	for( i = 1 ; i <= n ; i++ ){
		scanf("%d" , &num ) ;
		insert( &tree , num ) ;
	}
	
	leaf_visit( tree.root , 1 ) ;
	
	return 0;
}
