#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct elect{
	int num ;
	struct elect *next ;
};

struct elect *create_node(int data){//创建新的节点 // 
	struct elect *node = NULL ;
	node = (struct elect*)(malloc(sizeof(struct elect))) ;
	if( NULL == node ){
		printf(" malloc error\n") ;
	}
	memset( node , 0 , sizeof(struct elect) ) ;
	node->num = data ;
	node->next = NULL ;
}

void tail_insect( struct elect *now , struct elect *new_end ){// 尾插// 
	struct elect *p = now ;
	while( NULL != p->next ){
		p = p->next ;
	}
	p->next = new_end ;
}

int delete_node( struct elect *now , int data ){//删除// 
	struct elect *p = now ;
	struct elect *pre = NULL ;
	while( NULL!= p->next ){
		pre = p ;
		p = p->next ;
		if( p->num == data ){
			if( NULL != p->next ){
				pre->next = p->next ;
				free( p ) ;
			}
			else{
				pre->next = NULL ;
				free(p) ;
			}
			return 0 ;
		}
	}
	return -1 ;
}
	
int main(){
	
	struct elect *start = create_node(0) , *p = NULL , *pre = NULL ;
	int n , m , q ;//n个人 报数到m 从q开始 // 
	int i , judge , count ;
	
	scanf("%d %d %d" , &n , &m , &q ) ;
	
	for( i = 1 ; i <= n ; i++ ){
		tail_insect( start , create_node(i) ) ;
	}
	
	
	for( i = 0 , p = start ; i < q ; i++ , p = p->next ) {
	}
	
	count = 1 ;
	while( (start->next)->next != NULL ){
		if( m == count ){
			pre = p ;
			if( NULL == p->next ){
				p = start->next ; 
				count = 1 ;
			}
			else{
				p = p->next ;
				count = 1 ;
			}
			judge = delete_node( start , pre->num ) ;
		}
		else{
				if( NULL == p->next ){
				p = start->next ;
				count++ ;
			}
			else{
				p = p->next ;
				count++ ;
			}
		}
	}
	
	printf("%d" , (start->next)->num ) ;
	
	return 0 ;
}
