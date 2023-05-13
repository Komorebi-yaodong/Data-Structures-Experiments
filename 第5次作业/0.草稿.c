#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
typedef struct TreeNode {  //���Ľṹ��
	char val[200];
	int times;
	struct TreeNode *left;
	struct TreeNode *right;
} Tree,*Treep;

void VISIT(Treep t);       //�������ڵ������
void inorder(Treep t);     //�������
void insertBST(Treep *t,char *num); //�������������BST(��������Ǵ���struct TreeNode**)

void GetArticle(FILE *fp1);  //��ȡ����
void GetWord();     //��ȡ����

char s[2000000],tmp[200],ch;
int i,j,k;
Treep root=NULL;


int main() {
	FILE *fp1 = fopen("article.txt","r");
	GetArticle(fp1);
	GetWord();
	if(root->right->right->val!=NULL)  //������ĿҪ�����BST������
		printf("%s %s %s\n",root->val,root->right->val,root->right->right->val);
	else if(root->right->val!=NULL)
		printf("%s %s\n",root->val,root->right->val);
	else
		printf("%s\n",root->val);
	inorder(root);
	return 0;
}
void VISIT(Treep t) {
	printf("%s %d\n",t->val,t->times); //���ʵ��ʺʹ���
}
void inorder(Treep t) { //�������
	if(t!=NULL) {
		inorder(t->left);
		VISIT(t);
		inorder(t->right);
	}
}
void insertBST(Treep *t,char *num) { //����BST
	if(*t==NULL) { //����ڵ�Ϊ�գ�����ڵ�
		*t=(Treep)malloc(sizeof(Tree));
		strcpy((*t)->val,num);
		(*t)->times=1;
		(*t)->left=NULL;
		(*t)->right=NULL;
	} else if(strcmp((*t)->val,num)>0) { //�ֵ�������
		insertBST(&((*t)->left),num);
	} else if(strcmp((*t)->val,num)<0) {	//�ֵ�������
		insertBST(&((*t)->right),num);
	} else if(strcmp((*t)->val,num)==0) { //��ͬ���������
		(*t)->times++;
	}
}
void GetArticle(FILE *fp1) { //������
	ch=fgetc(fp1);
	i=0;
	while(ch!=EOF) {
		if(isalpha(ch)) s[i]=tolower(ch);
		else s[i]=ch;
		i++;
		ch=fgetc(fp1);
	}
}
void GetWord() { //��ȡ����
	for(i=0; i<strlen(s); i++) {
		if(isalpha(s[i])) { //�ҵ����ʿ�ͷ
			for(j=i; j<strlen(s); j++) {
				if(!isalpha(s[j])) { //�ҵ����ʽ�β
					break;
				}
			}
			memset(tmp,0,sizeof(tmp));
			for(k=0; k<j-i; k++) {
				tmp[k]=s[i+k]; //tmp�洢���ǵ���;
			}
			insertBST(&root,tmp); //ͨ�����ڵ㹹��BST
			i=j;
		} else	continue;
	}
}
