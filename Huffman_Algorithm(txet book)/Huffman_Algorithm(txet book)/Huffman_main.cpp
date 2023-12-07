#include<iostream>
using namespace std;
struct Node
{
	int weight;//Ȩֵ
	int parent, lchild, rchild;//�α�
};
void Select(Node hufftree[], int& i1, int& i2, int n);
void HuffmanTree(Node hufftree[], int w[], int n)//��������ʼ����������
//nΪ��������Ҷ�ӽ����
{
	int i, k, i1, i2;
	for (i = 0; i < 2 * n - 1; i++)//��ʼ���趨�����˫���뺢�ӣ���Ϊ��������㣩
	{
		hufftree[i].parent = -1;
		hufftree[i].lchild = hufftree[i].rchild= -1;
	}
	for (i = 0; i < n; i++)//ΪҶ�ӽ��洢Ȩֵ
		hufftree[i].weight = w[i];
	for (k = n; k < 2 * n - 1; k++)//n-1�κϲ�
	{
		Select(hufftree, i1, i2,n);//Ȩֵ��С�ĸ�����±�Ϊi1��i2
		hufftree[k].weight = hufftree[i1].weight + hufftree[i2].weight;
		hufftree[i1].parent = k; hufftree[i2].parent = k;
		hufftree[k].lchild = i1; hufftree[k].rchild = i2;//�ϲ��ϳɲ����Ӳ���һ����
	}
}
void Select(Node hufftree[], int& i1, int& i2, int n)
{
    int min1 = INT_MAX, min2 = INT_MAX;// ��ʼ��������Сֵ

    for (int i = 0; i < n; ++i)
    {
        if (hufftree[i].parent == -1)//����δ������Ľ��
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