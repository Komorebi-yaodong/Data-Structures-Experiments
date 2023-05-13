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

int count = 0 ;

void Select_sort_min( int a[] , int n ) ;
void Bubble_sort( int a[] , int n ) ;
void adjust(int k[ ],int i,int n) ;
void HeapSort( int a[] , int n ) ;
void quickSort( int k[] , int left , int right ) ;
void merge(int x[ ],int tmp[ ],int left,int leftend,int rightend) ;
void mSort( int k[] , int term[] , int left , int right ) ;
void mergeSort( int k[] , int n ) ;

int main() {

	int n ;
	int function ;
	int a[101] ;
	int i , j , k ;

	scanf("%d%d" , &n , &function ) ;

	for( i = 0 ; i < n ; i++ ) {
		scanf("%d" , &a[i] ) ;
	}

	switch(function) {
		case 1://  Ñ¡ÔñÅÅÐò ¡Ì
			Select_sort_min( a , n ) ;
			break ;
		case 2:// Ã°ÅÝÅÅÐò ¡Ì
			Bubble_sort( a , n ) ;
			break ;
		case 3:// ¶ÑÅÅÐò ¡Ì 
			HeapSort( a , n ) ;
			break ;
		case 4://¶þÂ·¹é²¢ÅÅÐò ¡Ì 
			mergeSort( a , n ) ;
			for( k = 0 ; k < n ; k++ ) {
				printf("%d " , a[k] ) ;
			}
			printf("\n%d" , count ) ;
			break ;
		case 5://¿ìËÙÅÅÐò ¡Ì 
			quickSort( a , 0 , n-1 ) ;
			
			for( k = 0 ; k < n ; k++ ) {
				printf("%d " , a[k] ) ;
			}
			printf("\n%d" , count ) ;
			
			break ;
	}



	return 0;
}

void Select_sort_min( int a[] , int n ) {
	int i , j , min , k ;
	int term ;
	for( i = 0 , count = 0 ; i < n ; i++ ) {
		for( j = i+1 , min = i ; j < n ; j++ , count++ ) {
			if( a[min] > a[j] ) {
				min = j ;
			}

		}
		term = a[i] ;
		a[i] = a[min] ;
		a[min] = term ;
	}
	for( k = 0 ; k < n ; k++ ) {
		printf("%d " , a[k] ) ;
	}
	printf("\n%d" , count ) ;
}

void Bubble_sort( int a[] , int n ) {
	int i , j , k , term , flag = 0 ;
	for( i = n-1 , count = 0 ; i >= 0 ; i-- ) {
		for( j = 0 , flag = 1 ; j < i ; j++ , count++ ) {
			if(a[j] > a[j+1]) {
				term = a[j] ;
				a[j] = a[j+1] ;
				a[j+1] = term ;
				flag = 0 ;
			}
		}
		if(flag == 1) {
			break;
		}
	}
	for( k = 0 ; k < n ; k++ ) {
		printf("%d " , a[k] ) ;
	}
	printf("\n%d" , count ) ;
}

void adjust(int k[ ],int i,int n) {
	int j , temp ;

	temp = k[i] ;
	j = 2*i+1 ;

	while( j < n ) {
		if( j < n-1 && k[j] < k[j+1] ) {
			j++ ;
		}
		count++ ;
		if( temp >= k[j] ) {
			break ;
		}
		k[(j-1)/2] = k[j];
		j = 2*j+1 ;
	}
	k[(j-1)/2] = temp ;
}

void HeapSort( int a[] , int n ) {
	int i , term , k ;

	for( i = n/2-1 ; i>= 0 ; i-- ) {
		adjust( a , i , n ) ;
	}

	for( i = n - 1 ; i > 0 ; i-- ) {
		term = a[0] ;
		a[0] = a[i] ;
		a[i] = term ;
		adjust( a , 0 , i ) ;
	}

	for( k = 0 ; k < n ; k++ ) {
		printf("%d " , a[k] ) ;
	}
	printf("\n%d" , count ) ;
}

void quickSort( int k[] , int left , int right ){
	int i , last , term ;

	if( left < right ){
		last = left ;
		for( i = left+1 ; i <= right ; i++ ){
			count++; 
			if( k[i] < k[left] ){
				term = k[++last] ;
				k[last] = k[i] ;
				k[i] = term ;
			}
		}
		term = k[last] ;
		k[last] = k[left] ;
		k[left] = term ;
		
		quickSort(k,left,last-1);
		quickSort(k,last+1,right);
	}
}

void merge(int x[ ],int tmp[ ],int left,int leftend,int rightend){     
    int i=left, j=leftend+1, q=left;

    while(i<=leftend && j<=rightend){
    	count++ ;
        if(x[i]<=x[j]) {
        	tmp[q++]=x[i++];
		}
        else{
        	tmp[q++]=x[j++];
        }
    }

    while(i<=leftend){
    	tmp[q++]=x[i++];
	}
    while(j<=rightend){
    	tmp[q++]=x[j++];
	}
    for(i=left; i<=rightend; i++){
    	x[i]=tmp[i];
    }
}

void mergeSort( int k[] , int n ){ // ¶þÂ·¹é²¢ÅÅÐò 
	int *term ;
	term = (int*)(malloc(sizeof(int)*n)) ;
	mSort( k , term , 0 , n-1 ) ;
	free(term) ;
}

void mSort( int k[] , int term[] , int left , int right ){
	int center ;
	if( left < right ){
		center = (left+right)/2 ;
		mSort(k,term,left,center) ;
		mSort(k,term,center+1,right) ;
		merge(k,term,left,center,right) ;
	}
}
