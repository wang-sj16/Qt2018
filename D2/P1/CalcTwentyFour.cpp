
#include <iostream>
#include <string>
#include "CalcTwentyFour.h"
#define TARGET 24                //目标为24，可更换
#define EPSILON 0.001          //允许误差，用于浮点数除法导致的误差
using namespace std;

TwentyFourCalculator::TwentyFourCalculator()
{
	//获取输入并初始化数组
	for (int i = 0; i < 4; i++)
	{
		cin >> p_numbers_[i];
		if ((p_numbers_[i] > 13) || (p_numbers_[i] < 1))
		{
			cout << "Input Invalid!." << endl;
			exit(0);
		} // 判断输入合法性
	}
}

void TwentyFourCalculator::StartCalculation()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				for (int t = 0; t < 4; t++)
				{
					if ((i != j) && (i != k) && (i != t) && (j != k) && (j != t) && (k != t))
					{
						int n1, n2, n3, n4;
						n1 = p_numbers_[i];
						n2 = p_numbers_[j];
						n3 = p_numbers_[k];
						n4 = p_numbers_[t];
						for (int order = 0; order < 5; ++order)
						{
							for (int l = 0; l < 4; l++)
								for (int m = 0; m < 4; m++)
									for (int n = 0; n < 4; n++)
									{
										GenerateAnswer(n1, n2, n3, n4, p_operators_[l], p_operators_[m], p_operators_[n], order);
									}
						}
					}
					else
					{
						continue;
					}
				}
			}
		}
	}
	PrintAnswer();    // 输出所有答案
}

void TwentyFourCalculator::Run()
{
	StartCalculation();
}


double TwentyFourCalculator::BinaryOperation(double a, double b, char oprt)
{
	switch (oprt)
	{
	case '+':
		return a + b;
		break;
	case '-':
		return a - b;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		if (b == 0) { return -99999; }    //对除零做出返回
		else { return a / b; }
		break;
	}
}


void TwentyFourCalculator::GenerateAnswer(int num1, int num2, int num3, int num4, char opr1, char opr2, char opr3, int order)
{
	string str1, str2, str3, str4, target;
	str1 = to_string(num1);
	str2 = to_string(num2);
	str3 = to_string(num3);
	str4 = to_string(num4);
	double result = 0;  // 记录当前运算结果
	switch (order)
	{
		case 0:             //     A?(B?(C?D))型
			result = BinaryOperation(num3, num4, opr3);
			result = BinaryOperation(num2, result, opr2);
			result = BinaryOperation(num1, result, opr1);

			if (abs(result - TARGET) < EPSILON)
			{
				string answer = str1 + opr1 + "(" + str2 + opr2 + "(" + str3 + opr3 + str4 + "))";
				answer_set_.insert(answer);
			}
			break;

		case 1:            //     A?((B?C)?D)型
			result = BinaryOperation(num2, num3, opr2);
			result = BinaryOperation(result, num4, opr3);
			result = BinaryOperation(num1, result, opr1);

			if (abs(result - TARGET) < EPSILON)
			{
				string answer = str1 + opr1 + "((" + str2 + opr2 + str3 + ")" + opr3 + str4 + ")";
				answer_set_.insert(answer);
			}
			break;
		case 2:              //   ((A?B)?C)?D型
			result = BinaryOperation(num1, num2, opr1);
			result = BinaryOperation(result, num3, opr2);
			result = BinaryOperation(result, num4, opr3);

			if (abs(result - TARGET) < EPSILON)
			{
				string answer = "((" + str1 + opr1 + str2 + ")" + opr2 + str3 + ")" + opr3 + str4;
				answer_set_.insert(answer);
			}
			break;

		case 3:           //     (A?(B?C))?D型
			result = BinaryOperation(num2, num3, opr2);
			result = BinaryOperation(num1, result, opr1);
			result = BinaryOperation(result, num4, opr3);

			if (abs(result - TARGET) < EPSILON)
			{
				string answer = "(" + str1 + opr1 + "(" + str2 + opr2 + str3 + "))" + opr3 + str4;
				answer_set_.insert(answer);
			}
			break;
		
		case 4:             //     (A?B)?(C?D)型
			result = BinaryOperation(num1, num2, opr1);
			double temp = BinaryOperation(num3, num4, opr3);
			result = BinaryOperation(result, temp, opr2);

			if (abs(result - TARGET) < EPSILON)
			{
				string answer = "(" + str1 + opr1 + str2 + ")" + opr2 + "(" + str3 + opr3 + str4 + ")";
				answer_set_.insert(answer);
			}
			break;
	}
}


void TwentyFourCalculator::PrintAnswer()
{
	if (answer_set_.empty())
	{
		cout << "no" << endl;
	}

	set<string>::iterator iter = answer_set_.begin();
	while (iter != answer_set_.end())
	{
		cout << *iter << endl;
		iter++;
	}
}
