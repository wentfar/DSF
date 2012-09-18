#include <iostream>

#define MAXINT 200000000
#define ARRSIZE 100

using namespace std;

void main(){
	int n;
	int a[ARRSIZE];
	cout<<"请输入维数(n)：";
	cin>>n;

	if (n>ARRSIZE) exit(0);
	for (int i=0;i<n;i++){
		if (i==0) a[i]=2;
		else if (a[i-1]*i*2>MAXINT) exit(0);
		else a[i]=a[i-1]*(i+1)*2;
	}
	for (int i=0;i<n;i++){
		cout<<a[i]<<" ";
	}
}

/*
请输入维数(n)：8
	2 8 48 384 3840 46080 645120 10321920 请按任意键继续. . .*/
