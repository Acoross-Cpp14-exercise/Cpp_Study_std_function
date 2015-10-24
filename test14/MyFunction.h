#pragma once

#include <iostream>

using namespace std;

namespace Acoross
{
	template <class _Ret, class... _Types>
	class _FuncDataBase
	{
	public:
		virtual _Ret Call(_Types... args) = 0;
	};

	template<class Ty, class _Ret, class... _Types>
	class _FuncDataImpl : public _FuncDataBase<_Ret, _Types...>
	{
	public:
		_FuncDataImpl() = delete;
		_FuncDataImpl(Ty& data)
			: m_data(data)
		{
		}

		virtual _Ret Call(_Types... args)
		{
			return m_data(args...);
		}

		Ty m_data;
	};

	template <class T>
	class function;

	template<class _Ret, class... _Types>
	class function<_Ret (_Types...)>
	{
	public:
		template<class Ty>
		function(Ty val)
		{
			if (m_Data)
				delete m_Data;

			m_Data = new _FuncDataImpl<Ty, _Ret, _Types...>(val);
		}
		~function()
		{
			if (m_Data)
				delete m_Data;
		}
		_Ret operator()(_Types... args)
		{
			return m_Data->Call(args...);
		}

		_FuncDataBase<_Ret, _Types...>* m_Data{ nullptr };
	};
}

class CTestMyFunction
{
public:
	static int Foo(int a)
	{
		cout << "Foo(" << a << ")" << endl;
		return a;
	}

	class FooCl
	{
	public:
		FooCl(int a)
			: m_nA(a)
		{}

		int operator() (int lhs)
		{
			return m_nA + lhs;
		}

	private:
		int m_nA;
		int m_data[20]{ 0, };
	};

	static void TestMyFunction()
	{
		FooCl f(10);

		Acoross::function<int(int)> FS(f);
		cout << FS(1) << endl;

		Acoross::function<int(int)> FS2 = Foo;
		cout << FS2(2) << endl;

		int n = 100;
		auto f3 = [n](int a)->int
		{
			return n + a;
		};

		Acoross::function<int(int)> FS3(f3);
		cout << FS3(3) << endl;
	}
};