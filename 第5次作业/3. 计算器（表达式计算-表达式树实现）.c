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

struct cacu_data{
	int flag ;
	int n ;
	char c ;
};
typedef struct cacu_data data ;

struct EXP_TREE{
	int judge ; 
	int number ;
	char str ;
	struct EXP_TREE *left ;
	struct EXP_TREE *right ;
};
typedef struct EXP_TREE Tree ;

int main(){
	
	data exp_2[202] ;//j
	Tree *line[202] , *node ;
	char stack[202] , exp[202] ;//k
	int i , j , k , num , l , ans[202] ;
	
	gets(exp) ;
	
	for( i = 0 , k = -1 , j = -1 , num = 0 ; exp[i] != 0 ; i++ ){
		if( exp[i] >= '0' && exp[i] <= '9' ){
			num = num * 10 + exp[i] - '0' ; 
		}
		else{
			if( i >= 0 && exp[i-1] >= '0' && exp[i-1] <= '9' ){
				exp_2[++j].flag = 1 ;
				exp_2[j].n = num ;
				num = 0 ;
			}
			if( exp[i] == '(' ){
				stack[++k] = '(' ;
			}
			else if( exp[i] == '%' || exp[i] == '*' ||exp[i] == '/' ){
				for( ; k >= 0 && stack[k] == '%' || stack[k] == '*' || stack[k] == '/' ; k-- ){
					exp_2[++j].flag = 2 ;
					exp_2[j].c = stack[k] ;
				}
				stack[++k] = exp[i] ;
			}
			else if( exp[i] == '+' || exp[i] == '-' ){
				for( ; stack[k] != '(' && k >= 0 ; k-- ){
					exp_2[++j].flag = 2 ;
					exp_2[j].c = stack[k] ;
				}
				stack[++k] = exp[i] ;
			}
			else if( exp[i] == ')' ){
				for( ; stack[k] != '(' && k >= 0 ; k-- ){
					exp_2[++j].flag = 2 ;
					exp_2[j].c = stack[k] ;
				}
				k-- ;//£¨ ³öÕ» 
			}
			else if( exp[i] == '=' ){
				for( ; k >= 0 ; k-- ){
					exp_2[++j].flag = 2 ;
					exp_2[j].c = stack[k] ;
				}
				exp_2[++j].flag = 2 ;
				exp_2[j].c = exp[i] ;
			}
		}
	}
	
	for( i = 0 , l = -1 ; i <= j ; i++ ){
		node = (Tree*)(malloc(sizeof(Tree))) ;
		if( exp_2[i].flag == 1 ){
			node->judge = 1 ;
			node->number = exp_2[i].n ;
			node->left = NULL ;
			node->right = NULL ;
		}
		else{
			node->judge = 2 ;
			node->str = exp_2[i].c ;
			node->left = NULL ;
			node->right = NULL ;
		}
		if( node->judge == 1 ){
			line[++l] = node ;
		}
		else{
			node->left = line[l-1] ;
			node->right = line[l] ;
			l -= 2 ;
			line[++l] = node ;
		}
	}
	
	printf("%c " , line[0]->str ) ;
	if(line[0]->left->judge == 1 ){
		printf("%d " , line[0]->left->number ) ;
	}
	else{
		printf("%c " , line[0]->left->str ) ;
	}
	if(line[0]->right->judge == 1 ){
		printf("%d\n" , line[0]->right->number ) ;
	}
	else{
		printf("%c\n" , line[0]->right->str ) ;
	}
	
	for( i = 0 , l = -1 ; i < j ; i++ ){
		if( exp_2[i].flag == 1 ){
			ans[++l] = exp_2[i].n ;
		}
		else{
			switch (exp_2[i].c){
				case '+' : ans[l-1] = ans[l-1]+ans[l] , l-- ; break ;
				case '-' : ans[l-1] = ans[l-1]-ans[l] , l-- ; break ;
				case '*' : ans[l-1] = ans[l-1]*ans[l] , l-- ; break ;
				case '/' : ans[l-1] = ans[l-1]/ans[l] , l-- ; break ;
				case '%' : ans[l-1] = ans[l-1]%ans[l] , l-- ; break ;
			}
		}
	}
	if( l > 0 ){
		printf("error\n") ;
	}
	printf("%d" , ans[0] ) ;

	
	return 0;
}

