#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
typedef struct TreeNode {  //树的结构体
	char val[200];
	int times;
	struct TreeNode *left;
	struct TreeNode *right;
} Tree,*Treep;

void VISIT(Treep t);       //访问树节点的内容
void inorder(Treep t);     //中序遍历
void insertBST(Treep *t,char *num); //构造二叉排序树BST(这个方法是传递struct TreeNode**)

void GetArticle(FILE *fp1);  //读取文章
void GetWord();     //获取单词

char s[2000000],tmp[200],ch;
int i,j,k;
Treep root=NULL;


int main() {
	FILE *fp1 = fopen("article.txt","r");
	GetArticle(fp1);
	GetWord();
	if(root->right->right->val!=NULL)  //按照题目要求输出BST的内容
		printf("%s %s %s\n",root->val,root->right->val,root->right->right->val);
	else if(root->right->val!=NULL)
		printf("%s %s\n",root->val,root->right->val);
	else
		printf("%s\n",root->val);
	inorder(root);
	return 0;
}
void VISIT(Treep t) {
	printf("%s %d\n",t->val,t->times); //访问单词和次数
}
void inorder(Treep t) { //中序遍历
	if(t!=NULL) {
		inorder(t->left);
		VISIT(t);
		inorder(t->right);
	}
}
void insertBST(Treep *t,char *num) { //构造BST
	if(*t==NULL) { //如果节点为空，构造节点
		*t=(Treep)malloc(sizeof(Tree));
		strcpy((*t)->val,num);
		(*t)->times=1;
		(*t)->left=NULL;
		(*t)->right=NULL;
	} else if(strcmp((*t)->val,num)>0) { //字典序排序
		insertBST(&((*t)->left),num);
	} else if(strcmp((*t)->val,num)<0) {	//字典序排序
		insertBST(&((*t)->right),num);
	} else if(strcmp((*t)->val,num)==0) { //相同则次数增加
		(*t)->times++;
	}
}
void GetArticle(FILE *fp1) { //读文章
	ch=fgetc(fp1);
	i=0;
	while(ch!=EOF) {
		if(isalpha(ch)) s[i]=tolower(ch);
		else s[i]=ch;
		i++;
		ch=fgetc(fp1);
	}
}
void GetWord() { //获取单词
	for(i=0; i<strlen(s); i++) {
		if(isalpha(s[i])) { //找到单词开头
			for(j=i; j<strlen(s); j++) {
				if(!isalpha(s[j])) { //找到单词结尾
					break;
				}
			}
			memset(tmp,0,sizeof(tmp));
			for(k=0; k<j-i; k++) {
				tmp[k]=s[i+k]; //tmp存储的是单词;
			}
			insertBST(&root,tmp); //通过根节点构造BST
			i=j;
		} else	continue;
	}
}
