/*
 *	optional -- 使用容器语义,包装了可能产生无效值得对象,实现了未初始化的概念 收入C++17标准
 *
 * 
 */

#include <boost\optional.hpp>
using namespace boost;

#include <iostream>
#include <vector>
#include <math.h>
using namespace std;


optional<double> calc(int x){
	return optional<double>(x != 0, 1.0/x);			// 条件构造函数
}

optional<double> sqrt_op(int x){
	return optional<double>(x >= 0, sqrt(x));		// 条件构造函数
}

void test_optional_usage(){
	optional<int> op0;						// 一个未初始化的optional对象
	optional<int> op1(none);				// 同上 使用none未初始化对象

	assert(!op0);							// bool测试
	assert(op0 == op1);						// 比较两个optional对象

	assert(op1.value_or(253) == 253);		// value_or获取默认值,如果op1未初始化,则返回传入参数253
	cout << op1.value_or_eval([](){return 874;}) << endl;	//使用函数对象

	optional<string> ops("test");
	cout << *ops << endl;
		

	ops.emplace("monado", 3);		// 就地创建一个字符,没有拷贝代价
	assert(*ops == "mon");			// 深比较 非浅比较

	vector<int> v(10);
	optional<vector<int>&> opv(v);
	assert(opv);

	opv->push_back(5);
	assert(opv->size() == 11);
	opv = none;						// 置于未初始化状态
	assert(!opv);

	//make_optional
	auto x = make_optional(5);		// make_optional无法推导出T引用类型的optional对象(optional<T&>)
	assert(*x == 5);
	auto y = make_optional<double>((*x > 10), 1.0);		// 条件不足,无法推导出y
	assert(!y);
}


int main(){
	test_optional_usage();
	return 0;
}