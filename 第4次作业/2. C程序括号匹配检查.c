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

char stack[202] , line[MAXLINE] , stack_1[202] ;
int num[202] , num_1[202] , top = -1 , ope[202] ;

int main(){
	
	int i , j , k , count = 0 , judge_1 = 1 , judge_2 = 1 , exe = 1 ;
	FILE *in ;
	
	in = fopen("example.txt","r") ;/* example.c */
	
	if( NULL == in ){
		printf("open file error\n") ;
	}
	
	while( ( fgets( line , MAXLINE , in )) != NULL ){
		count++ ;
		for( i = 0 , exe = 1 ; line[i] != 0 ; i++ ){
			if( '/' == line[i] && 0 != line[i+1] ){
				if( '/' == line[i] && '*' == line[i+1] ){
					judge_1 = 0 ;
				}
				if( '/' == line[i] && '/' == line[i+1] ){
					break ;
				}
			}
			else if( '"' == line[i] && judge_2 == 1 ){
				judge_2 = 0 ;
			}
			else if( '"' == line[i] && judge_2 == 0 ){
				judge_2 = 1 ;
			}
			else if( '*' == line[i] && 0 != line[i+1] ){
				if( '*' == line[i] && '/' == line[i+1] ){
					judge_1 = 1 ;
				}
			}
			if( 1 == judge_2 && 1 == judge_1 && (line[i] == '(' || line[i] == ')' || line[i] == '{' || line[i] == '}') ){
				stack[++top] = line[i] ;
				num[top] = count ;
			}
		}
	}
/*
	for( i = 0 ; i <= top ; i++ ){
		printf("%c %d " , stack[i] , num[i] ) ;
	} 
	puts("") ;
*/	
	for( i = 0 , j = -1 ; i <= top ; i++ ){
		if( stack[i] == '(' || stack[i] == '{' ){
			stack_1[++j] = stack[i] ;
			num_1[j] = num[i] ;
			if( stack[i] == '{' && j >= 0 ){
				if( stack_1[j-1] == '(' ){
					printf("without maching '%c' at line %d" , stack_1[j-1] , num_1[j-1] ) ;
					return 0 ;
				}
			}
		}
		else if( stack[i] == ')' ){
			if( j < 0 ){
				printf("without maching '%c' at line %d" , stack[i] , num[i] ) ;
				return 0 ;
			}
			else if( stack_1[j] != '(' ){
				printf("without maching '%c' at line %d" , stack[i] , num[i] ) ;
				return 0 ;
			} 
			else if( stack_1[j] == '(' ){
				j-- ;
			}
		}
		else if( stack[i] == '}' ){
			if( j < 0 ){
				printf("without maching '%c' at line %d" , stack[i] , num[i] ) ;
				return 0 ;
			}
			else if( stack_1[j] != '{' ){
				printf("without maching '%c' at line %d" , stack[i] , num[i] ) ;
				return 0 ;
			} 
			else if( stack_1[j] == '{' ){
				j-- ;
			}
		}
	}
	if( j >= 0 ){
		printf("without maching '%c' at line %d" , stack_1[j] , num_1[j] ) ;
		return 0 ;
	}
	else{
		for( i = 0 ; i <= top ; i++ ){
			printf("%c" , stack[i] , stack[i] ) ;
		}
	}
	fclose(in) ;
	return 0 ; 
}
