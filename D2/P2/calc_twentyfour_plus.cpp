#include "pch.h"
#include "calc_twentyfour_plus.h"
#include<iostream>
#include<math.h>
using namespace std;

void TwentyFourCalculatorPlus::ToBinaryCode(long num)
{
	int j = 0;
	if (num == 0)
	{
		code_array_[0] = 0;
	}
	while (num)
	{
		code_array_[j] = num % 2;
		num /= 2;
		j++;
	}
}

TwentyFourCalculatorPlus::TwentyFourCalculatorPlus()
{
	cin >> card_num_ >> target_;
	for (int i = 0; i < card_num_; i++)
	{
		cin >> card_numbers_array_[i];
	}
}

void TwentyFourCalculatorPlus::run()
{
	long total_permutation = pow(2, card_num_ - 1);       //n个数字，n-1个运算符，对应2^(n-1)种排列可能性
	long result = 0;
	for (int i = 0; i < total_permutation; i++)                  //遍历可能性
	{
		ToBinaryCode(i);                                //用十进制数代表第i种可能性，转换成二进制序列代表运算符排列序列
		result = CalculateFormula();
		if (result == target_)        //找到合法的算式
		{
			PrintResult(); 
		}
		else if (result > target_&&above_target_min_ == -1 || result > target_&&result < above_target_min_) 
		{    //检查是否更新比目标大的最小值
			above_target_min_ = result;
		}
	}
	if (above_target_min_ > result)           //未找到合法算法但是找到比目标大的最小值
	{
		cout << "No" << endl << above_target_min_;
	}
	else                    //未找到合法算法且最大值小于目标
	{
		cout << "No" << endl << -1;
	}
}

long TwentyFourCalculatorPlus::CalculateFormula()
{
	long temp_result = card_numbers_array_[0];
	for (int i = 0; i < card_num_-1; i++)                //编码为0对应加法
	{
		if (code_array_[i] == 1)
		{
			temp_result = temp_result + card_numbers_array_[i + 1];
		}
		else                                                             //编码为1对应乘法
		{
			temp_result = temp_result * card_numbers_array_[i + 1];
		}
	}
	return temp_result;
}

void TwentyFourCalculatorPlus::PrintResult()
{
	for (int j = 0; j < card_num_ - 1; j++)
	{
		if (code_array_[j] == 0)
		{
			cout << card_numbers_array_[j] << '*';
		}
		else
		{
			cout << card_numbers_array_[j] << '+';
		}
	}
	cout << card_numbers_array_[card_num_ - 1];
	exit(0);
}