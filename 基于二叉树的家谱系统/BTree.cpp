#include "BTree.h"
#include <string>



int main()
{
	string str;
	cout << "以括号表示法输入二叉树结构：";
	int i = 0;
	char object;
	cin >> str;
	BTree<char> btree(str);
	cout << "后序遍历递归算法：";
	btree.PostOrderRe(btree.getRoot());
	cout << endl;
	cout << "后序遍历非递归算法：";
	btree.PostOrder();
	cout << "先序遍历非递归算法：";
	btree.PreOrderNotRe();
	cout << "输入指定人物代号，以查询其所有长辈：";
	cin >> object;
	cout << object<<"的所有长辈：";
	btree.FindAllAncestor(object);
	return 0;
}
