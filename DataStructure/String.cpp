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
//�����м����
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

//�ݹ�д��
char* strrev5(char* str, int len)//��s���洮r
{
	if (len <= 1)
		return str;

	char t = *str;
	*str = *(str + len -1);
	*(str + len -1) = t;

	return (strrev5(str + 1,len - 2) - 1);
}

//�ַ���ƥ��
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
	//��ģʽ��P��next����ֵ����������next�У�i��j�ֱ����������ģʽ�����±�
	int i = 0; int j = -1; next[0] = -1;
	while(i < (int)(P.size()-1)){
		if( j==-1 || P[i] == P[j] ) { ++i; ++j; next[i] = j; }//ÿ������i��j���õ�һ���µ�next[i]
		else j = next[j];//ģʽ�������ƶ�
	}
}

void get_nextval(string P,  int nextval[]){
	//��ģʽ��P��next��������ֵ����������nextval
	int i = 0; int j = -1; nextval[0] = -1;
	while(i < (int)(P.size()-1)){
		if(j == -1 || P[i] == P[j]){
			++i; ++j;
			if(P[i]!=P[j]){nextval[i]=j;}//�´αȽϲ���ȣ�nextval[i]ȡj
			else nextval[i] = nextval[j];//�´αȽ���Ȼ��ȣ�nextval[i]ȡj����һ��nextval[j]
		}
		else j=nextval[j];
	}
} 

int Index_KMP(string S, string P, int pos){  
	//����ģʽ��P��next������P������S�е�pos���ַ�֮���λ�õ�KMP�㷨��
	//���У�P�ǿգ�0<=pos<StrLength(S)��  
	int i = pos; int j = 0;  
	while(i < (int)(S.size()) && j < (int)(P.size())){//ע��jΪint��size()Ϊunsigned int��ϵͳ�Զ���intת��Ϊunsigned int����-1ת��Ϊunsigned int ʱ�����Ϊ��-1ͬ��������޷�������32λ����Ϊ2^32-1
		if(j == -1 || S[i] == P[j]) { ++i; ++j; }//�����ȽϺ���ַ�
		else   j = Next[j];//ģʽ�����һ���
	}  
	if(j == P.size())   return  i - P.size();//ƥ��ɹ�
	else  return  0;  
}//Index_KMP


void main(){
	/*
	char *A=new char[10];//���Ϸ���ռ�
	gets(A);
	int len=strlen(A);
	cout<<strrev5(A, len)<<endl;
	*/
//////////////////////////////////////////////////////////////////////////
	/*
	while (1)
	{
		string A;//ջ�Ϸ���ռ�
		cout<<"������������"<<endl;
		cin>>A;
	

		string B;
		cout<<"������ģʽ����"<<endl;
		cin>>B;
	
		int pos;
		cout<<"������������ʼλ�ã�"<<endl;
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
		cout<<"������ģʽ����"<<endl;
		cin>>Pattern;
		get_next(Pattern, Next);
		for(int i=0;i<Max_Len;i++){
			cout<<Next[i]<<" ";
		}

		cout<<endl;
		cout<<"������������"<<endl;
		cin>>To_Match;
		cout<<"������������ʼλ�ã�"<<endl;
		cin>>POS;
		cout<<Index_KMP(To_Match, Pattern, POS)<<endl;
		system("pause");
	}
}