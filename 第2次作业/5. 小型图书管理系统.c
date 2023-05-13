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

FILE *in , *out ;

int compInc() ;
void input_1() ;
void search_2() ;
void Delete_3() ;
void upset_0() ;

int main(){
	
	int i = 0 , k ,  function ;
	char line[MAXLINE] , str[MAXLINE] ; 
	char book1[501][MAXLINE] , book2[501][MAXLINE] ;
	
	in = fopen("books.txt" , "r") ;//books.txt//
	out = fopen("ordered.txt" , "w") ;//ordered.txt//
	
	while( ( fgets( str , MAXLINE , in ) ) != NULL ){
		strcpy( book1[i] , str ) ;
		i++ ;
	}
	k = strlen(book1[i-1]) ;
	book1[i-1][k] = '\n' ;
	book1[i-1][k+1] = '\0' ;
	qsort( book1 , i , sizeof(book1[0]) , compInc );
/*	
	for( i = 0 ; book1[i][0] != 0 ; i++ ){
		printf("%s" , book1[i] ) ;
	}
*/	
	while( (scanf("%d" , &function )) != EOF ){
		if( 1 == function ){//录入// 
			input_1( book1 , book2 ) ;
		}
		else if( 2 == function ){//查找// 
			search_2( book1 ) ;
		}
		else if( 3 == function ){//删除// 
			Delete_3( book1 ) ;
		}
		else{//保存退出// 
			upset_0( book1 ) ;
			break ;
		}
	}
	
	fclose(in) ;
	fclose(out) ;
	
	return 0;
}

int compInc(const void *a, const void *b)//升序 // 
{
	 return (strcmp((char*)a, (char*)b));
}

void input_1( char a[][MAXLINE] , char b[][MAXLINE] ){
	int i , j = 0 , k , judge = 1 , exe = 1 ;
	char line[120] ;
	int c;
	
	while((c=getchar()) !='\n');
	
	gets( line ) ;
	k = strlen(line) ;
	line[k] = '\n' ;
	line[k+1] = '\0' ;
	
	for( i = 0 ; a[i][0] != 0 ; i++ ) ;
	k = i - 1 ;
	
	if( strcmp( line , a[0] ) < 0 && 1 == judge ){
		strcpy( b[j] , line ) ;
		j++ ;
		judge = 0 ;
	}
	for( i = 0 ; a[i][0] != 0; i++ ){
		if( i > 0 && strcmp( line , a[i] ) < 0 && strcmp( line , a[i-1] ) > 0 && 1 == judge){
			strcpy( b[j] , line ) ;
			j++ ;
			strcpy( b[j] , a[i] ) ;
			j++ ;
			judge = 0 ;
		}
		else{
			strcpy( b[j] , a[i] ) ;
			j++ ;
		}
	}
	if( 1 == judge && strcmp( line , a[k] ) > 0 ){
		strcpy( b[j] , line ) ;
		j++ ;
		judge = 0 ;
	}
	for( i = 0 ; b[i][0] != 0 ; i++ ){
		strcpy( a[i] , b[i] ) ;
	}
} 

void search_2( char a[][MAXLINE] ){
	int i , j , k , count ;
	char line[120] ;
	
	int c;
	k = strlen(line) ;
	line[k] = '\n' ;
	line[k+1] = '\0' ;
	
	while((c=getchar()) !='\n');
	
	gets(line) ;
	
	for( i = 0 ; a[i][0] != 0 ; i++ ){
		k = 0 ;
		if( strstr( a[i] , line ) != 0 ){
			for( j = 0 , count = 0 ; a[i][j] != ' ' ; j++ , count++ ){//书名// 
				printf("%c" , a[i][j]) ;
			}
			k = 50 - count ;
			for( ; k > 0 ; k-- ){
				printf(" ") ;
			}
			for( ; a[i][j] == ' ' ; j++ ) ;
			
			for( count = 0 ; a[i][j] != ' ' ; j++ , count++ ){//作者// 
				printf("%c" , a[i][j] ) ;
			}
			k = 20 - count ;
			for( ; k > 0 ; k-- ){
				printf(" ") ;
			}
			for( ; a[i][j] == ' ' ; j++ ) ;
			
			for( count = 0 ; a[i][j] != ' ' ; j++ , count++ ){//出版社// 
				printf("%c" , a[i][j] ) ;
			}
			k = 30 - count ;
			for( ; k > 0 ; k-- ){
				printf(" ") ;
			}
			for( ; a[i][j] == ' ' ; j++ ) ;
			
			for( count = 0 ; a[i][j] != 0 ; j++ , count++ ){//出版日期// 
				printf("%c" , a[i][j] ) ;
			}
		}
	}
}

void Delete_3( char a[][MAXLINE] ){
	int i , j , k ;
	char line[MAXLINE] ;
	int c;
	
	while((c=getchar()) !='\n');
	
	gets(line) ;
	
	for( i = 0 ; a[i][0] != 0 ; i++ ){
		if( strstr( a[i] , line ) != 0 ){
			a[i][0] = '!' ;
		}
	}
	for( i = 0 ; a[i][0] != 0 ; i++ ){
		if( a[i][0] == '!' ){
			for( k = i ; a[k][0] != 0 ; k++ ){
				if( a[k][0] != '!' ){
					strcpy( a[i] , a[k] ) ;
					a[k][0] = '!' ;
					break ;
				}
			}
		}
	}
	for( i = 0 ; a[i][0] != '!' && a[i][0] != 0; i++ );
	for( ; a[i][0] != 0 ; i++ ){
		a[i][0] = 0 ;
	}
}

void upset_0( char a[][MAXLINE]){
	int i , j , k , l , count ;
	char line[MAXLINE] ;
	
	for( i = 0 ; a[i][0] != 0 ; i++ ){
		for( j = 0 , count = 0 ; a[i][j] != ' ' ; j++ , count++ ){//书名// 
			line[j] = a[i][j] ;
		}
		l = j ;
		k = 50 - count ;
		for( ; k > 0 ; k-- ){
			line[j++] = ' ' ;
		}
		for( ; a[i][l] == ' ' ; l++ ) ;
		
		for( count = 0 ; a[i][l] != ' ' ; j++ , l++ , count++ ){//作者// 
			line[j] = a[i][l] ;
		}
		k = 20 - count ;
		for( ; k > 0 ; k-- ){
			line[j++] = ' ' ;
		}
		for( ; a[i][l] == ' ' ; l++ ) ;
		
		for( count = 0 ; a[i][l] != ' ' ; j++ , l++ , count++ ){//出版社// 
			line[j] = a[i][l] ;
		}
		k = 30 - count ;
		for( ; k > 0 ; k-- ){
				line[j++] = ' ' ;
		}
		for( ; a[i][l] == ' ' ; l++ ) ;
		
		for( count = 0 ; a[i][l] != 0 ; j++ , l++ , count++ ){//出版日期// 
			line[j] = a[i][l] ;
		}
		line[j] = '\0' ;
		fputs( line , out ) ;
	}
}
