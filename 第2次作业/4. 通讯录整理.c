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

char name[105][50] , number[105][50] ;
char tem[105] , max[105][50] , max_number[105][50];

int main(){
	
	int n ;
	int i , j , k = 0 , l , add , length , a1 , a2 , judge , count ;
	
	scanf("%d" , &n ) ;/*输入*/ 
	
	for( i = 0 ; i < n ; i++ ){
		scanf("%s %s" , name[i] , number[i] ) ;
	}
	
	for( i = 0 , count = 0 ; i < n ; i++ ){/*去除完全一样的*/ 
		for( j = n - 1 ; j > i ; j-- ){
			if( name[j][0] != '!' && name[i][0] != '!' ){
				if( strcmp(name[j] , name[i]) == 0 && i != j ){
					if(strcmp(number[j] , number[i]) == 0){
						name[j][0] = '!' ;
						count++ ; 
					}
				}
			} 
		}
	}
	count = n - count ;

	for( i = count - 1 , k = count - 1 ; i >= 0 , k >= 0 ; i-- ){/*按字典序排序并整理到新的列中*/ 
		for( l = n - 1 ; l >= 0 && name[l][0] == '!' ; l-- );
		if( l != n - 1 ){
			l++ ;
		}
		for( j = n - 1 , judge = l ; j >= 0 ; j-- ){
			if(name[j][0] != '!'){
				if( strcmp(name[j] , name[judge]) > 0 ){
					judge = j ;
				}
			}
		}

		a1 = strlen(name[judge]) ;
		a2 = strlen(number[judge]) ;
		strcpy(max[k],name[judge]) ;
		strcpy(max_number[k],number[judge]) ;
		max[k][a1] = 0 ;
		max_number[k][a2] = 0 ;
		k--;
		name[judge][0] = '!' ;
	}
	
	for( i = 1 ; i < count ; i++ ){/*加后缀*/ 
		if( strcmp(max[i] ,max[i-1]) == 0 ){
			add = 0 ;
			for( j = i - 1 ; strcmp(max[j] ,max[j+1]) == 0 && add < n ; j++ , add++ );
			for( k = 1 , j = i ; k <= add ; k++ , j++ ){
				length = strlen(max[j]) ;
				max[j][length] = '_' ;
				max[j][length + 1] = k + '0' ;
				max[j][length + 2] = 0 ;
			}
			i += add ;
		}
	} 
	
	for( i = 0 ; i < count ; i++ ){/*输出*/ 
		printf("%s %s\n\n" , max[i] , max_number[i] ) ;
	}
	
	return 0;
}
