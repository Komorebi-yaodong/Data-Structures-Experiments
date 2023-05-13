#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

struct train_array{
	char no[22] ;
	char destination[22] ;
	int distance ;
	struct train_array *left ;
	struct train_array *right ;
};

struct train_station{
	char destiation_station[22] ;
	int station_distance ;
	struct train_station *lnext ;
	struct train_station *rnext ;
};

typedef struct train_array train ;
typedef struct train_station station ;

void station_insert( station *head , station *node ){
	station *p = head ;
	while( p->rnext != NULL ){
		p = p->rnext ;
	}
	node->lnext = p ;
	p->rnext = node ;
	p = p->rnext ;
}

void train_insert( train *head , train *node , int flag ){
	train *p = head ;
	if( flag == 1 ){
		while( p->left != NULL ){
			p = p->left ;
		}
		node->right = p ;
		p->left = node ;
	}
	else{
		while( p->right != NULL ){
			p = p->right ;
		}
		node->left = p ;
		p->right = node ;
	}
}

int main(){
	
	train *a_head , *b_head , *p , *node , *m , *end , *m2 , *b_end ;
	station *station_head , *station_node , *q1 , *q2 , *tem ;
	int station_number , train_number , push_number = 0 , count ;
	int i , j , k , judge ;
	if(1){//初始化 站点头，三条铁路的头 
		station_head = (station*)(malloc(sizeof(station))) ; 
		station_head->destiation_station[0] = '\0' ;
		station_head->station_distance = 0 ;
		station_head->lnext = NULL ;
		station_head->rnext = NULL ;
		
		a_head = (train*)(malloc(sizeof(train))) ;
		a_head->destination[0] = 0 ;
		a_head->no[0] = 0 ;
		a_head->distance = 0 ;
		a_head->left = NULL ;
		a_head->right = NULL ;
		
		b_head = (train*)(malloc(sizeof(train))) ;
		b_head->destination[0] = 0 ;
		b_head->no[0] = 0 ;
		b_head->distance = 0 ;
		b_head->left = NULL ;
		b_head->right = NULL ;

	}
	
	scanf("%d" , &station_number ) ;
	
	for( i = 1 ; i <= station_number ; i++ ){ //初始化 站点+里程 
		station_node = (station*)(malloc(sizeof(station))) ;
		if( !station_node ){
			printf("memory error : station \n") ;
		}
		station_node->lnext = NULL ; 
		station_node->rnext = NULL ; 
		scanf("%s %d" , station_node->destiation_station , &station_node->station_distance ) ;
		station_insert( station_head , station_node ) ;
	}
	
	scanf("%d" , &train_number ) ;
	
	for( i = 1 ; i <= train_number ; i++ ){ //输入车厢信息 
		node = (train*)(malloc(sizeof(train))) ;
		if( !node ){
			printf("memory error : train \n") ;
		}
		node->left = NULL ;
		node->right = NULL ;
		scanf("%s %s" , node->no , node->destination ) ;
		tem = station_head->rnext ;
		while( strcmp(tem->destiation_station ,node->destination) != 0 ){
			tem = tem->rnext ;
		}
		if( strcmp(tem->destiation_station ,node->destination) == 0 ){
			node->distance = tem->station_distance ;
		}
		else{
			printf("error : distance\n") ; 
		}
		train_insert( a_head , node , 1 ) ;
	}
	
	if(1){ //把车厢全部推入B  
		p = a_head ;
		while( p->left != NULL ){
			p = p->left ;
		}
		b_head->right = p ;
		p->left = b_head ;
		p = a_head->left ;
		p->right = NULL ;
		a_head->left = NULL ;
	}
	
	if(1){ //循环判断 
		tem = station_head ;
		while( tem->rnext != NULL ){
			tem = tem->rnext ;
		}
		while( b_head->right != NULL && station_head != tem ){
			m = b_head ;
			p = a_head ;
			while( p->left != NULL ){//p是A最左侧车厢 
				p = p->left ;
			}
			while( m->right != NULL ){
				m = m->right ;
			}
			end = m ; // end 是B顶 
			count = 1 ;
			while( strcmp(m->destination,tem->destiation_station) != 0 && m != b_head ){
				m = m->left ;
				count++ ;
			}
			m2 = m ;
			b_end = m->left ;// b_end 是减去部分车厢后的B顶 
			if(strcmp(m->destination,tem->destiation_station) == 0){
				m->left->right = NULL ;
				m->left = NULL ;
				end->right = p ;
				p->left = end ;
				push_number+= count ;
				judge = 1 ;
				while( m->right != a_head && m != end->right ){
					if( m->distance > m->right->distance && m->right != a_head ){
						judge = 0 ;
					}
					m = m->right ;
				}
				if( 0 == judge ){
					m = m2 ;
					m2 = m2->right ;
					m2->left = b_end ;
					b_end->right = m2 ;
					end->right = NULL ;
					p->left = m ;
					m->right = p ;
					push_number ++ ;
				}
			}
			else{
				tem = tem->lnext ;
			}
		}
	}
	
	for( p = a_head->left ; p != NULL ; p=p->left ){
		printf("%s " , p->no ) ;
	} 
	puts("") ;
	printf("%d" , push_number ) ;
	return 0;
}
/*

1.输入 站 与 里程 ， push_num = 0 ；
2.输入车厢（编号，目的地）的编号以及站点 ；
3.全部推入B中  ；
4.循环开始（B中有车厢）{      //三重循环 （总共） 
	a.循环找B中最远，离顶最近车厢M（双重循环，找到就break） ； 
	b.把M到顶（共count+1节车厢）推入A ，push_num++ ； 
	c.判断A是否顺序：（是：下一个循环；不是：把M推入C中，剩余（count节车厢）推入B中,再把M推入A中 ， push_num++） ； 
  }
5. 输出A的车厢编号顺序 ，puts(""); 输出push_num ； 

*/
