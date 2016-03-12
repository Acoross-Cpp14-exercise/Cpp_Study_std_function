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

void GiveArrayAsArgument(IHaveArray arr)	// arr ��ü�� ��������Ǹ� arr.arr �� ����Ǿ���.
{
	cout << arr.arr[0] << endl;
	size_t siz = _countof(arr.arr);
	if (siz > 0)
		cout << arr.arr[siz - 1] << endl;

	arr.arr[0] = 200;
}

void PassArrayByValue(int arr[200])		// reference �� �Ѿ��. ��� ������� �ʴ´�.
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

	IHaveArray arr2 = arr;	// class ������ array ���� ����ȴ�...

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