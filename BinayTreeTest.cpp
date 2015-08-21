// BinayTreeTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

bool iscatch = false;

struct node
{
	node(int d) :data(d), pleft(0), pright(0){}
	node() :data(0), pleft(0), pright(0){}

	int data;
	node* pleft;
	node* pright;
};


//定义一个全局的变量，用于存储路径
vector<node*> pnodevector; 
vector<node*> pnodevector2;
//vector<int> iv;


//创建一个有9个结点的二叉树
node* createBT()
{
	node* root = new node(1);
	node* n2 = new node(2);
	node* n3 = new node(3);
	node* n4 = new node(4);
	node* n5 = new node(5);
	node* n6 = new node(6);
	node* n7 = new node(7);
	node* n8 = new node(8);
	node* n9 = new node(9);
	root->pleft = n2;
	root->pright = n3;
	n2->pleft = n4;
	n2->pright = n5;
	n3->pleft = n6;
	n3->pright = n7;
	n4->pleft = n8;
	n4->pright = n9;
	return root;

}

//先序遍历二叉树
void pretraverse(node * bt)
{
	if (bt)
	{
		cout << bt->data << " ";
	}
	if (bt->pleft)
	{
		pretraverse(bt->pleft);
	}
	if (bt->pright)
	{
		pretraverse(bt->pright);
	}
}



//先序遍历二叉树，寻找从根节点到指定节点的路径上所有的结点
node* searchpath(node* r,int data,vector<int>& iv)
{
	node* root = r;
	if (!iscatch&&root)
	{
		//cout << "push_back" << root->data << endl;
		iv.push_back(root->data);
		if (root->data == data)
		{
			iscatch = true;
			return root;
		}
	}
	if (!iscatch&&root->pleft)
	{
		searchpath(root->pleft,data,iv);
	}
	if (!iscatch&&root->pright)
	{
		searchpath(root->pright,data,iv);
	}
	
	if (!iscatch)
	{
		//cout << "pop_back  " << root->data << " " << endl;
		iv.pop_back();
	}
	
}


//求两个vector的最后一个公共结点
int lastcommon(vector<int> iv1, vector<int> iv2)
{
	int pre = 0;
	int i = 0;
	int len = iv1.size() > iv2.size() ? iv2.size() : iv1.size();
	while (i<len&&iv1[i]==iv2[i])
	{
		i++;
	}
	cout << "最低公共祖先结点为" << endl;
	cout << iv1[--i] << endl;
	return iv1[i];
}


int _tmain(int argc, _TCHAR* argv[])
{
	node* root = createBT();
	//pretraverse(root);
	vector<int> iv1;
	searchpath(root,9,iv1);
	iscatch = false;
	vector<int> iv2;
	searchpath(root,8,iv2);
	lastcommon(iv1, iv2);

	for (auto item : iv1)
		cout << item<< " ";
	cout << endl;
	for (auto item : iv2)
		cout << item << " ";

	return 0;
}

