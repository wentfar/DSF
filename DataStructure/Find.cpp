#include <iostream>
#include <string>
#include <iomanip>
#include "Definition.h"

#define COUNT_CHAR 10
#define SUCCESS 1  
#define UNSUCCESS 0  
#define DUPLICATE -1

#define NULLKEY 0//0Ϊ�޼�¼��־
using namespace std;


typedef int KeyType;

typedef struct ElemType{
	KeyType key_value;
	float weight;
/*	char name[COUNT_CHAR];*/
}ElemType;//��¼


typedef struct SSTable{
	ElemType *elem;
	int length;
}SSTable;//˳��洢�ṹ

typedef ElemType TElemType;

typedef struct BiNode{
	TElemType data;
	struct BiNode *lchild, *rchild;
}BiNode, *Bitree;


void Creat_Seq(SSTable &st, int n){
	st.elem=(ElemType*)malloc((n+1)*sizeof(ElemType));
	if(!st.elem) exit(1);
	st.length=n;
}

//ǰ�����
Status PreOrderTraverse(Bitree T){
	if(!T) return FALSE;
	else{
		cout<<T->data.key_value<<" ";
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

//�������
Status InOrderTraverse(Bitree T){
	if(!T) return FALSE;
	else{
		InOrderTraverse(T->lchild);
		cout<<T->data.key_value<<" ";
		InOrderTraverse(T->rchild);
	}
}

Status Assign_Seq(ElemType &e){
	cout<<"������key:";
	cin>>e.key_value;

	cout<<"������weight:";
	cin>>e.weight;

/*
	cout<<"������name:";
	cin>>e.name;*/


	return OK;
}
Status Printf_Seq(ElemType &e){
	cout<<e.key_value<<" "<<e.weight<<" "/*<<e.name*/<<endl;
	return OK;
}


void Traverse_Seq(SSTable st, Status (*visit)(ElemType&)){
	for(int i=1;i<=st.length;i++){
		if(!visit(st.elem[i]))
			exit(1);
	}
}

void Find_sw(SSTable st, float *sw){
	sw[0]=0.0;
	for(int i=1;i<=st.length;i++){
		sw[i]=sw[i-1]+st.elem[i].weight;
	}
}

//////////////////////////////////////////////////////////////////////////
//˳���Ĳ���
int Search_Seq(SSTable st, KeyType key){
	//�Ҳ����򷵻�0
	st.elem[0].key_value=key;
	int i=st.length;
	for( ;st.elem[i].key_value!=key;--i);
	return i;
}

//�����Ĳ��ң��۰���ң�
int Search_Bin(SSTable st, KeyType key){
	int low=1;
	int high=st.length;
	while(low<=high){
		int mid=(low+high)/2;
		if(st.elem[mid].key_value<key){low=mid+1;}
		else if(st.elem[mid].key_value>key){high=mid-1;}
		else return mid;
	}
	return 0;
}

//������Ų�����
void Second_Optimal(Bitree &T, ElemType R[], float sw[], int low, int high){
	int i=low;
	int _min=abs(sw[high]-sw[low]);//����ȡ��һ��ֵΪ��Сֵ

	int dw=sw[high]+sw[low-1];//deltaP��ǰ�벿��
	for(int j=low+1;j<=high;j++){
		if(_min>abs(dw-sw[j]-sw[j-1])) {
			_min=abs(dw-sw[j]-sw[j-1]);
			i=j;
		}
	}
	T=(Bitree)malloc(sizeof(BiNode));
	if(!T) exit(1);
	T->data=R[i];

	if(i==low) T->lchild=NULL;	
	else if(i>low) Second_Optimal(T->lchild, R, sw, low, i-1);//����������

	if(i==high) T->rchild=NULL;
	else if(i<high) Second_Optimal(T->rchild, R, sw, i+1, high);//����������
}

typedef Bitree SOSTree;
//�����������Ų�����
Status CreatSOSTree(SOSTree &T, SSTable st){
	float *sw=new float[st.length+1];
	if(st.length<=1){T=NULL;}
	else{
		Find_sw(st, sw);
		Second_Optimal(T, st.elem, sw, 1, st.length);
	}
	return OK;
}

//�ڸ�ָ����ָ�Ķ����������еݹ�Ĳ���ĳ�ؼ��ֵ���key������Ԫ�أ����ҳɹ�����ָ�룬ʧ���򷵻ؿ�ָ��
Bitree SearchBST(Bitree T, KeyType key){
	if(!T || T->data.key_value==key) return T;
	else if(T->data.key_value>key) return SearchBST(T->lchild, key);
	else return SearchBST(T->rchild, key);
}
//////////////////////////////////////////////////////////////////////////

//���Ŷ�ַ����ϣ��Ĵ洢�ṹ
int hashsize[]={11,19,29,37};//��ϣ������������һ�����ʵ��������У�
int m=0;//��ϣ�����ȫ�ֱ����� 

typedef struct{
	ElemType *elem;//����Ԫ�ش洢��ַ ��̬��������
	int count;//��ǰ����Ԫ�ظ��� 
	int size_index;//hashsize[size_index]Ϊ��ǰ���� 
}HashTable;

int InitHashTable(HashTable &ht){
	ht.count=0;
	ht.size_index=0;
	m=hashsize[ht.size_index];//��Ϊȫ�ֱ���
	ht.elem=(ElemType*)malloc(m*sizeof(ElemType));
	if(!ht.elem) exit(1);
	for(int i=0;i<m;i++){ht.elem[i].key_value=NULLKEY;}
	return 1;
}

/* ��ʼ����:��ϣ��H����*/  
/* �������:���ٹ�ϣ��H*/  
void DestroyHashTable(HashTable &ht)  
{  
	free(ht.elem);  
	ht.elem=NULL;  
	ht.count=0;  
	ht.size_index=0;  
} 

/* һ���򵥵Ĺ�ϣ����(mΪ�� ȫ�ֱ���)*/  
int Hash(KeyType K)  
{  
	return K%m;//key MOD p(����p<=m)
} 

/*����̽����ɢ��*/  
int collision(int p,int d)  
{  
	return (p+d)%m;//���Ŷ�ַ�������ͻ,mΪ�� 
}

/* �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,
�����ҳɹ�,��pָʾ��������Ԫ���ڱ���λ��,������SUCCESS;
����,��pָʾ����λ��,������UNSUCCESS��
c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο�*/
Status SearchHash(HashTable ht, KeyType key, int &p, int &c){
	p=Hash(key);
	int p_original=p;
	while(ht.elem[p].key_value!=NULLKEY && ht.elem[p].key_value!=key){
		if (c<m){
			p=collision(p_original,++c);
		}
		else{
			return UNSUCCESS;
		}
	}//��λ�������м�¼,���ҹؼ��ֲ����,����̽����ɢ��
	if(ht.elem[p].key_value==key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

void RecreateHashTable(HashTable&);
/* ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������1��
����ͻ�����������ؽ���ϣ�� */  
Status InsertHash(HashTable &ht, ElemType e){
	int p, c=0;
	if(SearchHash(ht, e.key_value, p, c)==SUCCESS){
		return DUPLICATE;
	}
	else if(c<hashsize[ht.size_index]/2){
		ht.elem[p]=e; ht.count++;
		return SUCCESS;
	}//��ͻ����cδ�ﵽ����,c�ķ�ֵ�ɵ� 
	else {
		RecreateHashTable(ht);

		InsertHash(ht, e);//����Ϊ�ع���ϣ��δ�����Ԫ�����²���
		return UNSUCCESS;
	}
}

void RecreateHashTable(HashTable &ht)//�ؽ���ϣ��
{
	int count=ht.count;
	ElemType *tmp=(ElemType *)malloc(count*sizeof(ElemType));
	ElemType *p=tmp;
	for(int i=0;i<m;i++){
		if(ht.elem[i].key_value!=NULLKEY)
			*(p++)=ht.elem[i];
	}//�ݴ�ԭ�е����ݵ�tmp
	printf("��ͻ�����ﵽ����,�����,�ؽ���ϣ��...\n"); 

	ht.size_index++;
	m=hashsize[ht.size_index];//����m
	p=(ElemType *)malloc(m*sizeof(ElemType));//����洢����,��ht.elem���·���ռ�p=new ElemType[m];
	if(!p) exit(1);
	ht.elem=p;

	ht.count=0;
	for(int i=0;i<m;i++)
		ht.elem[i].key_value=NULLKEY;//��ʼ��
	for(p=tmp;p<tmp+count;p++){//��tmp�е�ԭ�е����ݰ����µı����뵽�ؽ��Ĺ�ϣ����,ht.elem[p]=e; ht.count++; return SUCCESS;
		InsertHash(ht,*p);
	}
	printf("�ؽ���ϣ��ɹ�!\n"); 
}

/* ����ϣ��ַ��˳�������ϣ�� */  
void TraverseHash(HashTable ht,void(*Vi)(int ,ElemType)){
	printf("��ϣ��ַ:0~%d\n",m-1);
	for(int i=0;i<m;i++){
		if(ht.elem[i].key_value!=NULLKEY) Vi(i,ht.elem[i]);
	}

}

void Printf_Hash(int i, ElemType e){
	cout<<i<<" "<<e.key_value<<" "<<e.weight<<endl;
}

//////////////////////////////////////////////////////////////////////////

typedef struct Node{
	ElemType elem;
	struct Node *next;
}Node;

typedef struct{//������ַ�������ͻ����
	int h_value;
	struct Node *pointer;
}HashTable_L;

typedef HashTable_L* p_HashTable_L;

void Hash_Init(p_HashTable_L &ht){//��ϣ���ʼ��
	ht=new HashTable_L[m];
	for(int i = 0; i < m; i++){
		ht[i].h_value=NULLKEY;
		ht[i].pointer=NULL;
	}
}


Node* Hash_Search(p_HashTable_L ht, KeyType key){
	int p=Hash(key);
	if(ht[p].h_value == NULLKEY)
		return NULL;
	else if(ht[p].h_value == p){
		Node* ptr=ht[p].pointer;
		while(ptr != NULL){
			if(ptr->elem.key_value == key){
				return ptr;
			}
			ptr=ptr->next;
		}
	}
	else
		return NULL;
}

int Hash_Insert(p_HashTable_L &ht, ElemType e){
	int p=Hash(e.key_value);
	Node* node=new Node();
	node->elem=e;
	node->next=NULL;

	if(ht[p].h_value == NULLKEY){
		ht[p].pointer=node;
		ht[p].h_value=p;
		return 1;
	}
	else if(ht[p].h_value == p){
		Node* ptr=ht[p].pointer;
		while(ptr->next){ptr=ptr->next;}
		ptr->next=node;
		return 1;
	}
	return 0;
}


void main(){
	/*
		while (1)
		{
			SSTable st;
			int n;
			cout<<"�������¼��������";
			cin>>n;
			Creat_Seq(st,n);
			Traverse_Seq(st, Assign_Seq);
			Traverse_Seq(st, Printf_Seq);

			int key;
			cout<<"������ؼ���:";
			cin>>key;
			cout<<endl<<"Ԫ��λ��Ϊ:"<<Search_Seq(st, key);
			cout<<endl<<"Ԫ��λ��Ϊ(���ֲ���):"<<Search_Bin(st, key);

			SOSTree sost;
			cout<<endl<<"�������ɾ�̬������:";
			CreatSOSTree(sost, st);

			cout<<endl<<"ǰ������������:";
			PreOrderTraverse(sost);

			cout<<endl<<"��������������:";
			InOrderTraverse(sost);

			KeyType _key;
			cout<<endl<<"������Ҫ���ҵĹؼ���:";
			cin>>_key;
			cout<<endl<<SearchBST(sost, _key)->data.key_value;
			system("pause");
		}
		*/
	//////////////////////////////////////////////////////////////////////////
	/*
	while(1){
		ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
		//ElemType r[10]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
		HashTable h;
		InitHashTable(h);
		cout<<"���ϣ���в����¼...";
		for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
			if(InsertHash(h,r[i]) == DUPLICATE){
				cout<<endl<<"�������йؼ���"<<r[i].key_value<<"�ļ�¼,�޷��ٲ���ü�¼!"<<endl;
				system("pause");
				cout<<endl<<"�����������Ԫ��..."<<endl;
			}
		}

		printf("����ϣ��ַ��˳�������ϣ��:\n");
		TraverseHash(h,Printf_Hash);
		printf("���ٹ�ϣ��...\n");

		DestroyHashTable(h);
		system("pause");
	}*/

	ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
	p_HashTable_L ht=NULL;
	Hash_Init(ht);
	for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
		Hash_Insert(ht, r[i]);
	}


	while (1)
	{
		int key;
		cout<<"������ؼ���(key):";
		cin>>key;
		Node *p=NULL;
		if(p=Hash_Search(ht, key))
			cout<<Hash(key)<<" "<<p->elem.key_value<<" "<<p->elem.weight<<endl;
		else
			cout<<"��ƥ��!";
	}



}
