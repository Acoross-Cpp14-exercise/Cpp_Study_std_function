#include <array>
#include <iostream>

#include <memory>

#include "MyFunction.h"

using namespace std;


namespace EnumTester
{
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

	void TestEnumFunc()
	{
		TestEnum t1 = TestEnum::EMAX;


		for (int i = 0; i < 10; ++i)
		{
			TestEnum te;
			te = (TestEnum)i;

			EnumPrinter(te);
		}
	}
}


class CBaseOfAll
{
public:
	virtual ~CBaseOfAll() = default;
	virtual void Call() = 0;
};

template<class _T>
class HaveLambda
	: _T, public CBaseOfAll
{
public:
	using _MyLambdaT = _T;
	HaveLambda(_T a)
		: _T(a), CBaseOfAll()
	{	
	}

	virtual void Call() override
	{
		(*this)();
	}

private:
	int* a;	
};

class OnlyHavePointer
{
private:
	int* a;
};

class IHaveArray
{
public:
	int arr[200];
};

void GiveArrayAsArgument(IHaveArray arr)	// arr 객체가 복사생성되며 arr.arr 도 복사되었다.
{
	cout << arr.arr[0] << endl;
	size_t siz = _countof(arr.arr);
	if (siz > 0)
		cout << arr.arr[siz - 1] << endl;

	arr.arr[0] = 200;
}

void PassArrayByValue(int arr[200])		// reference 로 넘어간다. 사실 복사되지 않는다.
{
	cout << arr[0] << endl;
	cout << arr[199] << endl;
	arr[0] = 200;
}

void main()
{
	//CTestMyFunction::TestMyFunction();
	//EnumTester::TestEnumFunc();
	
	int rarr[200];
	rarr[0] = 1;
	rarr[199] = 200;
	PassArrayByValue(rarr);
	cout << rarr[0] << endl;
	
	IHaveArray arr;

	for (int i = 0; i < _countof(arr.arr); ++i)
	{
		arr.arr[i] = i;
	}

	IHaveArray arr2 = arr;	// class 내부의 array 값이 복사된다...

	GiveArrayAsArgument(arr);

	cout << arr.arr[0] << endl;

	auto lambda = []()
	{
		cout << "lambda" << endl;
	};

	HaveLambda<decltype(lambda)> dd(lambda);
	cout << sizeof(dd) << endl;
	
	auto lambda2 = []()
	{
		cout << "lambda2" << endl;
	};

	HaveLambda<decltype(lambda2)> dd2(lambda2);

	array<CBaseOfAll*, 5> arrayOfBaseIsLambda;
	arrayOfBaseIsLambda[0] = &dd;
	arrayOfBaseIsLambda[1] = &dd2;

	arrayOfBaseIsLambda[0]->Call();
	arrayOfBaseIsLambda[1]->Call();


	OnlyHavePointer cc;
	cout << sizeof(cc) << endl;
	
	{
		auto deleter = [](OnlyHavePointer* pPointer)
		{
			cout << "hahahaha" << endl;

			delete pPointer;
		};

		unique_ptr<OnlyHavePointer, decltype(deleter)> pUnique(nullptr, deleter);
		pUnique.reset(new OnlyHavePointer);

		cout << sizeof(pUnique) << endl;
	}

	
	{
		auto deleter2 = [&cc](OnlyHavePointer* pPointer)
		{
			cout << "hahahaha" << endl;

			delete pPointer;
		};

		unique_ptr<OnlyHavePointer, decltype(deleter2)> pUnique(nullptr, deleter2);
		pUnique.reset(new OnlyHavePointer);

		cout << sizeof(pUnique) << endl;
	}


	cout << "git ignore test" << endl;

	system("pause");
}