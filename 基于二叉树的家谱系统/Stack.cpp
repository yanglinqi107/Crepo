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
//    T* elem;   //保持不变，NULL 不存在栈
//    int length; //实际存放元素的个数
//    int listsize; //可以容纳的最大元素的个数
//public:
//    Status SeqInsert(T e)
//    {
//        T* p, * q;
//        for (p = elem; p <= elem + length - 1; p++)
//            if (*p > e) break;
//        //移动P位置以后的结点，空出位置存放e
//        for (q = elem + length - 1; q >= p; q--)
//            *(q + 1) = *q;
//        *p = e;
//        ++length;
//    }
//};

//SqStack<T>  //为事先定义好的栈类型
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
