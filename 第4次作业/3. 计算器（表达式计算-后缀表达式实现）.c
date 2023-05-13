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

int main(){
	
	data exp2[202] ;
	char stack[202] , exp[202] ;
	int i , j , k , l , num , ans[202] , a ;
	
	gets(exp) ;
	
	for( i = 0 , j = -1 , k = -1 , num = 0 ; exp[i] != 0 ; i++ ){
		if( exp[i] >= '0' && exp[i] <= '9' ){
			num = num * 10 + exp[i] - '0' ; 
		}
		else{
			if( exp[i-1] >= '0' && exp[i-1] <= '9' ){
				exp2[++j].flag = 1 ;
				exp2[j].n = num ;
				num = 0 ;
			}
			if( exp[i] == '(' ){
				stack[++k] = exp[i] ;
			}
			else if( exp[i] == '*' || exp[i] == '/' || exp[i] == '%' ){
				for( ; stack[k] != '(' && k >= 0 && ( stack[k] =='*' || stack[k] =='/' || stack[k] =='%' ); k-- ){
						exp2[++j].flag = 2 ;
						exp2[j].c = stack[k] ;
					}
					stack[++k] = exp[i] ;
			}
			else if( exp[i] == '+' || exp[i] == '-' ){
				if( k == -1 ){
					stack[++k] = exp[i] ;
				}
				else{
					for( ; stack[k] != '(' && k >= 0 ; k-- ){
						exp2[++j].flag = 2 ;
						exp2[j].c = stack[k] ;
					}
					stack[++k] = exp[i] ;
				}
			}
			else if( exp[i] == ')' ){
				for( ; stack[k] != '(' && k >= 0 ; k-- ){
					exp2[++j].flag = 2 ;
					exp2[j].c = stack[k] ;
				}
				k-- ;//£¨ ³öÕ» 
			}
			else if( exp[i] == '=' ){
				for( ; k >= 0 ; k-- ){
					exp2[++j].flag = 2 ;
					exp2[j].c = stack[k] ;
				}
				exp2[++j].flag = 2 ;
				exp2[j].c = exp[i] ;
			}
		}
	}
/*	
	for( i = 0 ; i <= j ; i++ ){
		if(exp2[i].flag == 1 ){
			printf("%d " , exp2[i].n ) ;
		}
		else{
			printf("%c " , exp2[i].c ) ;
		}
	}
	puts("") ;
*/	
	for( i = 0 , l = -1 ; i < j ; i++ ){
		if( exp2[i].flag == 1 ){
			ans[++l] = exp2[i].n ;
/*			printf("%d\n" , exp2[i].n ) ;*/
		}
		else{
/*			printf("%c\n" , exp2[i].c ) ;*/
			switch (exp2[i].c){
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
