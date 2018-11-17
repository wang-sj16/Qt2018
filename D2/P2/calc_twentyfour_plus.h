
#pragma once

class TwentyFourCalculatorPlus
{
public:
	void ToBinaryCode(long num);     //将十进制数编码成为二进制序列，对应储存加法和乘法的序列
	void run();     //对外算法运行接口；
	TwentyFourCalculatorPlus();     //构造函数  用于输入并初始化数据

private:
	int card_num_;                               //卡牌数量
	int target_;                                     //目标数量
	int code_array_[23] = {0};              //二进制编码数列，对应运算符
	long card_numbers_array_[24];     //储存卡牌各数字的数列
	long above_target_min_ = -1;       //比目标数量大的最小值

	long CalculateFormula();               //计算代数式的值
	void PrintResult();                          //打印代数式
};