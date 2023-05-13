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

char str[105] ;

int main() {

	int i , num_point , flag ;
	char *point ;

	gets(str) ;

	for( i = 0 ; str[i] != 0 ; i++ ) {
		if( str[i] != '0' && str[i] != '.' ) {
			flag = i ;
			break ;
		}
	}

	point = strchr( str , '.' ) ;

	num_point = point - str  ;

	if( num_point < flag ) {

		printf("%c" , str[i] ) ;

		if( str[++i] == 0 ) {
			printf("e%d" , num_point - flag ) ;
		}

		else {
			printf(".") ;
			for( ; str[i] != 0 ; i++ ) {
				if( str[i] != '.' ) {
					printf("%c" , str[i] ) ;
				}
			}
			printf("e%d" , num_point - flag ) ;
		}
	} else {
		printf("%c" , str[i] ) ;

		if( str[++i] == 0 ) {
			printf("e%d" , num_point - flag ) ;
		}

		else {
			printf(".") ;
			for( ; str[i] != 0 ; i++ ) {
				if( str[i] != '.' ) {
					printf("%c" , str[i] ) ;
				}
			}
			printf("e%d" , num_point - flag - 1 ) ;
		}
	}

	return 0;
}
