#include "BTree.h"
#include <string>



int main()
{
	string str;
	cout << "�����ű�ʾ������������ṹ��";
	int i = 0;
	char object;
	cin >> str;
	BTree<char> btree(str);
	cout << "��������ݹ��㷨��";
	btree.PostOrderRe(btree.getRoot());
	cout << endl;
	cout << "��������ǵݹ��㷨��";
	btree.PostOrder();
	cout << "��������ǵݹ��㷨��";
	btree.PreOrderNotRe();
	cout << "����ָ��������ţ��Բ�ѯ�����г�����";
	cin >> object;
	cout << object<<"�����г�����";
	btree.FindAllAncestor(object);
	return 0;
}
