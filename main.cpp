#include <iostream>
#include <chrono>
#include "fib.h"
#include "pow.h"

//������� ������������ � ����������� ������� ������ ���������� ���������� � �������
//������� �� ����� �������� ������� ���������� � �������, ���������, ��������� � ����� ������.
void test_pow(double(*f)(double, long), const std::string& s, double d, long l) {
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	auto ans = f(d, l);
	end = std::chrono::high_resolution_clock::now();
	std::cout << s << "( " << d << ", " << l << "):\n " << "- " << ans << " ("<< std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms)" << std::endl;
}

//������� ������������ � ����������� ������� ������ ���������� ������ ����� ���������
//������� �� ����� �������� ������� ���������� � �������, ���������, ��������� � ����� ������.
void test_fib(double (*f)(size_t), const std::string& s, size_t n) {
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	auto ans = f(n);
	end = std::chrono::high_resolution_clock::now();
	std::cout << s << "( " << n << "):\n " << "- " << ans << " (" << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms)" << std::endl;
}


int main() {
	
	std::string s1 = "pow_iter";
	std::string s2 = "pow_2step";
	std::string s3 = "pow_bin";

	test_pow(pow_iter, s1, 1.0000001, 1000000000);			 //2.6881e+43,    3853 ��
	test_pow(pow_2step, s2, 1.0000001, 1000000000);			 //2.6881e+43,    1654 ��
	test_pow(pow_bin<double>, s3, 1.0000001, 1000000000);    //2.6881e+43,    0 ��
	
	std::string s4 = "fib_rec";
	std::string s5 = "fib_rec_upgrade";
	std::string s6 = "fib_iter";
	std::string s7 = "fib_gold";
	std::string s8 = "fib_matrix";

	test_fib(fib_rec, s4, 42);          //2.67914e+08, 10569 ��
	test_fib(fib_rec_upgrade, s5, 42);	//2.67914e+08, 10338 �� 
	test_fib(fib_iter, s6, 1001);		//7.03304e+208, 0 ��
	test_fib(fib_gold, s7, 1001);		//7.03304e+208, 0 ��
	test_fib(fib_matrix, s8, 1001);		//7.03304e+208, 0 ��
	
	return 0;
}