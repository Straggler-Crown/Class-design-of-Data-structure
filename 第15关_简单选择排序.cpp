#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
typedef struct Food {
	char name[100];		        // 中文名称
	char sname[100];	        // 英文名称
	char health[10000];	        // 养生功效
	char nutrition[10000];      // 营养与功效
	char expert[10000];	        // 专家提醒
	char link[10000];	        // 相关链接
	string recipe[30];	        // 养生保健食谱
	int recipe_size = 0;        // 食谱数量
	string therapy[30];	        // 食疗验方
	int therapy_size = 0;       // 验方数量
} Food;
typedef struct {
	Food* elem;                 // 指向数组的指针
	int length;                 // 数组的长度
} SqList;
int len = strlen("中文名称：");

void InitList(SqList& L) {
	// 使用动态内存分配new进行初始化
	L.elem = new Food[MAXSIZE];
	L.length = 0;
}

void FreeList(SqList& L) {
	// 释放内存
	delete[] L.elem;
}

void ReadFood(Food& f, ifstream& infile) {
	infile.getline(f.name, 100);
	infile.getline(f.sname, 100);
	infile.getline(f.health, 10000);
	infile.getline(f.nutrition, 10000);
	infile.getline(f.expert, 10000);
	infile.getline(f.link, 10000);

	string line;
	int i = 0, j = 0;
	while (getline(infile, line)) {
		if (line == "#") {
			break;
		}
		else if (line == "养生保健食谱：") {
			while (getline(infile, line)) {
				if (line == "食疗验方：")
					break;
				else if (line == "#") return;
				f.recipe[i++] = line;
			}
		}
		else if (line == "食疗验方: ") {
			while (getline(infile, line)) {
				if (line == "#")
					break;
				f.therapy[j++] = line;
			}
		}
	}
}

void ReadFile(SqList& L, string filename) {
	ifstream file(filename);
	string line;
	int i = 0;
	ifstream infile(filename);
	if (!infile) {
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}

	while (!infile.eof()) {
		Food f;
		for (int i = 0; i < 30; i++)
			f.sname[i] = '/0';
		ReadFood(f, infile);
		for (int i = 0; i < 100 - len; i++)
			f.sname[i] = f.sname[i + len];
		//cout << f.sname << endl;
		L.elem[L.length++] = f;
	}

	infile.close();
}


int cmp(Food a, Food b) {
	// 比较函数，按照食材英文名称从小到大排序
	//11
	char* s1 = new char[30], * s2 = new char[30];
	for (int i = 0; i < 30; i++) {
		s1[i] = a.sname[i];
		s2[i] = b.sname[i];
	}
	string ss1(s1), ss2(s2);
	if (ss1 >= ss2)
		return 1;
	else
		return -1;
}


void Lcopy(Food& f2, Food& f1)
{
	//将左边的值给到右边
	strcpy(f1.name, f2.name);
	//f1清空
	strcpy(f1.sname, f2.sname);
	strcpy(f1.health, f2.health);
	strcpy(f1.nutrition, f2.nutrition);
	strcpy(f1.expert, f2.expert);
	strcpy(f1.link, f2.link);
	f1.recipe_size = f2.recipe_size;
	f1.therapy_size = f2.therapy_size;
	for (int i = 0; i < f2.recipe_size; i++)
		f1.recipe[i] = f2.recipe[i];
	for (int i = 0; i < f2.therapy_size; i++)
		f1.therapy[i] = f2.therapy[i];
}

void SelectSort(SqList& L, int& kcn, int& rmn) {
	// 对顺序表做简单选择排序
	// 注：L.elem[0]用做哨兵单元
	// 输出排序后的食材英文名称、KCN和RMN

	int k, j;

	// 将顺序表元素依次向后移动一位
	for (int i = L.length; i >= 1; i--)
		Lcopy(L.elem[i - 1], L.elem[i]);

	for (int i = 1; i < L.length; i++)
	{
		// 从当前位置开始，进行简单选择排序

		k = i;

		for (j = i + 1; j <= L.length; j++) {
			// 在无序部分找到最小元素的位置
			if (cmp(L.elem[j], L.elem[k]) == -1)
				k = j;
			kcn++;
			// 每次比较关键字次数+1
		}

		if (k != i)
		{
			// 如果最小元素不在当前位置，进行交换
			Lcopy(L.elem[k], L.elem[0]);
			Lcopy(L.elem[i], L.elem[k]);
			Lcopy(L.elem[0], L.elem[i]);
			rmn += 3;
			// 记录移动次数+3
		}
	}


	// 输出排序后的食材英文名称
	for (int k = 1; k <= L.length; k++)
		cout << L.elem[k].sname << endl;

	cout << "总的关键字比较次数KCN为：" << kcn << endl;
	cout << "总的记录移动次数RMN为：" << rmn << endl;
}


int main() {
	SqList L;
	InitList(L);
	int kcn = 0;
	int rmn = 0;
	ReadFile(L, "food.txt");
	SelectSort(L, kcn, rmn);
	FreeList(L);
	return 0;
}