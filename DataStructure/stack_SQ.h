#ifndef sq_stack_h
#define sq_stack_h

#define STACK_INIT_SIZE 10 //��ʼջ����󳤶�
#define STACKINCREMENT 10 //ÿ��������ջ�ĳ���

template <class DataType>
class sq_stack{
public:
	sq_stack();
	void Push(DataType e); //����Ϊe����ջ��Ԫ��
	void Pop(); //ɾ��ջ��Ԫ��
	DataType Top(); //ȡ��ջ��Ԫ��
	bool Empty(); //�ж�ջ�Ƿ�Ϊ�գ��շ���1
	~sq_stack(); //ջ������

private:
	DataType *base; //ջβ
	DataType *top; //ջ��
	int stacksize;
};
#endif