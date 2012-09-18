/*测试sizeof运算符  2011.10.1*/

#include <iostream>
using namespace std;
//#pragma pack(4)    //设置4字节对齐 
//#pragma pack()     //取消4字节对齐 

typedef struct node
{

}S;

typedef struct node1
{
	int a;
	char b;
	short c;
}S1;

typedef struct node2
{
	char a;
	int b;
	short c;
}S2;

typedef struct node3
{
	int a;
	short b;
	static int c;
}S3;

typedef struct node4
{
	bool a;
	S1 s1;
	short b;
}S4;

typedef struct node5
{
	bool a;
	S1 s1;
	double b;
	int c;
}S5;

typedef struct node6
{
	bool a;
	S1 s1;
	int b;
	double c;
}S6;

int main(int argc, char *argv[])
{
	cout<<sizeof(char)<<" "<<sizeof(short)<<" "<<sizeof(int)<<" "<<sizeof(float)<<" "<<sizeof(double)<<endl;
	S s;
	S1 s1;
	S2 s2;
	S3 s3;
	S4 s4;
	S5 s5;
	S6 s6;
	cout<<sizeof(s)<<" "<<sizeof(s1)<<" "<<sizeof(s2)<<" "<<sizeof(s3)<<" "<<sizeof(s4)<<" "<<sizeof(s5)<<" "<<sizeof(s6)<<endl;
	system("pause");
	return 0;
}

/*
1 2 4 4 8
	1 8 12 8 16 32 24
	请按任意键继续. . .*/
