#include <iostream>
#define NULLKEY 0//0Ϊ�޼�¼��־
#define SUCCESS 1  
#define UNSUCCESS 0  
#define DUPLICATE -1
using namespace std;

int hashsize[]={11,19,29,37};//��ϣ������������һ�����ʵ��������У�
int Hash_length=0;//��ϣ���

//�����¼
struct ElemType{
	int key_value;
	float weight;
};
//�����ϣ��
struct HashTable{
	ElemType *elem;//����Ԫ�ش洢��ַ����̬�������飩
	int count;//��ǰ����Ԫ�ظ��� 
	int size_index;//hashsize[size_index]Ϊ��ǰ���� 
};

//��ʼ����ϣ��
int InitHashTable(HashTable &ht){
	ht.count=0;
	ht.size_index=0;
	Hash_length=hashsize[ht.size_index];//��Ϊȫ�ֱ���
	ht.elem=(ElemType*)malloc(Hash_length*sizeof(ElemType));
	if(!ht.elem) exit(1);
	for(int i=0;i<Hash_length;i++){ht.elem[i].key_value=NULLKEY;}//��������ж϶�Ӧλ���Ƿ�ռ��
	return 1;
}

//���ٹ�ϣ��
//��ʼ����:��ϣ��ht���ڣ��������:���ٹ�ϣ��ht 
void DestroyHashTable(HashTable &ht)  
{  
	if(ht.elem != NULL) free(ht.elem);  
	ht.elem=0;  
	ht.count=0;  
	ht.size_index=0;  
} 

//һ���򵥵Ĺ�ϣ����������Hash_lengthΪ��
int Hash(int K)  
{  
	return K%Hash_length;//key MOD p(����p<=Hash_length)
} 

//���Ŷ�ַ�������ͻ,Hash_lengthΪ��������̽����ɢ��
int collision(int H_key,int d)  
{  
	return (H_key+d)%Hash_length;
}

//�ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,
//�����ҳɹ�,��pָʾ��������Ԫ���ڱ���λ��,������SUCCESS;
//����,��pָʾ����λ��,������UNSUCCESS��
//ע�⣺c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο�
int SearchHash(HashTable ht, int key, int &p, int &c){
	p=Hash(key);
	int p_original=p;
	c = 0;
	while(c<hashsize[ht.size_index] && ht.elem[p].key_value!=NULLKEY && ht.elem[p].key_value!=key){
		c++;
		p=collision(p_original,c);
	}

	if(ht.elem[p].key_value==key)
		return SUCCESS;
	else
		return UNSUCCESS;
}

//ɾ��Ԫ��
int DeleteElem(HashTable ht, int key){
	int p, c=0;
	if (SearchHash(ht, key, p, c)==SUCCESS){
		ht.elem[p].key_value=NULLKEY;
		ht.count--;
		return SUCCESS;
	}
	else{
		return UNSUCCESS;
	}
}

void RecreateHashTable(HashTable &ht);

//���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��ht�У�������1������ͻ�����������ؽ���ϣ��
int InsertHash(HashTable &ht, ElemType e){
	int p, c=0;
	if(SearchHash(ht, e.key_value, p, c)==SUCCESS){//�Ѿ�����e
		return DUPLICATE;
	}
	else if(c<hashsize[ht.size_index]/2){//������e����ͻ����cδ�ﵽ����hashsize[ht.size_index]/2
		ht.elem[p]=e;
		ht.count++;
		return SUCCESS;
	}
	else {//������e����ͻ����c�ﵽ����
		RecreateHashTable(ht);//�ؽ��µĹ�ϣ��ht��ht�������Լ�Ԫ�ص�λ�÷����仯
		InsertHash(ht, e);//��Ԫ�ز���
		return SUCCESS;
	}
}

void RecreateHashTable(HashTable &ht)//�ؽ���ϣ��
{
	printf("��ͻ�����ﵽ���ޣ���������ؽ���ϣ������\n"); 

	ElemType* p_tmp=ht.elem;//�ݴ�
	int size_index_tmp=ht.size_index;//�ݴ�

	//����洢����,��ht.elem���·���ռ�
	ht.count=0;
	ht.size_index++;
	Hash_length=hashsize[ht.size_index];//����Hash_length
	ElemType* p_new=(ElemType*)malloc(Hash_length*sizeof(ElemType));
	if(!p_new) exit(1);
	ht.elem=p_new;

	//��ʼ��
	for(int i=0;i<Hash_length;i++)
		ht.elem[i].key_value=NULLKEY;

	//��tmp�е�ԭ�е����ݰ����µı����뵽�ؽ��Ĺ�ϣ����
	for(int i=0;i<hashsize[size_index_tmp];i++){
		if((p_tmp+i)->key_value!=NULLKEY){
			InsertHash(ht,*(p_tmp+i));
		}
	}

	delete[] p_tmp;
	printf("�ؽ���ϣ��ɹ���\n"); 
}


/* ����ϣ��ַ��˳�������ϣ�� */  
void TraverseHash(HashTable ht,void(*Visit)(int, ElemType)){
	printf("��ϣ��ַ:0~%d\n",Hash_length-1);
	for(int i=0;i<Hash_length;i++){
		if(ht.elem[i].key_value!=NULLKEY) Visit(i,ht.elem[i]);
	}

}

void Print_Hash(int i, ElemType e){
	cout<<i<<" "<<e.key_value<<endl;
}

//////////////////////////////////////////////////////////////////////////
#define HASH_LENGTH 13

//�����¼
struct ElemType1{
	int key_value;
	float weight;
};

//����ÿ�������Ľ��
struct Node{
	ElemType1 elem;
	struct Node *next;
};

//�����ϣ��Ľ��
struct HashTable_Node{
	int h_value;//��ȡ�����õ��Ĺ�ϣֵ
	struct Node *pointer;//ÿ���������׵�ַ
};

//��������ַ���Ĺ�ϣ��
typedef HashTable_Node* HashTable_L;

//һ���򵥵Ĺ�ϣ����������HASH_LENGTHΪ��
int Hash1(int K)  
{  
	return K%HASH_LENGTH;//key MOD p(����p<=HASH_LENGTH)
} 

void Hash_Init(HashTable_L &ht){//��ϣ���ʼ��
	ht=new HashTable_Node[HASH_LENGTH];
	if (!ht) exit(1);
	for(int i = 0; i < HASH_LENGTH; i++){
		ht[i].h_value=NULLKEY;//�������Ͳ���
		ht[i].pointer=NULL;
	}
}

void Hash_Insert(HashTable_L &ht, ElemType1 e){
	int p=Hash1(e.key_value);

	Node* node=new Node();
	if (!node) exit(1);
	node->elem=e;
	node->next=NULL;

	if(ht[p].h_value == NULLKEY){//��Ӧ�ù�ϣֵ������Ϊ��
		ht[p].pointer=node;
		ht[p].h_value=p;
	}
	else if(ht[p].h_value == p){//��Ӧ�ù�ϣֵ��������Ϊ��
		Node* ptr=ht[p].pointer;
		while(ptr->next){ptr=ptr->next;}
		ptr->next=node;
	}
}

Node* Hash_Search(HashTable_L ht, int key){
	int p=Hash1(key);
	if(ht[p].h_value == NULLKEY)//��Ӧ�ù�ϣֵ������Ϊ��
		return NULL;
	else if(ht[p].h_value == p){//��Ӧ�ù�ϣֵ��������Ϊ��
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


void main(){
	while(1){
		//ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
		ElemType r[12]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{60,9},{13,10}};
		HashTable h;
		InitHashTable(h);

		cout<<"���ϣ���в����¼������"<<endl;
		for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
			if(InsertHash(h,r[i]) == DUPLICATE){
				cout<<"�������йؼ���"<<r[i].key_value<<"�ļ�¼,�޷��ٲ���ü�¼��"<<endl;
				cout<<"�����������Ԫ�ء�����"<<endl;
			}
		}

		printf("����ϣ��ַ��˳�������ϣ��\n");
		TraverseHash(h,Print_Hash);

		DeleteElem(h,29);

		printf("����ϣ��ַ��˳�������ϣ��\n");
		TraverseHash(h,Print_Hash);

		printf("���ٹ�ϣ������\n");
		DestroyHashTable(h);
		system("pause");
	}


	//ElemType1 r[13]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{60,2},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};
	////ElemType1 r[13]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{5,9},{6,10},{7,11},{8,12}};

	//HashTable_L ht=NULL;
	//Hash_Init(ht);

	//for(int i=0;i<sizeof(r)/sizeof(r[0]);i++){
	//	Hash_Insert(ht, r[i]);
	//}

	//while (1)
	//{
	//	int key;
	//	cout<<"������ؼ���(key):";
	//	cin>>key;
	//	Node *p=NULL;
	//	if(p=Hash_Search(ht, key))
	//		cout<<"��ϣֵ��ؼ��ֵ�ֵ�ֱ�Ϊ��"<<Hash1(key)<<" "<<p->elem.key_value<<endl;
	//	else
	//		cout<<"��ƥ��!"<<endl;
	//}
}