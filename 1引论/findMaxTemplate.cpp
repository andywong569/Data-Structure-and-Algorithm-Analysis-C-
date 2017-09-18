/**
 *  \file findMaxTemplate.cpp
 *  \brief 寻找最大值的模板类以及函数对象的operator()重载
 */
 
#ifndef FINDMAXTEMPLATE_H
#define FINDMAXTEMPLATE_H

/**
 *  Return the maximum item in array a.
 *  Assumes a.size() > 0.
 *  Comparable objects must provide operator< and operator=
 *  V1.0
 */
template<typename Comparable>
const Comparable& findMax(const vector<Comparable>& a)
{
	int maxIndex = 0;
	for(int i = 1; i < a.size(); ++i)
	{
		if(a[maxIndex] < a[i])
			maxIndex = i;
	}
	return a[maxIndex];
}


/**
 *  Generic findMax, with a function object, C++ style.
 *  Precondition: a.size() > 0.
 *  V2.0
 */
template<typename Object, typename Comparable>
const Object& findMax(const vector<Object>& arr, Comparable isLessThan)
{
	int maxIndex = 0;
	for(int i = 1; i < arr.size(); ++i)
	{
		if(isLessThan(arr[max], arr[i]))
			maxIndex = i;
	}
	return arr[maxIndex];
}

#include <functional>
template<typename Object>
const Object& findMax(const vector<Object>& arr)
{
	return findMax(arr, less<Object>());
}

/**
 *  函数对象：定义一个包含零个数据和一个人成员函数的类，然后传递这个类的实例
 *  从效果上看，通过将其放在对象中实现函数的传递
 *  1、不是使用函数名来调用函数，而是使用操作符重载；operator()
 *  2、当调用operator()时，cmp.operator()(x, y)可以缩写为cmp(x, y)，这看起来就像函数调用
 */
class CaseInsensitiveCompare
{
	bool operator()(const string& lhs, const string& rhs) const
	{
		return stricmp(lhs.c_str(), rhs.c_str()) < 0;
	}
};

class Employee
{
public:
	void setValue(const string& name, double salary)
	{
		m_name = name;
		m_salary = salary;
	}
	
	const string& getName() const
	{
		return m_name;
	}
	
	void print(ostream& os) const
	{
		os<<m_name<<" ("<<m_salary<<")";
	}
	bool operator<(const Employee& rhs) const
	{
		return this->m_salary < rhs.m_salary;
	}
	
	// Other general accessors and mutators, not shown
	
private:
	string m_name;
	double m_salary;
};

ostream& operator<<(ostream& os, const Employee& rhs)
{
	rhs.print(os);
}

int main()
{
	/**
	 *  V1.0
	 */
	vector<Employee> v(3);
	
	v[0].setValue("George Bush", 400 000.00);
	v[1].setValue("Bill Gates", 2 000 000 000.00);
	v[2].setValue("Dr. Phil", 13 000 000.00);
	cout<<findMax(v)<<endl;
	
	/**
	 *  V2.0
	 */
	vector<string> arr(3);
	arr[0] = "ZEBRA";
	arr[1] = "alligator";
	arr[2] = "crocodile";
	cout << findMax(arr, CaseInsensitiveCompare()) << endl;
	cout << findMax(arr) << endl;
	
	return 0;
}

#endif	// FINDMAXTEMPLATE_H