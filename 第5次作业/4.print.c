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

typedef struct DEVICES {

	int ID ;
	int type ;//0：交换机 1：计算机 2：打印机
	int father_ID ;
	int father_port ;//对应父结点的端口
	struct DEVICES *port[9] ;
	int mark ;
} Dev;

Dev *p , *printer[300] = { NULL } ;
int plug = -1 , printers[300] = { 0 } ;

Dev* create_node() { //创造设备结点
	Dev *node ;
	int i = 0 ;
	node = (Dev*)(malloc(sizeof(Dev))) ;
	if( node == NULL ) {
		printf("memory error\n") ;
	}
	node->father_ID = -2 ;
	node->father_port = -2 ;
	node->ID = -2 ;
	node->type = -2 ;
	node->mark = 0 ;
	for( i = 0 ; i <= 8 ; i++ ) {
		node->port[i] = NULL ;
	}

	return node ;
}

void insert( Dev *point , int id , int tp , int f_id , int fp ) { //插入设备
	Dev *node ;
	int i ;

	if( point == NULL ) {
		printf("insert() function error\n") ;
	}

	if( point->ID == f_id ) {
		node = create_node() ;
		if( node == NULL ) {
			printf("create error\n");
		}
		node->ID = id ;
		node->type = tp ;
		node->father_ID = f_id ;
		node->father_port = fp ;
		node->port[8] = point ;
		point->port[fp] = node ;
	} else if( point->ID != f_id ) {
		for( i = 0 ; i < 8 ; i++ ) {
			if( point->port[i] != NULL ) {
				insert( point->port[i] , id , tp , f_id , fp ) ;
			}
		}
	}

}
void visit_computer( Dev *point , int computer ) {

	int i ;

	if( point->ID == computer ) {
		p = point ;
	} else {
		for( i = 0 ; i < 8 ; i++ ) {
			if( point->port[i] != NULL ) {
				visit_computer( point->port[i] , computer );
			}
		}
	}
}

void visit_printer( Dev *point ) {
	int i ;
	if( point->type == 2 ) {
		printer[++plug] = point ;
	} else {
		for( i = 0 ; i < 8 ; i++ ) {
			if( point->port[i] != NULL ) {
				visit_printer( point->port[i] );
			}
		}
	}
}

void clearing( Dev *point ) {
	int i ;
	point->mark = 0 ;
	for( i = 0 ; i < 8 ; i++ ) {
		if( point->port[i] != NULL ) {
			clearing( point->port[i] );
		}
	}
}

void back_printer( Dev *point ) {
	point->mark = 1 ;
	if( point->ID != 0 ) {
		back_printer( point->port[8] ) ;
	}
}

int main() {

	Dev *head , *read ;
	FILE *in ;
	char line[MAXLINE] , alp ;
	int a[4] ;
	int number , computer ;
	int i , j , k , l , num , judge = 1 , flag = 0 ;

	scanf("%d %d" , &number , &computer ) ;
	in = fopen("in.txt" , "r") ;

	for( i = 0 ; i < number ; i++ ) { //建立设备网
		fgets( line , MAXLINE , in ) ;
		if( i == 0 ) {
			a[0] = 0 , a[1] = 0 , a[2] = -1 , a[3] = -1 ;
			head = create_node() ;//根节点
			head->ID = a[0] ;
			head->type = a[1] ;
			head->father_ID = a[2] ;
			head->father_port = a[3] ;
			head->mark = 0 ;
			for( j = 0 ; j <= 8 ; j++ ) {
				head->port[j] = NULL ;
			}
		} else {
			for( l = 0 , k = 0 ; l < 4 ; l++ ) {
				for( num = 0 , judge = 0 ; line[k] != 0 ; k++ ) {
					if( line[k] >= '0' && line[k] <= '9' ) {
						num = num*10 + line[k] - '0' ;
						judge = 1 ;
					}
					if( !(line[k] >= '0' && line[k] <= '9') && judge == 1 ) {
						break ;
					}
				}
				a[l] = num ;
			}
			insert( head , a[0] , a[1] , a[2] , a[3] ) ;
		}
	}

	visit_computer( head , computer ) ;//找 目标电脑

	visit_printer( head ) ;//找所有打印机

	for( i = plug ; i >= 0 ; i-- ) { //记录 打印机 与 电脑 距离
		clearing( head ) ;
		back_printer( printer[i] ) ;
		read = p->port[8] ;
		while( read->mark != 1 ) {
			printers[i]++ ;
			read = read->port[8] ;
		}
		while( read != printer[i] ) {
			printers[i]++ ;
			for( k = 0 ; k < 8 ; k++ ) {
				if( read->port[k] != NULL ) {
					if( read->port[k]->mark == 1 ) {
						read = read->port[k] ;
						break ;
					}
				}
			}
		}
	}

	for( i = plug , flag = plug ; i >= 1 ; i-- ) {
		if(printers[flag]>=printers[i]) {
			flag = i ;
		}
	}

	clearing( head ) ;

	printf("%d " , printer[flag]->ID ) ;

	back_printer( printer[flag] ) ;

	read = p->port[8] ;
	while( read->mark != 1 ) {
		printf("%d " , read->ID ) ;
		read = read->port[8] ;
	}

	while(read != printer[flag]) {
		printf("%d " ,read->ID ) ;
		for( i = 0 ; i < 8 ; i++ ) {
			if( read->port[i] != NULL ) {
				if( read->port[i]->mark == 1 ) {
					read = read->port[i] ;
					break ;
				}
			}
		}
	}

	return 0;
}
