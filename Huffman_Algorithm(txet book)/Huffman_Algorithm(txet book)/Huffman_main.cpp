#include<iostream>
using namespace std;
struct Node
{
	int weight;//权值
	int parent, lchild, rchild;//游标
};
void Select(Node hufftree[], int& i1, int& i2, int n);
void HuffmanTree(Node hufftree[], int w[], int n)//建立并初始化哈夫曼树
//n为哈夫曼的叶子结点数
{
	int i, k, i1, i2;
	for (i = 0; i < 2 * n - 1; i++)//初始化设定结点无双亲与孩子（即为独立根结点）
	{
		hufftree[i].parent = -1;
		hufftree[i].lchild = hufftree[i].rchild= -1;
	}
	for (i = 0; i < n; i++)//为叶子结点存储权值
		hufftree[i].weight = w[i];
	for (k = n; k < 2 * n - 1; k++)//n-1次合并
	{
		Select(hufftree, i1, i2,n);//权值最小的根结点下标为i1和i2
		hufftree[k].weight = hufftree[i1].weight + hufftree[i2].weight;
		hufftree[i1].parent = k; hufftree[i2].parent = k;
		hufftree[k].lchild = i1; hufftree[k].rchild = i2;//合并合成并连接产生一棵树
	}
}
void Select(Node hufftree[], int& i1, int& i2, int n)
{
    int min1 = INT_MAX, min2 = INT_MAX;// 初始化两个最小值

    for (int i = 0; i < n; ++i)
    {
        if (hufftree[i].parent == -1)//考虑未被并入的结点
        {
            if (hufftree[i].weight < min1)
            {
                min2 = min1;
                i2 = i1;

                min1 = hufftree[i].weight;
                i1 = i;
            }
            else if (hufftree[i].weight < min2)
            {
                min2 = hufftree[i].weight;
                i2 = i;
            }
        }
    }
}