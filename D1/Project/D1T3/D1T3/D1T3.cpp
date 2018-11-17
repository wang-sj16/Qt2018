// D1T3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<string>
using namespace std;

template<typename T>                    //创建模板函数
T Max(const T& left, const T& right)
{
	return left > right ? left : right;
}

int main()
{
	int i = 1;
	int j = 2;
	cout << "Max(i, j): " << Max(i, j) << endl;
	double f1 = 11.1;
	double f2 = 22.2;
	cout << "Max(f1, f2): " << Max(f1, f2) << endl;
	string s1 = "AAAAA";
	string s2 = "BBBBB";
	cout << "Max(s1, s2): " << Max(s1, s2) << endl;
	return 0;
}

