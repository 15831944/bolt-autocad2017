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
			if (i <= 0) {
				return true;
			}
		}
		return false;
	};

	// ê�˼��ž�0.6-1.0m ����0.1m��ȡ��
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

	// ê�����ž�  1.2m~3m  ����0.1m��ȡ��
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

	//ê�˳�����1.6m~2.8m֮�䡣����0.1m��ȡ��
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
	//��ê������6m~10m֮�䣬����0.1m��ȡ��
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

	// ê�̳�  ����0.1m��ȡ�� 
	static double RestrainAlength(double length) {
		return ceil(length * 10) / 10;
	}
};

