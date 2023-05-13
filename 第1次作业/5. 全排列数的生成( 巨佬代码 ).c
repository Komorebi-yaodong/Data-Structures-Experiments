#include<stdio.h>
int N;
int i,j;
int jiecheng[11];
int output[10];

int factorial() {
	jiecheng[0]=1;
	int i;
	for(i=1; i<10; i++) {
		jiecheng[i]=i*jiecheng[i-1];
	}
}

void print() {
	int i=0;
	for(i=0; i<N-1; i++)
		printf("%d ",output[i]);
	printf("%d\n",output[i]);
}

void find() {
	for(i=N-2; i>=0; i--) {
		if(output[i]<output[i+1])
			break;
	}
	int k1=i;
	int temp_low=i+1;
	for(i=k1+1; i<N; i++) {
		if(output[i]>output[k1]&&output[i]<output[temp_low])
			temp_low=i;
	}
	int temp;
	temp=output[k1];
	output[k1]=output[temp_low];
	output[temp_low]=temp;
	for(j=k1+1,i=N-1; i>j; i--,j++) {
		temp=output[i];
		output[i]=output[j];
		output[j]=temp;
	}
}

int main() {
	factorial();
	scanf("%d",&N);
	int i;
	for(i=0; i<N; i++) {
		output[i]=i+1;
	}
	print();
	for(i=1; i<jiecheng[N]; i++) {
		find();
		print();
	}
}

