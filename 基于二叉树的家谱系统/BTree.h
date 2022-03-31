#pragma once
#ifndef __BTREE_H__
#define __BTREE_H__
#include<stdio.h>
#include<malloc.h>
#include<iostream>
#include"Stack.h"
#define MaxSize 100
using namespace std;

template<class ElemType>
void visite(ElemType e);

template<class ElemType>
class BTree
{
private:
	//���Ľṹ�嶨��
	typedef struct node
	{
		ElemType data;//���ڵ�ֵ
		struct node* lchild;//���ڵ�����
		struct node* rchild;//���ڵ��Һ���
	}BTNode;
	BTNode* b;//���ڵ�

public:
	BTree(string str);//�������ű�ʾ����ʼ����
	~BTree();		  //��������
	void PostOrder();				//��������ǵݹ��㷨		
	void PostOrderRe(BTNode* b);	//��������ݹ��㷨
	void PreOrderNotRe();			//��������ǵݹ��㷨
	void FindAllAncestor(char object);//����ڵ�object�����г���
	void ShowAncestor(BTNode* p);//���ancestor��ֵ����ͬ����ֵ,�����ֵܱ�ʾ���������������ֵ�
	void DestroyBTree(BTNode*& b);//������
	BTNode* getRoot() { return b; }	//��ȡ���ڵ�	
	bool Ancestor(BTNode* b, ElemType x);
};
#endif __BTREE_H__ //!__BTREE_H__

template<class ElemType>
BTree<ElemType>::BTree(string str)//�������ű�ʾ����ʼ����
{
	BTNode* p = NULL; 
	b = NULL;
	Stack<BTNode> bnode;
	int k = 0;
	BTNode* h;
	for (int i = 0; i < str.length(); i++)
	{
		switch (str[i])
		{
		case'(':bnode.Push(p); k = 1; break;
		case')':bnode.Pop(h); break;
		case',':k = 2; break;
		default:
			p = new BTNode;
			p->data = str[i];
			p->lchild = p->rchild = NULL;
			if (b == NULL)
			{
				b = p;
			}
			else
			{
				if (k == 1) 
				{
					bnode.Pop(h);
					h->lchild = p;
					bnode.Push(h);
				}
				if (k == 2)
				{
					bnode.Pop(h);
					h->rchild = p;
					bnode.Push(h);
				}
			}
		}
	}
}

template<class ElemType>			//��������
BTree<ElemType>::~BTree()
{
	DestroyBTree(b);
}

template<class ElemType>
void BTree<ElemType>::FindAllAncestor(char object)		//����ڵ�object�����г���
{
	BTNode* r, * p;//rΪ�ջ�ָ����һ�����ʵĽڵ�Ԫ�أ�pָ��ǰԪ��
	bool flag;//����Ƿ���������ջ
	Stack<BTNode> stack;//��ʼ��ջ
	p = new BTNode;
	p = b;
	do {
		//��p�ڵ��������������ջ 
		while (p != NULL)
		{
			stack.Push(p);
			p = p->lchild;
		}
		r = NULL;
		flag = true;
		while (!stack.StackEmpty() && flag)
		{
			stack.GetTop(p);
			if (p->rchild == r || p->rchild == NULL)//������Ϊ�ջ��Ѿ����ʹ�
			{
				if (p->data == object)//�����ǰԪ��ΪҪ���ҵĵĳ�Ա
				{
					bool flag_ancestor = false;//��������²������������Ϊ�����������ֵ�
					int i = stack.GetNum();
					while (!flag_ancestor && i > 0)//����ȥ���²������������ӵ�Ԫ��
					{
						if (stack.GetElement(i - 1)->lchild != NULL)
						{
							if (stack.GetElement(i - 1)->lchild->data == stack.GetElement(i)->data)
								flag_ancestor = true;
						}
						i--;
					}//����ShowAncestor(BTNode*)���ջ��ʣ��Ԫ�ؼ���ͬ��
					while (i > -1 && flag_ancestor)
					{
						if (i > 0 && stack.GetElement(i - 1)->lchild->data == stack.GetElement(i)->data)
						{
							ShowAncestor(stack.GetElement(i));
						}
						if (i == 0)
						{
							ShowAncestor(stack.GetElement(0));
						}
						i--;
					}
				}
				stack.Pop(p);
				r = p;
			}//����������ջ
			else
			{
				p = p->rchild;
				flag = false;
			}
		}
	} while (!stack.StackEmpty());
	cout << endl;
}

template<class ElemType>
void BTree<ElemType>::PostOrderRe(BTNode* b)	//��������ݹ��㷨
{
	if (b) 
	{
		PostOrderRe(b->lchild);
		PostOrderRe(b->rchild);
		visite(b->data);
	}
}

template<class ElemType>
void BTree<ElemType>::PostOrder()				//��������ǵݹ��㷨
{
	BTNode* p;
	Stack<BTNode> stack;//��ʼ��ջ
	Stack<BTNode> inverse;	//���������ڵ�
	p = b;
	do {
		//��p�ڵ������������ջ 
		while (p != NULL)
		{
			stack.Push(p);
			inverse.Push(p);
			p = p->rchild;
		}
		while (stack.Pop(p))
		{
			p = p->lchild;
			if (p)
			{
				break;
			}
		}
	} while (!stack.StackEmpty() || p != NULL);
	while (!inverse.StackEmpty())
	{
		inverse.Pop(p);
		visite(p->data);
	}
	cout << endl;
}

template<class ElemType>
void BTree<ElemType>::PreOrderNotRe()	//��������ǵݹ��㷨
{
	BTNode* p;
	Stack<BTNode> stack;//��ʼ��ջ
	p = b;
	do {
		//��p�ڵ��������������ջ 
		while (p != NULL)
		{
			stack.Push(p);
			visite(p->data);
			p = p->lchild;
		}
		while (stack.Pop(p)) 
		{
			p = p->rchild;
			if (p)
			{
				break;
			}
		}
	} while (!stack.StackEmpty() || p != NULL);
	cout << endl;
}

template<class ElemType>
void BTree<ElemType>::ShowAncestor(BTNode* p)//���ancestor��ֵ����ͬ����ֵ,�����ֵܱ�ʾ���������������ֵ�
{
	while (p)
	{
		visite(p->data);
		p = p->rchild;
	}
}

template<class ElemType>
void BTree<ElemType>::DestroyBTree(BTNode*& b)//������
{
	if (b != NULL) {				//�����������Ϊ��
		DestroyBTree(b->lchild);	//�ݹ�����������
		DestroyBTree(b->rchild);	//�ݹ�����������
		delete b;					//�ͷŸý��
	}
}

template<class ElemType>
void visite(ElemType e)				//������ڵ��Ԫ��
{
	cout << e;
}	  

template<class ElemType>
bool BTree<ElemType>::Ancestor(BTNode* b, ElemType x)		//��������Ϊ�ֵ���������
{
	if (b == NULL)
		return false;
	else if ((b->lchild != NULL && b->lchild->data == x) || (b->rchild != NULL && b->rchild->data == x))
	{
		visite(b->data);
		return true;
	}
	else if (Ancestor(b->lchild, x) || Ancestor(b->rchild, x))
	{
		visite(b->data);
		return true;
	}
	return false;
}


