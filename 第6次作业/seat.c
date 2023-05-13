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

char stu_num[102][10] , stu_name[102][20] ;

int strswap( char a[] , char b[] ){
	char term[20] ;
	strcpy(term,a) ;
	strcpy(a,b) ; 
	strcpy(b,term) ;
} 

int get_mid( int a[] , int left , int right ){
	int pivot = a[left] ;
	int term ;
	int i = left , j = right + 1 , k ;
	while( i < j ){
		do{
			i++ ;
		}while( pivot > a[i] && i != right ) ;
		do{
			j--; 
		}while( pivot < a[j] && j != left ) ;
		if( i < j ){
			term = a[j] ;
			a[j] = a[i] ;
			a[i] = term ;
			strswap(stu_num[i] , stu_num[j]) ;
			strswap(stu_name[i] , stu_name[j]) ;
		}
		else{
			break ;
		}
	}
	term = a[j] ;
	a[j] = a[left] ;
	a[left] = term ;
	strswap(stu_num[left] , stu_num[j]) ;
	strswap(stu_name[left] , stu_name[j]) ;

	return j ;
} 

void quick_sort( int a[] , int left , int right ){
	int mid ;
	int i , k ;
	if( left < right ){
		mid = get_mid( a , left , right ) ;
		quick_sort( a , left , mid-1 ) ;
		quick_sort( a , mid+1 , right ) ;
	}
}

void Push( int a[] , int n , int left ){
	int i ;
	for( i = n ; i > left ; i-- ){
		a[i] = a[i-1] ;
		strcpy(stu_num[i] , stu_num[i-1]) ;
		strcpy(stu_name[i] , stu_name[i-1]) ;
	}
}
int main(){
	
	int stu_seat[102] ;
	int n ;
	int level ;
	int min ;
    int i , j , k , term ;
    int Q ;
	FILE *in , *out ;
	
	in = fopen("in.txt","r") ;
	out = fopen("out.txt","w") ;
	
	scanf("%d" , &n ) ;
	for( i = 0 ; i < n ; i++ ){
		fscanf( in , "%s %s %d%" , stu_num[i] , stu_name[i] , &stu_seat[i] ) ;
	}
	
	quick_sort( stu_seat , 0 , n-1 ) ;
	
	for( i = 1 ; i < n ; i++ ){ 
		if(stu_seat[i-1]==stu_seat[i]){
			if( strcmp(stu_num[i-1] , stu_num[i]) > 0 ){
				strswap(stu_num[i-1],stu_num[i]) ; 
				strswap(stu_name[i-1],stu_name[i]) ;
				term = stu_seat[i-1] ;
				stu_seat[i-1] = stu_seat[i] ;
				stu_seat[i] = term ;
			}
		}
	} 
	
	Q = MIN(n,stu_seat[n-1]) ;
	
	for( i = 1 ; i <= Q ; i++ ){

		for( j = 0 ; j < n && stu_seat[j] < i ; j++ );
		if( stu_seat[j] == i ){
			continue ;
		}
		else{
			for( k = 0 ; stu_seat[k] < i ; k++ ) ;
			Push( stu_seat , n , k ) ;
			stu_seat[k] = i ;
			strcpy(stu_num[k] , stu_num[n]) ;
			strcpy(stu_name[k] , stu_name[n]) ;
		}
	}
	
	for( i = 1 , level = 1 ; i < n ; i++ ){
		if(stu_seat[i] == stu_seat[i-1]){
			stu_seat[i] = stu_seat[n-1]+level ;
			level++ ;
		}
	}
	
	for( i = 0 ; i < n ; i++ ){ 
		for( j = i , min = i ; j < n ; j++ ){
			if( strcmp(stu_num[min],stu_num[j])>=0){
				min = j ;
			}
		}
		term = stu_seat[i] ;
		stu_seat[i] = stu_seat[min] ;
		stu_seat[min] = term ;
		strswap(stu_num[i] , stu_num[min]) ;
		strswap(stu_name[i] , stu_name[min]) ;
		
	} 
	
	for(i = 0 ; i < n ; i++ ){
		fprintf( out , "%s %s %d\n" , stu_num[i] , stu_name[i] , stu_seat[i] ) ;
	}
	
	fclose(in); 
	fclose(out) ;
	
	return 0;
}
/*
1.排序：按照座位号顺序进行排序（座位号相同时照学号排序）->T2
2.漏排检查：从后往前安排：中间有空位，将T2最后的学生安排至此 
3.重排检查：重排座位依次向后推 
*/

