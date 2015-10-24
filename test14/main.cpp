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

// enum 은 underlying type 을 지정하건 enum class 를 사용하건, 실질적인 데이터타입은 정수형이다. (int, unsigned, char 등)
// 그렇기 때문에 enum 변수는 해당 정수형 변수가 취할 수 있는 모든 값을 저장할 수 있으며,
// enum 에서 지정한 열거형 값이 아닌 값을 들고 있을 수 있다...
// 그동안 몰랐다니 부끄럽다.
	// 참고로 VS2010 까지는 enum 은 integer.
// underlying type 을 지정하지 않으면 기본은 int 인듯.
// 열거타입의 값을 지정하지 않으면 앞에서부터 0, 1, 2, ... 로 증가.
enum class TestEnum : char
{
	E1,
	E2,
	E3,
	EMAX = 1000	// underlying type 을 char 로 지정하고 1000 을 할당하면, 1000 이 char 에 맞게 잘려 저장됨.
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