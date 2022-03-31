#include "Stack.h"

//template<class T>
//struct LinkNode
//{
//    T data;
//    LinkNode<T>* next;
//};
//
//template <class T>
//class LinkedList
//{
//private:
//
//    LinkNode<T>* head;
//
//public:
//
//    LinkNode* DelPrior(LinkNode* p)
//    {
//        LinkNode q, r;
//
//        r = p->next;
//
//        while (r->next->next != p)
//
//            r = r->next;
//
//        q = r->next;
//
//        r->next = p;
//
//        delete(q);
//
//        return (q);
//    }
//};
//
//#define ListSize 50
//#define ListIncrease 10
//#define Status int
//#define DataType int
//#define OK 1
//#define ERROR 0
//template <class T>
//class SqList
//{
//private:
//    T* elem;   //���ֲ��䣬NULL ������ջ
//    int length; //ʵ�ʴ��Ԫ�صĸ���
//    int listsize; //�������ɵ����Ԫ�صĸ���
//public:
//    Status SeqInsert(T e)
//    {
//        T* p, * q;
//        for (p = elem; p <= elem + length - 1; p++)
//            if (*p > e) break;
//        //�ƶ�Pλ���Ժ�Ľ�㣬�ճ�λ�ô��e
//        for (q = elem + length - 1; q >= p; q--)
//            *(q + 1) = *q;
//        *p = e;
//        ++length;
//    }
//};

//SqStack<T>  //Ϊ���ȶ���õ�ջ����
//char* Train_arrange(char* train)
//{
//    char c, * result;
//    result = new char;
//    SqStack<char> s;
//    int i = 0, j = 0;
//    while (*(train + i)) {
//        if (*(train + i) == 'H')
//            s.Push(*(train + i));
//        else
//            *(result + j++) = *(train + i);
//        i++;
//    }
//    while (!s.IsEmpty())
//    {
//        s.Pop(c);
//        *(result + j++) = c;
//    }
//    *(result + j) = '\0';
//    return result;
//}
//
//Status IsPalindrome(char* ptr)
//{
//    SqStack<char> s;
//    CircularQueue<char> q;
//    char e1, e2;
//    int i = 0;
//    while (*(ptr + i)) {
//        s.Push(*(ptr + i));
//        q.EnQueue(*(ptr + i));
//        i++;
//    }
//    while (s.IsEmpty()) {
//        s.Pop(e1);
//        q.DeQueue(e2);
//        if (e1 != e2) return NO;
//    }
//    return YES;
//}
