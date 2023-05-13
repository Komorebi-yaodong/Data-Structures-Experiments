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
	if(1){//��ʼ�� վ��ͷ��������·��ͷ 
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
	
	for( i = 1 ; i <= station_number ; i++ ){ //��ʼ�� վ��+��� 
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
	
	for( i = 1 ; i <= train_number ; i++ ){ //���복����Ϣ 
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
	
	if(1){ //�ѳ���ȫ������B  
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
	
	if(1){ //ѭ���ж� 
		tem = station_head ;
		while( tem->rnext != NULL ){
			tem = tem->rnext ;
		}
		while( b_head->right != NULL && station_head != tem ){
			m = b_head ;
			p = a_head ;
			while( p->left != NULL ){//p��A����೵�� 
				p = p->left ;
			}
			while( m->right != NULL ){
				m = m->right ;
			}
			end = m ; // end ��B�� 
			count = 1 ;
			while( strcmp(m->destination,tem->destiation_station) != 0 && m != b_head ){
				m = m->left ;
				count++ ;
			}
			m2 = m ;
			b_end = m->left ;// b_end �Ǽ�ȥ���ֳ�����B�� 
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

1.���� վ �� ��� �� push_num = 0 ��
2.���복�ᣨ��ţ�Ŀ�ĵأ��ı���Լ�վ�� ��
3.ȫ������B��  ��
4.ѭ����ʼ��B���г��ᣩ{      //����ѭ�� ���ܹ��� 
	a.ѭ����B����Զ���붥�������M��˫��ѭ�����ҵ���break�� �� 
	b.��M��������count+1�ڳ��ᣩ����A ��push_num++ �� 
	c.�ж�A�Ƿ�˳�򣺣��ǣ���һ��ѭ�������ǣ���M����C�У�ʣ�ࣨcount�ڳ��ᣩ����B��,�ٰ�M����A�� �� push_num++�� �� 
  }
5. ���A�ĳ�����˳�� ��puts(""); ���push_num �� 

*/
