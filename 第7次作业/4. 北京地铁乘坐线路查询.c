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
#define MAXNUM 520
#define MAXLEN 22
#define Infinity 32767

struct Station{
	char sname[MAXLEN] ; //车站名 
	int is_change ; //是否换乘站 
};
struct Weight{
	int weight ; //两站之间的权重
	int  line_number ; //两个顶点坐在的线路号 
};
struct Station BGstation[MAXNUM] ;
struct Weight BGside[MAXNUM][MAXNUM] ;
int Vnum = 0 ;// 实际地铁总站数
int Small_weight[MAXNUM] ;
int Spath[MAXNUM] ;
int Weight_found[MAXNUM] ; 

void Dijkstra( int v0 ){
	int i , j , v , minweight ;
	for( i = 0 ; i < Vnum ; i++ ){
		Small_weight[i] = BGside[v0][i].weight ;
		Spath[i] = v0 ;
	}
	Weight_found[v0] = 1 ;
	Small_weight[v0] = 0 ;
	for( i = 0 ; i < Vnum - 1 ; i++ ){
		minweight = Infinity ;
		for( j = 0 ; j < Vnum ; j++ ){
			if( !Weight_found[j] && (Small_weight[j] < minweight) ){
				v = j ;
				minweight = Small_weight[v] ;
			}
		}
		Weight_found[v] = 1 ; 

		for( j = 0 ; j < Vnum ; j++ ){
			if( !Weight_found[j] && ( BGside[v][j].weight + minweight < Small_weight[j]) ){
				Small_weight[j] =  BGside[v][j].weight + minweight ;
				Spath[j] = v ;
			}
		}
	}
}

int add_station( struct Station station ){
	int i ;
	for( i = 0 ; i < Vnum ; i++ ){
		if( strcmp(BGstation[i].sname , station.sname) == 0 ){
			break ;
		}
	}
	if( i != Vnum ){
		return i ;
	}
	else{
		Vnum++ ;
		strcpy(BGstation[i].sname , station.sname) ;
		BGstation[i].is_change = station.is_change ;
		return i ;
	}
}
int main(){

	FILE *in ;
	struct Station st ;
	int total_line , line , line_station ;
	char begin[MAXLEN] , end[MAXLEN] ;
	int v1 , v2 , v_begin , v_end ;
    int i , j , k ;
    int stack[MAXNUM] ;
    int tail = -1 , v_now = 0 ;
    int count = 0 ;
    int judge ;
    
	in = fopen("bgstations.txt","r") ;
	
	fscanf( in , "%d" , &total_line ) ;
	for( i = 0 ; i < total_line ; i++ ){
		fscanf( in , "%d %d" , &line , &line_station ) ;
		for( j = 0 , v1 = v2 = -1 ; j < line_station ; j++ ){
			fscanf( in , "%s %d" , st.sname , &st.is_change ) ;
			v2 = add_station( st ) ;
			if( v1 != -1 ){
				BGside[v1][v2].weight = BGside[v2][v1].weight = 1 ;
				BGside[v1][v2].line_number = BGside[v2][v1].line_number = line ;
			}
			v1 = v2 ;
		}
	}
		
	scanf("%s %s" , begin , end ) ;
	for( i = 0 ; i < Vnum ; i++ ){
		if( strcmp(BGstation[i].sname , begin) == 0 ){
			v_begin = i ;
		}
		if( strcmp(BGstation[i].sname , end) == 0 ){
			v_end = i ;
		}
	}
	
	for( i = 0 ; i < Vnum ; i++ ){
		for( j = 0 ; j < Vnum ; j++ ){
			if( BGside[i][j].weight == 0 && i != j ){
				BGside[i][j].weight = Infinity ;
			}
		}
	}
	
	Dijkstra( v_begin ) ; // v_begin
	v_now = v_end ;
	
	while( v_now != v_begin ){
		stack[++tail] = v_now ;
		v_now = Spath[v_now] ;
	}
	
	stack[++tail] = v_now ;

	
	for( i = tail , count = 0 , judge = BGside[stack[i]][stack[i-1]].line_number ; i > 0 ; i-- , count++ ){
		if( stack[i] == v_begin ){
			printf("%s-%d" , BGstation[stack[i]].sname , BGside[stack[i]][stack[i-1]].line_number ) ;
		}
		else if( BGside[stack[i]][stack[i-1]].line_number != judge ){
			printf("(%d)-%s-%d" , count , BGstation[stack[i]].sname , BGside[stack[i]][stack[i-1]].line_number ) ;
			count = 0 ;
			judge = BGside[stack[i]][stack[i-1]].line_number ;
		}
	}
	printf("(%d)-%s" , count , BGstation[stack[0]].sname ) ;
	
	fclose(in) ;
	
	return 0;
}

