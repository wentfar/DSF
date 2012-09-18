#include "stdio.h" 
typedef struct
{ 
	char c; 
	int d; 
	short e; 

}A; 
typedef struct 
{ 
	char c; 
	__int64 d; 
	int e; 
	short f; 
	A g; 
	char h; 
	int i; 
}B; 
typedef struct
{ 
	char c; 
	__int64 d; 
	int e; 
	short f; 
	char g; 
	int h; 
	A i;
}C;


typedef struct node
{

}D;

int main() 
{
	int i1=sizeof(A); 
	int i2=sizeof(B); 
	int i3=sizeof(C); 
	int i4=sizeof(D);
	printf("i1:%d\ni2:%d\ni3:%d\ni4:%d\n",i1,i2,i3,i4);
	getchar();
} 