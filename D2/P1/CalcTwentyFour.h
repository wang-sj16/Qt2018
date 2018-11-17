#ifndef TWENTYFOURCALCULATION_H
#define TWENTYFOURCALCULATION_H
#include <vector>
#include <set>

namespace std
{
	class TwentyFourCalculator
	{
	public:
		TwentyFourCalculator();      //构造函数 完成输入
		void PrintAnswer();    // 输出运行结果
		void Run();     // 对外可见的运算运行入口

	private:
		int p_numbers_[4];    //输入数字
		char p_operators_[4] = { '+','-','*','/' };  //运算符
		set<string> answer_set_;      //合法的答案存储集合

		void StartCalculation();
		//开始运算 

		double BinaryOperation(double a, double b, char opr);
		//进行二元运算  参数为运算元素和字符标识的运算符

		void GenerateAnswer(int n1, int n2, int n3, int n4, char o1, char o2, char o, int order);
		// 生成结果和算术表达式  参数代表数字和运算符
	};
}


#endif TWENTYFOURCALCULATION_H
