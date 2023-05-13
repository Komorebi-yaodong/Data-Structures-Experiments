#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define Pi 3.141593

char s[1000] ;

int main()
{
	int i = 0 , j ;
	
	scanf("%s" , s ) ;
	
	if( s[0] == '-' ){
		i++ ;
	}
	
	for(; s[i] != '\0' ; i++ ){
		if( s[i] != '-' ){
			printf("%c" , s[i] ) ;
		}
		
		else{
			if((islower(s[i-1]))&&(islower(s[i+1]))){
				for( j = 1 ; s[i-1] + j < s[i+1] ; j++ ){
					printf("%c" , s[i-1] + j ) ;
				}
			}
			else if((isupper(s[i-1]))&&(isupper(s[i+1]))){
				for( j = 1 ; s[i-1] + j < s[i+1] ; j++ ){
					printf("%c" , s[i-1] + j ) ;
				}
			}
			else if((s[i-1] >= '0' && s[i-1] <= '9') && (s[i+1] >= '0' && s[i+1] <= '9')){
				for( j = 1 ; s[i-1] + j < s[i+1] ; j++ ){
					printf("%c" , s[i-1] + j ) ;
				}
			}
			else{
				printf("-") ;
			}
		}
	}
	
	return 0 ;
}

