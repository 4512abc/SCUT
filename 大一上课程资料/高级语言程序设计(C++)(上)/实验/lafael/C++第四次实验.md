#                                                                                             C++第四次实验

###                                                                                                                                                                                                                                                                                                                                                                                                           ————指针的应用

## Task 1

内容：

（1）根据输入的一系列整数，以0标志结束，用**头插法**建立单链表，并输出单链表中各元素值，观察输入的内容与输出的内容是否一致。

（2）根据输入的一系列整数，以0标志结束，用**尾****插法**建立单链表，并输出单链表中各元素值，观察输入的内容与输出的内容是否一致。

（3）在单链表的第i个元素之后插入一个值为x的元素，并输出插入后的单链表中各元素值。

（4）删除单链表中第i个元素，并输出删除后的单链表中各元素值。

（5）在单链表中查找第i个元素，如果查找成功，则显示该元素的值，否则显示该元素不存在。

```c++
#include<iostream>
#include<algorithm>
using namespace std;
struct zs
{
	int hd;
	zs*dz;
};
void output( zs *a)
{
	 
	for (zs* s = a; s->dz!= NULL;)
	{
		cout << s->hd << " ";;
		s = s->dz;
	}
}
void hput()
{
	zs sw[123] = {};
	cout << "输入元素个数"<<endl;
	int n; cin >> n;
	cout << "依次输入"<<endl;
	for (int i = 0; i < n; i++)
	{
		int g;
		cin >> g;
		sw[i] = { g,&sw[i + 1] };
	}
	output(&sw[0]);
}
void wput()
{
	zs sw2[123] = {};
	cout << "输入元素个数"<<endl;
	int n; cin >> n;
	cout<<"依次输入"<<endl;
	for (int i = n; i >=1; i--)
	{
		int g; cin >> g;
		sw2[i+1] = { g,&sw2[i] };
	}
	output(&sw2[n+1]);
}
void cut(zs sw[])
{
	cout << "输入要删去元素的位置"<<endl;
	int g; cin >> g;
	sw[g - 2].dz = &sw[g];
	output(&sw[0]);
}
void find(zs sw[],int n)
{
	int g; cin >> g;
	if (g > n)cout << "找不到"<<endl;
	else cout << sw[g-1].hd;
}
bool jian(zs a, zs b)
{
	if (a.hd < b.hd)return 1;
	else return 0;
}
int main()
{	
	zs sw[123] = {};
	cout << "输入元素个数"<<endl;
	int n; cin >> n;
	cout << "依次输入"<<endl;
	for (int i = 0; i < n; i++)
	{
		int g;
		cin >> g;
		sw[i] = { g,&sw[i + 1] };
	}
	sort(sw + 0, sw + n, jian);
	output(&sw[0]);
}
```

使用hput和wput分别实现头插和尾插。

输出结果如下：

```c++
输入元素个数
6
依次输入
1 2 5 4 3 6
5
3
输入要删去元素的位置
4
1 2 5 3 6

```

## Task 2 插入排序

```c++
void change(zs* a,zs*b)
{
	zs* q = a;
	b->dz = q->dz;
	q->dz = b;
}
int main()
{
	zs  se[123] = {};
	se[0].dz = &se[1];
	cout << "输入元素个数" << endl;
	int n; cin >> n;
	cout << "依次输入" << endl;
	for (int i = 1; i <= n; i++)
	{
		int g;
		cin >> g;
		se[i] = { g,&se[i + 1] };
	}
	zs* sw=se+1; int j = 1;
	for (int i = 1; i <= n; i++)
	{
		for (zs*sw = se; sw->dz != (se+i)->dz; sw=sw->dz,j++)
		{
			if ((se+i)->hd < sw->dz->hd)
			{
				zs* sq = se;
				for (int g = 1; g <= n; g++,sq=sq->dz)
				{
					
					if (sq->dz->hd == se[i].hd)
					{
						sq->dz = &se[i + 1];
						break;
					}
				}
				change(sw, se + i);
				if (j == 1)j = 0;
				else j = 1;
				break;
			}		
		}
		if (j == 0)sw = se + i;
		else j = 1;
		output(sw);
		cout << endl;
		
	}

}
```

输出为

```c++
输入元素个数
5 2 1 3 5 4
依次输入
2 1 3 5 4
1 2 3 5 4
1 2 3 5 4
1 2 3 5 4
1 2 3 4 5
```

会依次输出每次插入排序的结果。

收获：

通过对指针指向的改变，可以实现链节的增添，删除，替换，相比于数组更加灵活，但相对的更加复杂。也可以通过链表实现对精灵类成员的管理。
