#pragma once
#include "stdafx.h"
 
class DataChecker
{
public:
	DataChecker() {};
	~DataChecker() {};
	// �������Ƿ�Ϊ����
	static bool IsNegative(double num) {
		return num < 0 ? true : false;

	};
	// �������Ƿ�ΪС��
	static bool IsDecimal(double num) {
		return (num - int(num)) == 0 ? false : true;
	};

	//��ê�˸��� - 1��*��� + 2 * ����Ԥ����СֵӦ��С��������
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

