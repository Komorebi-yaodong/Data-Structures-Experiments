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

int main(){

    int i , j , k = -1 , judge = 0 ;
    int point = -1 , symbol = -1 ;
    char stack[102] ;
    char str[102] , c ; 
    
    gets(str) ;
    
    j = strlen(str) ;
    
    if( str[0] == '-' ){
    	symbol = 1 ;
	}

	for( i = 0 ; str[i] != 0 ; i++ ){
		if( str[i] == '.' ){
			point = i ;
			break ;
		}
	}
	
	if( point == -1 ){
		if( symbol == 1 ){
			printf("-") ;
		}
		if( str[1] == '\0' ){
			printf("%ce0" , str[0] ) ;
		}
		else{
			printf("%c" , str[0] ) ;
			for( i = j-1 , k = -1 , judge = 0 ; i>=1 ; i-- ){
				if( str[i] != '0' ){
					judge = 1 ;
				}
				if( judge == 1 ){
					stack[++k] = str[i] ;
				}
			}
			if( k != -1 ){
				printf(".") ;
			}
			for( ; k>=0 ; k-- ){
				printf("%c" , stack[k] ) ;
			}
			printf("e%d" , j-1 ) ;
		}
	}
	else{
		if( str[0] != '0' ){
			printf("%c." , str[0] ) ;
			for( i = 1 ; str[i] != 0 ; i++ ){
				if( str[i] != '.' ){
					printf("%c" , str[i] ) ;
				}
			}
			printf("e%d" , point-1 ) ;
		}
		else{
			for( judge = 0 , i = 0 ; str[i] != 0 ; i++ ){
				if( str[i] != '0' && str[i] != '.' ){
					judge = i ;
					break ;
				}
			}
			if( str[judge+1] == 0 ){
				printf("%ce%d" , str[judge] , point-j+1 ) ;
			}
			else{
				printf("%c." , str[judge] ) ;
				for( i = judge+1 ; str[i] != 0 ; i++ ){
					printf("%c" , str[i] ) ;
				} 
				printf("e%d" , point-judge ) ;
			}
		}
	}
	
	return 0;
}

