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

struct Tire{//字典树 
	int number ;
	struct Tire *link[26] ;
}; 

struct Sentence{
	int fre ;
	char *start ;
	char *end ;
};

struct Tire *head ;
struct Sentence cut[10000000] ;
char article[100000000] ;

void add_tire( char word[] ){//组装字典树 
	int i , j ;
	int k ;
	struct Tire *p , *node ;
	for( i = 0 , p = head ; word[i] != 0 ; i++ ){
		k = tolower(word[i])-'a' ;
		if(p->link[k] == NULL ){
			node = (struct Tire *)(malloc(sizeof(struct Tire))) ;
			node->number = 0 ;
			for( j = 0 ; j < 26 ; j ++ ){
				node->link[j] = NULL ;
			}
			p->link[k] = node ;
			p = p->link[k] ;
		} 
		else{
			p = p->link[k] ;
		}
	}
	(p->number)++ ;
}

int find( char word[] ){ //单个单词的频率查找 
	int i , k ;
	struct Tire *p ;
	for( i = 0 , p = head ; word[i] != 0 ; i++ ){
		k =tolower(word[i]) - 'a' ;
		p = p->link[k] ;
	}
	return p->number ;
}

int is_break( char c ){ // 是否句子截止符 
	return ( c == '.' || c == '?'|| c == '!') ;
}

int is_NULL( char c ){ // 是否非单词字符 
	return !(((c >= 'a' && c <= 'z')||(c >='A'&& c <= 'Z'))) ;
}

void divide( char word[] ){ // 停止词记录 
	int i , k ;
	struct Tire *p ;
	for( i = 0 , p = head ; word[i] != 0 ; i++ ){
		k = tolower(word[i]) - 'a' ;
		p = p->link[k] ;
	}
	p->number = 0 ;
}

int S_fre( char *a , char*b ){
	int i , fre_word = 0 ;
	int fre_num = 0 ;
	char *p , c , word[20];
	p = a ;
	i = -1 ;
	while( p != b+1 ){
		c = *p ;
		p++ ;
		if( is_NULL(c) && i < 0 ){
			continue ;
		}
		else if( is_NULL(c)&& i >= 0 ){
			word[++i] = 0 ;
			fre_word = find( word ) ;
			fre_num += fre_word ;
			i = -1 ;
//			memset(word,0,20*sizeof(char)) ;
			continue ;
		}
		word[++i] = c ;
	}
	return fre_num ;
}

int get_mid( int left , int right ){
	int pivot = cut[left].fre ;
	struct Sentence term ;
	int i = left , j = right + 1 ;
	while( i < j ){
		do{
			i++ ;
		}while( pivot > cut[i].fre && i != right ) ;
		do{
			j--; 
		}while( pivot < cut[j].fre && j != left ) ;
		if( i < j ){
			term = cut[j] ;
			cut[j] = cut[i] ;
			cut[i] = term ;
		}
		else{
			break ;
		}
	}
	term = cut[j] ;
	cut[j] = cut[left] ;
	cut[left] = term ;
	
	return j ;
} 

void q_sort( int left , int right ){
	int mid ;
	 if( left < right ){
	 	mid = get_mid( left , right ) ;
	 	q_sort( left , mid-1 ) ;
		q_sort( mid+1 , right ) ;
	 }
}

int main(){
	
	FILE *in , *stop_words , *out ;
	char word[20] , c , *p ;
	int n ;
    int i , j , count , judge = 0 ;
    int num ;
    int str_num = 0 ;
	
	//打开文件 
	in = fopen("article.txt","r") ;
    stop_words = fopen("stopwords.txt","r") ;
    
    //建立Trie树 
    head = (struct Tire *)(malloc(sizeof(struct Tire))) ;
	head->number = 0 ;
	for( j = 0 ; j < 26 ; j ++ ){
		head->link[j] = NULL ;
	}
	count = -1 ;//得到单词频率 
	while( ( c = fgetc(in)) != EOF ){
		if( is_NULL(c) && count < 0 ){
			continue ;
		}
		else if( is_NULL(c)&& count >= 0 ){
			word[++count] = 0 ;
			add_tire( word ) ;
			count = -1 ;
//			memset(word,0,20*sizeof(char)) ;
			continue ;
		}
		word[++count] = c ;
	}
	
	// 在Trie中减去停止词 
    while( (fscanf(stop_words , "%s" , word )) != EOF ){//减去非停止词频率 
    	add_tire( word ) ; 
    	divide(word) ;
	}
	fclose( stop_words ) ;
	
	//重新打开文件（文章文件） 
	fclose( in ) ;
	in = fopen("article.txt","r") ;//article.txt
	
	//读取文章 同时记录词频率
	i = -1 ;
	j = -1 ;
	judge = 0 ;
	num = 0 ;
	while( (c=fgetc(in)) != EOF ){
		article[++i] = c ;
		if( !isspace(c) && !is_break(c) && judge == 0 ){
			cut[++j].start = &article[i] ;
			judge = 1 ;
		}
		if( judge == 1 && is_break(c)){
			cut[j].end = &article[i] ;
			num = S_fre( cut[j].start , cut[j].end ) ;//可否化简？ 
			cut[j].fre = num ;
			judge = 0 ;
		}
	}
	
	str_num = j+1 ;
	
	scanf("%d" , &n ) ;
	
	q_sort( 0 , str_num-1 ) ;//排序 
	
	//标准输出 
	for( i = str_num-1 ; i >= str_num-5 ; i-- ){
		p = cut[i].start ;
		printf("%d " , cut[i].fre ) ; 
		while( p != cut[i].end+1 ){
			printf("%c" , *p ) ;
			p++ ;
		}
		printf("\n") ;
	}
	
	//文件输出 
	out = fopen("results.txt","w") ;
	for( i = str_num-1 ; i >= str_num-n ; i-- ) {
		p = cut[i].start ;
		fprintf( out , "%d " , cut[i].fre ) ;
		while( p != cut[i].end+1 ){
			fputc(*p,out) ;
			p++ ;
		}
		fprintf( out , "\n" ) ;
	}
	
	fclose(in) ;
	fclose(out) ;
	return 0;
}

