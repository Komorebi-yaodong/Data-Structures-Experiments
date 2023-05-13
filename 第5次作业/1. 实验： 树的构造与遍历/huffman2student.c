//�ļ�ѹ��-Huffmanʵ��
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode {					//Huffman���ṹ
	char c;		
	int weight;					//���ڵ�Ȩ�أ�Ҷ�ڵ�Ϊ�ַ������ĳ��ִ���
	struct tnode *left,*right;
} ; 
int Ccount[128]={0};			//���ÿ���ַ��ĳ��ִ�������Ccount[i]��ʾASCIIֵΪi���ַ����ִ��� 
struct tnode *Root=NULL; 		//Huffman���ĸ��ڵ�
char HCode[128][MAXSIZE]={{0}}; //�ַ���Huffman���룬��HCode['a']Ϊ�ַ�a��Huffman���루�ַ�����ʽ�� 
int Step=0;						//ʵ�鲽�� 
FILE *Src, *Obj;
	
void statCount();				//����1��ͳ���ļ����ַ�Ƶ��
void createHTree();				//����2������һ��Huffman�������ڵ�ΪRoot 
void makeHCode();				//����3������Huffman������Huffman����
void atoHZIP(); 				//����4������Huffman���뽫ָ��ASCII���ı��ļ�ת����Huffman���ļ�

void print1();					//�������1�Ľ��
void print2(struct tnode *p);	//�������2�Ľ�� 
void print3();					//�������3�Ľ��
void print4();					//�������4�Ľ��

int main()
{
	if((Src=fopen("input.txt","r"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "input.txt");
		return 1;
	}
	if((Obj=fopen("output.txt","w"))==NULL) {
		fprintf(stderr, "%s open failed!\n", "output.txt");
		return 1;
	}
	scanf("%d",&Step);					//���뵱ǰʵ�鲽�� 
	
	statCount();						//ʵ�鲽��1��ͳ���ļ����ַ����ִ�����Ƶ�ʣ�
	(Step==1) ? print1(): 1; 			//���ʵ�鲽��1���	
	createHTree();						//ʵ�鲽��2�������ַ�Ƶ��������Ӧ��Huffman��
	(Step==2) ? print2(Root): 2; 		//���ʵ�鲽��2���	
	makeHCode();				   		//ʵ�鲽��3������RootΪ���ĸ���Huffman��������ӦHuffman����
	(Step==3) ? print3(): 3; 			//���ʵ�鲽��3���
	(Step>=4) ? atoHZIP(),print4(): 4; 	//ʵ�鲽��4����Huffman��������ѹ���ļ��������ʵ�鲽��4���	

	fclose(Src);
	fclose(Obj);

    return 0;
} 

//��ʵ�鲽��1����ʼ 

void statCount()
{
	char c = '1' ;
	Ccount[0] = 1 ;
	while( (c = fgetc(Src)) != EOF ){
		if( c != '\n' ){
			Ccount[c]++ ;
		}
		else{
			continue ;
		}
	}
}

//��ʵ�鲽��1������

//��ʵ�鲽��2����ʼ
struct tnode *create_tree( char alp , int weigh ){
	struct tnode *p ;
	p = (struct tnode *)malloc(sizeof(struct tnode));
	p->c = alp; 
	p->weight = weigh ;	
	p->left = p->right = NULL;
	
	return p ;
} 
void sort( struct tnode *point[] , int Head , int Tail ){/*       */
	struct tnode *term ;
	int i , j ;
	for( i = Head ; i <= Tail ; i++ ){
		for( j = Tail ; j > i ; j-- ){
			if( point[j]->weight < point[j-1]->weight ){
				term = point[j] ;
				point[j] = point[j-1] ;
				point[j-1] = term ;
			}
			else if( point[j]->weight == point[j-1]->weight && point[j]->c != -1 && point[j-1]->c != -1 && (point[j-1]->c > point[j]->c)){
				term = point[j] ;
				point[j] = point[j-1] ;
				point[j-1] = term ;
			}
		}
	}
}

void createHTree()
{
	struct tnode *F[100000] , *p1 , *p2 , *p0 ;
	int  i , head = 0 , tail = -1 , count = 0 ;
	for( i = 0 ; i < 128  ; i++ ){
		if( Ccount[i] > 0 ){
			F[++tail] = create_tree( i , Ccount[i] ) ;
		}
	}
	while(  tail - head + 1 > 1 ){
		sort( F , head , tail ) ;
		p1 = F[head] ;
		p2 = F[head+1] ;
		p0 = create_tree( -1 , F[head]->weight + F[head+1]->weight ) ;
		p0->left = p1; 
		p0->right = p2 ;
		F[++tail] = p0;
		head = head + 2 ;
	}
	Root = F[head] ;
}

//��ʵ�鲽��2������

//��ʵ�鲽��3����ʼ

void visit( struct tnode *point , char line[] , int i ){
	if( point->left == NULL && point->right == NULL ){
		line[++i] = 0 ; 
		strcpy( HCode[point->c] , line ); 
		i-- ;
	}
	if( point->left != NULL ){
		line[++i] = '0' ;
		visit( point->left , line , i ) ;
		line[i] = 0 ;
		i-- ;
	}
	if( point->right != NULL ){
		line[++i] = '1' ;
		visit( point->right , line , i ) ;
		line[i] = 0 ;
		i-- ;
	}
}

void makeHCode()
{
	char line[MAXSIZE] ;
	visit( Root , line , -1 ) ;
} 

//��ʵ�鲽��3������

//��ʵ�鲽��4����ʼ

void clearing( char str[] ){
	int i ;
	for( i = 0 ; str[i] != 0 ; i++ ){
		str[i] = 0 ;
	}
}

void atoHZIP()
{
	char s[100000] = {0} , term[100000] = {0} ;
	char file_c ;
	int hc , i , j , k1 , k2 ;
	
	fclose(Src) ;
	Src=fopen("input.txt","r") ;
	clearing(s) ;
	clearing(term) ;
	
	while( (file_c = fgetc(Src)) != EOF ){
		k2 = strlen(term) ;
		if( k2 > 0 ){
			clearing( s ) ;
			strcpy( s , term ) ;
			clearing( term ) ;
		}
		strcat( s , HCode[file_c] ) ; 
		k1 = strlen(s) ;
		if( k1 < 8 ){
			continue ;
		}
		else if( k1 > 8 ){
			for( i = 8 , j = 0 ; s[i] != 0 ; i++ , j++ ){
				term[j] = s[i] ;
				s[i] = 0 ;
			}
			term[j] = 0 ;
		}
		for( i = 0 , hc = 0 ; s[i] != 0 ; i++ ){
			hc = (hc<<1)|( s[i] - '0' ) ;
			if( (i+1)%8 == 0 ){
				fputc( hc , Obj ) ;
				printf("%x" , hc ) ;
				hc = 0 ;
			}
		}
		clearing(s) ;
	}
	k1 = strlen(s) ;
	k2 = strlen(term) ;
	if( k2 > 0 || k1 > 0 ){
		if( k2 > 0 ){
			strcat(term , HCode[0] ) ;
			strcpy( s , term ) ;
		}
		for( i = 0 ; s[i] != 0 ; i++ );
		for( ; (i+1) % 8 != 0 ; i++ ){
			s[i] = '0' ;
		} 
		for( i = 0 ; s[i] != 0 ; i++ ){
			hc = (hc<<1)|( s[i] - '0' ) ;
			if( (i+1)%8 == 0 ){
				fputc( hc , Obj ) ;
				printf("%x" , hc ) ;
				hc = 0 ;
			}
		}
	}
	else{
		strcpy(s,HCode[0]) ;
		for( i = 0 ; s[i] != 0 ; i++ ){
			hc = (hc<<1)|( s[i] - '0' ) ;
			if( (i+1)%8 == 0 ){
				fputc( hc , Obj ) ;
				printf("%x" , hc ) ;
				hc = 0 ;
			}
		}
	}
}

//��ʵ�鲽��4������

void print1()
{
	int i;
	printf("NUL:1\n");
	for(i=1; i<128; i++)
		if(Ccount[i] > 0)
			printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
	if(p != NULL){
		if((p->left==NULL)&&(p->right==NULL)) 
			switch(p->c){
				case 0: printf("NUL ");break;
				case ' ':  printf("SP ");break;
				case '\t': printf("TAB ");break;
				case '\n':  printf("CR ");break;
				default: printf("%c ",p->c); break;
			}
		print2(p->left);
		print2(p->right);
	}
}

void print3()
{
	int i;
	
	for(i=0; i<128; i++){
		if(HCode[i][0] != 0){
			switch(i){
				case 0: printf("NUL:");break;
				case ' ':  printf("SP:");break;
				case '\t': printf("TAB:");break;
				case '\n':  printf("CR:");break;
				default: printf("%c:",i); break;
			}
			printf("%s\n",HCode[i]);
		}
	}
} 

void print4()
{
	long int in_size, out_size;
	
	fseek(Src,0,SEEK_END);
	fseek(Obj,0,SEEK_END);
	in_size = ftell(Src);
	out_size = ftell(Obj);
	
	printf("\nԭ�ļ���С��%ldB\n",in_size);
	printf("ѹ�����ļ���С��%ldB\n",out_size);
	printf("ѹ���ʣ�%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
