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
			if (i <= 0) {
				return true;
			}
		}
		return false;
	};

	// 锚杆间排距0.6-1.0m 按照0.1m下取整
	static double RestrainBoltSpace(double space) {
		if (space < 0.6) {
			space = 0.6;
		}
		else if (space > 1) {
			space = 1;
		}
		else {
			space = floor(space * 10) / 10;
		}
		return space;
	};

	// 锚索间排距  1.2m~3m  按照0.1m下取整
	static double RestrainCableSpace(double space) {
		if (space < 1.2) {
			space = 1.2;
		}
		else if (space > 3) {
			space = 3;
		}
		else {
			space = floor(space * 10) / 10;
		}
		return space;
	};

	//锚杆长度在1.6m~2.8m之间。按照0.1m上取整
	static double RestrainBoltLength(double length) {
		if (length < 1.6) {
			length = 1.6;
		}
		else if (length > 2.8) {
			length = 2.8;
		}
		else {
			length = ceil(length * 10) / 10;
		}
		return length;
	};
	//长锚索长度6m~10m之间，按照0.1m上取整
	static double RestrainCableLength(double length) {
		if (length < 6) {
			length = 6;
		}
		else if (length > 10) {
			length = 10;
		}
		else {
			length = ceil(length * 10) / 10;
		}
		return length;
	};

	// 锚固长  按照0.1m上取整 
	static double RestrainAlength(double length) {
		return ceil(length * 10) / 10;
	}
};

