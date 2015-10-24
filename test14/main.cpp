#include <array>
#include <iostream>

#include "MyFunction.h"

using namespace std;


class enumBase
{
public:
	enumBase(int a)
		: m_data(a)
	{}

	int m_data{ 0 };
};

// enum �� underlying type �� �����ϰ� enum class �� ����ϰ�, �������� ������Ÿ���� �������̴�. (int, unsigned, char ��)
// �׷��� ������ enum ������ �ش� ������ ������ ���� �� �ִ� ��� ���� ������ �� ������,
// enum ���� ������ ������ ���� �ƴ� ���� ��� ���� �� �ִ�...
// �׵��� �����ٴ� �β�����.
	// ����� VS2010 ������ enum �� integer.
// underlying type �� �������� ������ �⺻�� int �ε�.
// ����Ÿ���� ���� �������� ������ �տ������� 0, 1, 2, ... �� ����.
enum class TestEnum : char
{
	E1,
	E2,
	E3,
	EMAX = 1000	// underlying type �� char �� �����ϰ� 1000 �� �Ҵ��ϸ�, 1000 �� char �� �°� �߷� �����.
};

void EnumPrinter(TestEnum te)
{
	switch (te)
	{
	case TestEnum::E1:
	case TestEnum::E2:
	case TestEnum::E3:
	case TestEnum::EMAX:
		cout << "right enum: " << endl;
		break;
	default:
		cout << "default:" << (int)te << endl;
		break;
	}
}

void main()
{
	CTestMyFunction::TestMyFunction();

	TestEnum t1 = TestEnum::EMAX;


	for (int i = 0; i < 10; ++i)
	{
		TestEnum te;
		te = (TestEnum)i;

		EnumPrinter(te);
	}

	system("pause");
}