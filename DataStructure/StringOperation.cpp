#include <iostream>
#include <string>
#include "Definition.h"
#define Max_Len 10

using namespace std;
int Next[Max_Len];

typedef struct{
	char * ch;
	int length;
}HString;



char* strrev1(const char* str){
	if(str==NULL) return NULL;
	int len=strlen(str);
	char* p=new char[len+1];
	strcpy(p, str);
	char tmp;
	for(int i=0;i<len/2;i++){
		tmp=p[i];
		p[i]=p[len-1-i];
		p[len-1-i]=tmp;
	}
	return p;
}
//不用中间变量
char* strrev2(const char* str){
	if(str==NULL) return NULL;
	int len=strlen(str);
	char* p=new char[len+1];
	strcpy(p, str);
	char* ret=p;
	char* t = ret + len - 1;

	while(p<t){
		*p =*p+*t;
		*t=*p-*t;
		*p=*p-*t;
		
		p++;
		t--;
	}
	return ret;
}

char* strrev3(const char* str){
	if(str==NULL) return NULL;
	int len=strlen(str);
	char* p=new char[len+1];
	strcpy(p, str);
	char* ret=p;
	char* t = ret + len - 1;

	while(p<t){
		*p=*p^*t;
		*t=*p^*t;
		*p=*p^*t;

		p++;
		t--;
	}
	return ret;
}

//递归写法
char* strrev5(char* str, int len)//求s的逆串r
{
	if (len <= 1)
		return str;

	char t = *str;
	*str = *(str + len -1);
	*(str + len -1) = t;

	return (strrev5(str + 1,len - 2) - 1);
}

//字符串匹配
int Index(string S, string T, int pos){
	int len_S=S.length();
	int len_T=T.length();
	if(len_S<=0 || len_T<=0 || pos<0 ||pos >len_S-1) return ERROR;

	int i=pos, j=0, back;
	while(i<len_S-len_T+1 && j<len_T){
		if(S[i]==T[j]) {
			i++;j++;
		}
		else{
			i=i-j+1;	j=0;
		}
	}
	if(j==len_T){
		return i-j;
	}
	else{
		return FALSE;
	}
}

void get_next(string P,  int next[]){
	//求模式串P的next函数值并存入数组next中，i、j分别代表主串、模式串的下标
	int i = 0; int j = -1; next[0] = -1;
	while(i < (int)(P.size()-1)){
		if( j==-1 || P[i] == P[j] ) { ++i; ++j; next[i] = j; }//每当自增i和j，得到一个新的next[i]
		else j = next[j];//模式串向右移动
	}
}

void get_nextval(string P,  int nextval[]){
	//求模式串P的next函数修正值并存入数组nextval
	int i = 0; int j = -1; nextval[0] = -1;
	while(i < (int)(P.size()-1)){
		if(j == -1 || P[i] == P[j]){
			++i; ++j;
			if(P[i]!=P[j]){nextval[i]=j;}//下次比较不相等，nextval[i]取j
			else nextval[i] = nextval[j];//下次比较仍然相等，nextval[i]取j的下一个nextval[j]
		}
		else j=nextval[j];
	}
} 

int Index_KMP(string S, string P, int pos){  
	//利用模式串P的next函数求P在主串S中第pos个字符之后的位置的KMP算法。
	//其中，P非空，0<=pos<StrLength(S)。  
	int i = pos; int j = 0;  
	while(i < (int)(S.size()) && j < (int)(P.size())){//注意j为int，size()为unsigned int，系统自动将int转换为unsigned int，将-1转换为unsigned int 时将会变为与-1同样补码的无符号数，32位机上为2^32-1
		if(j == -1 || S[i] == P[j]) { ++i; ++j; }//继续比较后继字符
		else   j = Next[j];//模式串象右滑动
	}  
	if(j == P.size())   return  i - P.size();//匹配成功
	else  return  0;  
}//Index_KMP


void main(){
	/*
	char *A=new char[10];//堆上分配空间
	gets(A);
	int len=strlen(A);
	cout<<strrev5(A, len)<<endl;
	*/
//////////////////////////////////////////////////////////////////////////
	/*
	while (1)
	{
		string A;//栈上分配空间
		cout<<"请输入主串："<<endl;
		cin>>A;
	

		string B;
		cout<<"请输入模式串："<<endl;
		cin>>B;
	
		int pos;
		cout<<"请输入主串起始位置："<<endl;
		cin>>pos;
	
		cout<<Index(A, B, pos)<<endl;
	
		system("pause");
	}
	*/

	//////////////////////////////////////////////////////////////////////////

	while (1)
	{
		int POS;
		string Pattern, To_Match;
		cout<<"请输入模式串："<<endl;
		cin>>Pattern;
		get_next(Pattern, Next);
		for(int i=0;i<Max_Len;i++){
			cout<<Next[i]<<" ";
		}

		cout<<endl;
		cout<<"请输入主串："<<endl;
		cin>>To_Match;
		cout<<"请输入主串起始位置："<<endl;
		cin>>POS;
		cout<<Index_KMP(To_Match, Pattern, POS)<<endl;
		system("pause");
	}
}