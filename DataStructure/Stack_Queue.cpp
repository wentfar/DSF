#include <iostream>
#include "Definition.h"
#include <ctype.h>

using namespace std;

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10//վ��ʱ����
#define N 20
#define MAXQSIZE 100

typedef char QElemType;
typedef char SElemType;

typedef struct{
	SElemType * base;//����ջ��ָ�룬ָ�����ռ��׵�ַ
	SElemType * top;
	int stacksize;
}SqStack;

typedef struct{
	float * base;//����ջ��ָ�룬ָ�����ռ��׵�ַ
	float * top;
	int stacksize;
}SqStack_float;


//��ʼ��һ����ջ��char��
Status InitStack(SqStack &s){
	s.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!s.base) exit(OVERFLOW);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return OK;
}
//��ʼ��һ����ջ��float��
Status InitStack(SqStack_float &s){
	s.base=(float *)malloc(STACK_INIT_SIZE*sizeof(float));
	if(!s.base) exit(OVERFLOW);
	s.top=s.base;
	s.stacksize=STACK_INIT_SIZE;
	return OK;
}


Status Push(SqStack &s, SElemType e){
	if(s.top-s.base>=s.stacksize){
		s.base=(SElemType*)realloc(s.base, (s.stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!s.base) exit(OVERFLOW);
		s.top=s.base+s.stacksize;
		s.stacksize+=STACKINCREMENT;
	}
	*s.top++=e;//���ȼ�'.'>'*','*'='++'
	return OK;
}
Status Push(SqStack_float &s, float e){
	if(s.top-s.base>=s.stacksize){
		s.base=(float*)realloc(s.base, (s.stacksize+STACKINCREMENT)*sizeof(float));
		if(!s.base) exit(OVERFLOW);
		s.top=s.base+s.stacksize;
		s.stacksize+=STACKINCREMENT;
	}
	*s.top++=e;//���ȼ�'.'>'*','*'='++'
	return OK;
}

Status Pop(SqStack &s, SElemType &e){
	if(s.top==s.base) return ERROR;
	e=*--s.top;
	return OK;
}
Status Pop(SqStack_float &s, float &e){
	if(s.top==s.base) return ERROR;
	e=*--s.top;
	return OK;
}

Status Pop(SqStack &s){
	if(s.top==s.base) return ERROR;
	--s.top;
	return OK;
}
Status Pop(SqStack_float &s){
	if(s.top==s.base) return ERROR;
	--s.top;
	return OK;
}

Status StackTraverse(SqStack s){
	if(s.base==NULL) return ERROR;
	SElemType *p=s.base;
	while(p!=s.top){
		cout<<*p<<" ";
		++p;
	}
	cout<<endl;
	return OK;
}

Status StackEmpty(SqStack s){
	if(s.base==NULL) exit(OVERFLOW);
	else if(s.base==s.top) return TRUE;
	else return FALSE;
}
Status StackEmpty(SqStack_float s){
	if(s.base==NULL) exit(OVERFLOW);
	else if(s.base==s.top) return TRUE;
	else return FALSE;
}


SElemType GetTop(SqStack s){
	if(s.base==NULL || s.base==s.top) return ERROR;
	return *(s.top-1);
}
float GetTop(SqStack_float s){
	if(s.base==NULL || s.base==s.top) return ERROR;
	return *(s.top-1);
}


//3.17�ж�������ַ�����'&'ǰ��'&'�󲿷��Ƿ�Ϊ�洮,���򷵻�1,���򷵻�0
int IsReverse(){
	SqStack s;
	InitStack(s);
	cout<<"������ǰ�벿���ַ�����&��Ϊ������:"<<endl;
	char e_l=' ';
	while ((e_l=getchar())!='&'){
		Push(s, e_l);
	}

	while(getchar()!='\n');

	cout<<"�������벿���ַ�����@��Ϊ������:"<<endl;
	char e_r=' ', e=' ';
	while((e_r=getchar())!='@'){
		if(StackEmpty(s)) return 0;
		Pop(s, e);
		if(e_r!=e) return 0;
	}
	if(!StackEmpty(s)) return 0;
	return 1;
}

////3.19�б���ʽ�����������Ƿ�ƥ�䣬����ʹ�ö���
Status AllBrackets_Test(char *str){
	SqStack s;
	InitStack(s);
	char *p=str, q=' ';
	while(*p){
		if(*p=='{' || *p=='[' || *p=='('){
			Push(s, *p);
		}
		else if(*p=='}' || *p==']' || *p==')'){
			if(StackEmpty(s)) return 0;
			Pop(s,q);
			if(*p=='}' && q!='{') return 0;
			if(*p==']' && q!='[') return 0;
			if(*p==')' && q!='(') return 0;
		}
		p++;
	}
	if(!StackEmpty(s)) return 0;
	return 1;
}

int In(char c)//�ж϶�����ַ��Ƿ�Ϊ������������Ƿ���1�������򷵻�0
{
	if((c>='0'&&c<='9') || c=='.') return 0;
	else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#') return 1;
	else
	{
		printf("ERROR!\n");
		return 2;
	}
}


int Precede(char a,char b)//�Ƚϲ�����a��b�����ȼ���a�����ȼ���b�߷���1��a�����ȼ���b�ͷ���0��a��bͬ������2�����ɱȽϷ���3(���Ⱥ�˳��֮��)
{
	switch(a)
	{
	case '+':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '-':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '*':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 1;
			case '/':return 1;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '/':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 1;
			case '/':return 1;
			case '(':return 0;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '(':
		{
			switch(b)
			{
			case '+':return 0;
			case '-':return 0;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 2;
			case '#':return 3;
			}
		}
	case ')':
		{
			switch(b)
			{
			case '+':return 1;
			case '-':return 1;
			case '*':return 1;
			case '/':return 1;
			case '(':return 3;
			case ')':return 1;
			case '#':return 1;
			}
		}
	case '#':
		{
			switch(b)
			{
			case '+':return 0;
			case '-':return 0;
			case '*':return 0;
			case '/':return 0;
			case '(':return 0;
			case ')':return 3;
			case '#':return 2;
			}
		}
	}

}

float Operate(float a,char theta,float b)//�������㡣
{
	float c;
	switch(theta)
	{
	case '+':c=a+b;break;
	case '-':c=a-b;break;
	case '*':c=a*b;break;
	case '/':
		{
			if(b==0)
			{
				printf("\n��ĸΪ�㣬������ֹ��\n");
				return (b);
			}
			else
			{
				c=a/b;
				break;
			}
		}
	}
	return (c);
}

//����׺���ʽstrת�����沨��ʽnew
void NiBoLan(char *str, char *new_str){
	SqStack s;
	char temp=' ';
	char *p=str;
	char *q=new_str;
	InitStack(s);//������ջ��Խ��ջ�����ȼ�Խ�ߵ�ԭ��
	Push(s, '#');

	while(*p){
		if (In(*p)==0){//��������ֻ���С����
			*q=*p;
			q++;
			p++;
			if(*p && In(*p)==1) *q++='|';//����ַ����пո����(��ͬ)
		}
		else if(In(*p)==1){//����������
			switch(Precede(GetTop(s), *p)){
			case 0:	Push(s, *p);//*p�����ȼ��ߣ���*p��ջ����ȡһ���ַ�
					p++;
					break;
			case 1:	do{
						Pop(s, temp);
						*q++=temp;
						*q++='|';
					}while(Precede(GetTop(s), *p)==1);//*p�����ȼ��ͣ������˴�ѭ��ʱ��p���䣬����ִ��while��
					break;
			case 2: Pop(s);//���ȼ���ȣ�����������������������������ע�⣺��������û�н�ջ��
					p++;
					break;
			case 3:	
			default: printf("\nERROR!\n");break;
			}
		}
		else{
			printf("\nERROR!\n");break;
		}
	}

	if(*(--p)!=')' && GetTop(s)!='#') *q++='|';

	while(GetTop(s)!='#') {//��ջ��ʣ���������������빤�������С�
		Pop(s, temp);
		*q++=temp;
		*q++='|';
	}

	//����ĩβ�ַ���
	--q;
	if(*q=='|') *q='\0';
	else *(++q)='\0';

}

//3.22
float GetValue_NiBoLan(char *str)//���沨��ʽ��ֵ���沨��ʽ����Ԫ��֮���ԡ�|���ָ���
{	
	SqStack_float s;
	InitStack(s);
	char *p=(char*)malloc(2*N*sizeof(char));
	strcpy(p, str);
	const char *delim="|"; 
	char *q;
	float a, b, last;
	q=strtok(p, delim);
	while(q){
		if(In(*q)!=1){
			Push(s, atof(q));
		}
		else if(In(*q)==1){//����ǲ���������ջ�����㣬��ջ
			Pop(s, a);
			Pop(s, b);
			last=Operate(b, *q, a);//ע��˳��
			Push(s, last);
		}
		q=strtok(NULL, delim);
	}
	Pop(s, last);
	return last;
}

//////////////////////////////////////////////////////////////////////////

typedef struct QNode{
	QElemType data;
	struct QNode * next;
}QNode, *QueuePtr;

typedef struct{
	QueuePtr front;//��ͷ
	QueuePtr rear;//��β
}LinkQueue;

//��ʼ����ʽ����Q
void InitQueue(LinkQueue &lq){
	lq.front=lq.rear=(QueuePtr)malloc(sizeof(QNode));//ֻ��ʼ������ͷ
	if(!lq.front) exit(OVERFLOW);
	lq.front->next=NULL;
}

//ɾ������(�Ӷ�ͷ֮ǰ��lq.front��ʼɾ��)
Status DetroryQueue(LinkQueue &lq){
	while(lq.front){
		lq.rear=lq.front->next;//�ݴ�
		free(lq.front);
		lq.front=lq.rear;
	}
	return OK;
}

//��β����
Status EnQueue(LinkQueue &lq, QElemType e){
	QueuePtr p_qn=(QueuePtr)malloc(sizeof(QNode));
	if(!p_qn) exit(OVERFLOW);
	p_qn->data=e;	p_qn->next=NULL;
	lq.rear->next=p_qn;	lq.rear=p_qn;
	return OK;
}
//��ͷȥ��
Status DeQueue(LinkQueue &lq, QElemType &e){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;
	lq.front->next=p_qn->next;
	e=p_qn->data;
	if(lq.rear==p_qn) lq.rear=lq.front;//�������lq.front�⣬ֻ��һ��Ԫ�أ���ɾ������пգ���Ҫ�ı�lq.rear��ֵ
	free(p_qn);
}
//����
Status QueueTraverse(LinkQueue lq){
	if(lq.front==lq.rear) return ERROR;
	QueuePtr p_qn=lq.front->next;//ָ�����ͷ
	while(p_qn){
		cout<<p_qn->data<<' ';
		p_qn=p_qn->next;
	}
	cout<<endl;
	return OK;
}
//////////////////////////////////////////////////////////////////////////
//˳��ѭ������

typedef struct{
	QElemType *base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue &sq){
	sq.base=(QElemType*)malloc(sizeof(QElemType)*MAXQSIZE);
	sq.front=sq.rear=0;
	return OK;
}

//���г���
int QueueLength(SqQueue sq){
	return (sq.rear-sq.front+MAXQSIZE)%MAXQSIZE;
}

//�����
Status EnQueue(SqQueue &sq, QElemType e){
	if((sq.rear+1)%MAXQSIZE==sq.front) return ERROR;//������
	sq.base[sq.rear]=e;
	sq.rear=(sq.rear+1)%MAXQSIZE;
	return OK;
}

//������
Status DeQueue(SqQueue &sq, QElemType &e){
	if(sq.rear==sq.front) return ERROR;//���п�
	e=sq.base[sq.front];
	sq.front=(sq.front+1)%MAXQSIZE;
}

//���п�
Status QueueEmpty(SqQueue sq){
	if(sq.rear==sq.front) return 1;//���п�
	else return 0;
}

//����
Status QueueTraverse(SqQueue sq){
	if(sq.front==sq.rear) return ERROR;//�ն���
	int i=sq.front;
	while(i!=sq.rear){
		cout<<sq.base[i]<<' ';
		i++;
		i=(i+MAXQSIZE)%MAXQSIZE;
	}
	cout<<endl;
	return OK;
}
//3.31
int Palindrome_Test()//�б�������ַ����Ƿ��������,���򷵻�1,���򷵻�0
{
	SqStack s;
	InitStack(s);
	SqQueue sq;
	InitQueue(sq);
	char e_stack;
	char e_queue;
	char *p=new char;
	while((*p=getchar())!='@'){
		Push(s, *p);
		EnQueue(sq, *p);
	}
	StackTraverse(s);
	QueueTraverse(sq);

	while(!StackEmpty(s)){
		Pop(s, e_stack);
		DeQueue(sq, e_queue);
		if(e_stack!=e_queue) return FALSE;
	}
	StackTraverse(s);
	QueueTraverse(sq);

	if(!QueueEmpty(sq)) return FALSE;
	delete p;
	return OK;
}

int main(){
	/*
	while (1){
		cout<<IsReverse();
		system("pause");
		while(getchar()!='\n');
	}
	*/

//////////////////////////////////////////////////////////////////////////

	/*
	//3.19
	while(1){
		char a[N];
		gets(a);
		cout<<AllBrackets_Test(a);
	}
	*/

//////////////////////////////////////////////////////////////////////////
	/*
	//3.21
	while(1){
		char a[N],b[2*N];
		cout<<"������������ʽa[N]:";
		gets(a);
		NiBoLan(a, b);
		cout<<"ת�����沨��ʽb[N]:";
		cout<<b<<endl;

		cout<<"ת�����沨��ʽb[N]��ֵΪ:";
		cout<<GetValue_NiBoLan(b)<<endl;
		system("pause");
	}
	*/

	//////////////////////////////////////////////////////////////////////////
	/*
	LinkQueue lq;
	InitQueue(lq);
	char x=' ';
	while (x!='@')
	{
		cin>>x;
		EnQueue(lq, x);
	}
	cout<<QueueTraverse(lq)<<endl;

	DeQueue(lq, x);
	cout<<QueueTraverse(lq)<<endl;

	while(lq.rear!=lq.front){
		DeQueue(lq, x);
	}
	cout<<QueueTraverse(lq)<<endl;

	system("pause");
	*/

	//////////////////////////////////////////////////////////////////////////
	/*
	while(1){
		cout<<Palindrome_Test()<<endl;
		system("pause");
	}
	*/

}