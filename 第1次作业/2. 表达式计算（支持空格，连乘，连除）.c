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

char a[10000] ;
int symbol[5] = {0} ;// *  / - + //

void caculate( char c , char *symb);

int main(){
	
	int i ;
	char *p , *q ;
	
	gets(a) ;
	
	for( i = 0 ; a[i] != '=' ; i++ ){
		if( a[i] == '*' ){
			symbol[1]++ ;
		}
		else if( a[i] == '/' ){
			symbol[2]++ ;
		}
		else if( a[i] == '-' ){
			symbol[3]++ ;
		}
		else if(a[i] == '+' ){
			symbol[4]++ ;
		}
	}
	
	for( ; symbol[1] > 0 || symbol[2] > 0 ;  ){
		p = strchr( a , '*' ) ;
		q = strchr( a , '/' ) ;
		if( symbol[1] > 0 && symbol[2] > 0 ){
			if( p < q ){
				caculate( '*' , p ) ;
				symbol[1]-- ;
			}
			else{
				caculate( '/' , q ) ;
				symbol[2]-- ;
			}
		}
		else if( p == NULL && q != NULL ){
			caculate( '/' , q ) ;
			symbol[2]-- ;
		} 
		else if( q == NULL && p != NULL ){
			caculate( '*' , p ) ;
			symbol[1]-- ;
		} 
		
		
	}
	for( ; symbol[3] > 0 || symbol[4] > 0 ; ){
		p = strchr( a , '-' ) ;
		q = strchr( a , '+' ) ;
		if( p != NULL && q != NULL ){
			if( p < q ){
				caculate( '-' , p ) ;
				symbol[3]-- ;
			}
			else{
				caculate( '+' , q ) ;
				symbol[4]-- ;
			}
		}
		else if( p == NULL && q != NULL ){
			caculate( '+' , q ) ;
			symbol[4]-- ;
		} 
		else if( q == NULL && p != NULL ){
			caculate( '-' , p ) ;
			symbol[3]-- ;
		} 
	}
	
	for( i = 0 ; a[i] != '=' ; i++ ){
		if( a[i] >= '0' && a[i] <= '9' ){
			printf("%c" , a[i] ) ;
		}
		if( a[i] == '^' ){
			printf("-") ;
		}
	}
	
	return 0;
}

void caculate( char c , char *symb){
	long long pp = 0 , qq = 0  , elemt , judge0 = 0 , judge1 = 0 , judge2 = 0 ;
	long long i , x ;
	char *begin , *end , *point ;
	
	for( point = symb - 1 ; *point != '+' && *point != '-' && *point != '*' && *point != '/' && *point != '=' && point >= a ; point-- );
	begin = point  + 1;
	for( point = symb + 1 ; *point != '+' && *point != '-' && *point != '*' && *point != '/' && *point != '=' ; point++ );
	end = point - 1 ;
	
	for( point = ( begin ) ; point < symb ; point++ ){
		if( *point == '^' ){
			judge1 = 1 ;
		}
	}
	
	for( point = ( begin ) ; point < symb ; point++ ){
		if( *point >= '0' && *point <= '9'){
			pp += *point - '0' ;
			pp *= 10 ;
		}
	}
	pp /= 10 ;
	if( judge1 == 1 ){
		pp = -pp ;
	}
	
	for( point = ( symb + 1 ) ; point <= end ; point++ ){
		if( *point == '^' ){
			judge2 = 1 ;
		}
	}
	
	for( point = ( symb + 1 ) ; point <= end ; point++ ){
		if( *point >= '0' && *point <= '9'){
			qq += *point - '0' ;
			qq *= 10 ;
		}
	}
	qq /= 10 ;
	if( judge2 == 1 ){
		qq = -qq ;
	}
	
	if( c == '*' ){
		elemt = pp * qq ;
	}
	else if( c == '/' ){
		elemt = pp / qq ;
	}
	else if( c == '-' ){
		elemt = pp - qq ;
	}
	else if( c == '+' ){
		elemt = pp + qq ;
	}
	
	for( point = begin ; point <= end ; point++ ){
		*point = ' ' ;
	}
	
	if( elemt < 0 ){
		elemt = -elemt ;
		judge0 = 1 ;
	}
	if( elemt == 0 ){
		point = end ;
		*point = x + '0' ;
	} 
	
	else{
		for( point = end ; elemt > 0 ; point-- , elemt /= 10 ){
		x = elemt % 10 ;
		*point = x + '0' ;
	}
	
	}
	if( judge0 == 1 ){
		*point = '^' ;
	}
}
