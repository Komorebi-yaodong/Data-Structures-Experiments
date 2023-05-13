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
	
	int i , j , k , judge ;
	char key[50] , code[50] , alp = 'z' , read ;
	FILE *in , *out ;
	
	scanf("%s" , key ) ;
	
	for( i = 0 , j = 0 ; key[i] != 0 ; i++ ){
		if( key[i] >= 'a' && key[i] <= 'z' ){
			judge = 1 ;
			for( k = 0 ; k < i ; k++ ){
				if( key[i] == key[k] ){
					judge = 0 ;
				}
			}
			if(judge == 1 ){
				code[j++] = key[i] ;
			}
		}
	}
	
	for( ; alp >= 'a' ; alp-- ){
		judge = 1 ;
		for( i = 0 ; key[i] != 0 ; i++ ){
			if( alp == key[i] ){
				judge = 0 ;
			}
		}
		if( 1 == judge ){
			code[j++] = alp ;
		}
	}
	code[j] = 0 ;
	
	in = fopen("encrypt.txt" , "r") ;
	out = fopen("output.txt" , "w") ;
	
	while( ( read = fgetc(in) ) != EOF){
		if( read >= 'a' && read <= 'z' ){
			read = code[read - 'a'] ;
		}
		fputc(read,out) ;
	}
	
	fclose(in) ;
	fclose(out) ;
	
	return 0;
}

