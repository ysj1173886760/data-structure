#include<stdio.h>

union data		//������  ����һ���ڴ� 
{
	int a;
	float b;
}jj;

int binary[100];

int main()
{
	jj.b=2.3;
	char x[4];
	x[0]=jj.a;	//ǿ������ת������ȥ��λ�� 
	x[1]=jj.a>>8;
	x[2]=jj.a>>16;
	x[3]=jj.a>>24;
	int now=0;
	for(int i=3;i>=0;i--)printf("%d ",x[i]);
    return 0;
}
10000000 00010011 00110011 00110011
