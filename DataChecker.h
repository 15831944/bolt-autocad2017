#pragma once
#include "stdafx.h"
 
class DataChecker
{
public:
	DataChecker() {};
	~DataChecker() {};
	// 该数字是否为负数
	static bool IsNegative(double num) {
		return num < 0 ? true : false;

	};
	// 该数字是否为小数
	static bool IsDecimal(double num) {
		return (num - int(num)) == 0 ? false : true;
	};

	//（锚杆根数 - 1）*间距 + 2 * 两边预留最小值应该小于巷道宽度
	static bool IsBoltNumberLeagal(double length, double num, double space) {
		return (num - 1) * space + 400 <= length ? true : false;
	};

	static bool HasZeroOrNegativeValue(std::vector<double> num) {

		for (auto i : num) {

			std::cout << i << std::endl;
			if (i <= 0) {
				return true;
			}
		}
		return false;
	};
};

