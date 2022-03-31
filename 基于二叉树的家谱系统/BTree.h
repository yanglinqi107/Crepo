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
	//树的结构体定义
	typedef struct node
	{
		ElemType data;//树节点值
		struct node* lchild;//树节点左孩子
		struct node* rchild;//树节点右孩子
	}BTNode;
	BTNode* b;//根节点

public:
	BTree(string str);//根据括号表示法初始化树
	~BTree();		  //析构函数
	void PostOrder();				//后序遍历非递归算法		
	void PostOrderRe(BTNode* b);	//后序遍历递归算法
	void PreOrderNotRe();			//先序遍历非递归算法
	void FindAllAncestor(char object);//输出节点object的所有长辈
	void ShowAncestor(BTNode* p);//输出ancestor的值及其同辈的值,孩子兄弟表示法中右子树代表兄弟
	void DestroyBTree(BTNode*& b);//销毁树
	BTNode* getRoot() { return b; }	//获取根节点	
	bool Ancestor(BTNode* b, ElemType x);
};
#endif __BTREE_H__ //!__BTREE_H__

template<class ElemType>
BTree<ElemType>::BTree(string str)//根据括号表示法初始化树
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

template<class ElemType>			//析构函数
BTree<ElemType>::~BTree()
{
	DestroyBTree(b);
}

template<class ElemType>
void BTree<ElemType>::FindAllAncestor(char object)		//输出节点object的所有长辈
{
	BTNode* r, * p;//r为空或指定上一步访问的节点元素，p指向当前元素
	bool flag;//标记是否将右子树进栈
	Stack<BTNode> stack;//初始化栈
	p = new BTNode;
	p = b;
	do {
		//将p节点的所有左子树入栈 
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
			if (p->rchild == r || p->rchild == NULL)//右子树为空或已经访问过
			{
				if (p->data == object)//如果当前元素为要查找的的成员
				{
					bool flag_ancestor = false;//用来标记下层的右子树，因为右子树代表兄弟
					int i = stack.GetNum();
					while (!flag_ancestor && i > 0)//用于去掉下层以右子树连接的元素
					{
						if (stack.GetElement(i - 1)->lchild != NULL)
						{
							if (stack.GetElement(i - 1)->lchild->data == stack.GetElement(i)->data)
								flag_ancestor = true;
						}
						i--;
					}//调用ShowAncestor(BTNode*)输出栈中剩余元素及其同辈
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
			}//将右子树进栈
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
void BTree<ElemType>::PostOrderRe(BTNode* b)	//后序遍历递归算法
{
	if (b) 
	{
		PostOrderRe(b->lchild);
		PostOrderRe(b->rchild);
		visite(b->data);
	}
}

template<class ElemType>
void BTree<ElemType>::PostOrder()				//后序遍历非递归算法
{
	BTNode* p;
	Stack<BTNode> stack;//初始化栈
	Stack<BTNode> inverse;	//逆后序遍历节点
	p = b;
	do {
		//将p节点的所有子树入栈 
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
void BTree<ElemType>::PreOrderNotRe()	//先序遍历非递归算法
{
	BTNode* p;
	Stack<BTNode> stack;//初始化栈
	p = b;
	do {
		//将p节点的所有左子树入栈 
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
void BTree<ElemType>::ShowAncestor(BTNode* p)//输出ancestor的值及其同辈的值,孩子兄弟表示法中右子树代表兄弟
{
	while (p)
	{
		visite(p->data);
		p = p->rchild;
	}
}

template<class ElemType>
void BTree<ElemType>::DestroyBTree(BTNode*& b)//销毁树
{
	if (b != NULL) {				//如果二叉树不为空
		DestroyBTree(b->lchild);	//递归销毁左子树
		DestroyBTree(b->rchild);	//递归销毁右子树
		delete b;					//释放该结点
	}
}

template<class ElemType>
void visite(ElemType e)				//输出树节点的元素
{
	cout << e;
}	  

template<class ElemType>
bool BTree<ElemType>::Ancestor(BTNode* b, ElemType x)		//右子树不为兄弟树的祖先
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


