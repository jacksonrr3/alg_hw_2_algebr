#include <cmath>
#include <vector>
#include <algorithm>
#include "pow.h"

//поиск n-го числа Фибоначи через рекурсию.
double fib_rec(size_t n) {
	if (n <= 2) { return 1; }
	else { return fib_rec(n - 1) + fib_rec(n - 2); }
}

//поиск n-го числа Фибоначи через рекурсию, с улучшением алгоритма. 
//добавляем массив в который сохраняются вычисленные значения чисел Фибоначи,
//тем самым избавляемся от повторных вычислений и уменьшаем количество веток
//в тестах время итерационные алгоритмы показывают одинаковое, так как скоре евсего 
//компилятор сам оптимизирует обычный рекурсивный алгоритм, избавляя его от повторных вычислений
double fib_rec_upgrade(size_t n) {
	static std::vector<double> m(1000, 0);
	if (m[n] != 0) { return m[n]; }
	else {
		if (n <= 2) { return 1; }
		else { return fib_rec(n - 1) + fib_rec(n - 2); }
	}
}


//поиск n-го числа Фибоначи через итерацию. гораздо быстрее, чем рекурсивный алгоритм. 
//экономит память, всего три переменные long double
double fib_iter(size_t n) {
	double first = 1;
	double second = 1;
	for (size_t i = 3; i <= n; i++) {
		double temp = first + second;
		second = first;
		first = temp;
	}
	return first;
}

//поиск n-го числа Фибоначи через формулу золотого сечения. 
//для вычисления степени используется функция вычисления степени через двоичное разложение показателя степени
double fib_gold(size_t n) {
	double f = (1 + std::sqrt(5)) / 2;
	return double((pow_bin<double>(f, n)) / std::sqrt(5) + 0.5);
}

//Дополнительный класс для возведения в степень матриц размерности 2 х 2
class Matrix {
	Matrix() {
		_m = new double[4];
		_m[0] = 1;
		_m[1] = 1;
		_m[2] = 1;
		_m[3] = 0;
	}

	~Matrix() {
		delete[] _m;
	};


	Matrix& operator=(Matrix& other) {
		std::swap(_m, other._m);
		return *this;
	}

	Matrix& operator*=(const Matrix& other) {
		Matrix temp;
		temp._m[0] = _m[0] * other._m[0] + _m[1] * other._m[2];
		temp._m[1] = _m[0] * other._m[1] + _m[1] * other._m[3];
		temp._m[2] = _m[2] * other._m[0] + _m[3] * other._m[2];
		temp._m[3] = _m[2] * other._m[1] + _m[3] * other._m[3];
		*this = temp;
		return *this;
	}

	Matrix& stepen_n(size_t n) {
		Matrix one;
		n -= 1;
		while (n > 1) {
			if (n % 2) {
				(*this)*= one;
			}
			one *= one;
			n /= 2;
		}
		if (n > 0) { (*this)*= one; }
		return *this;
	}

	double* _m;

	friend double fib_matrix(size_t n);
};

//Алгоритм поиска чисел Фибоначчи через умножение матриц
double fib_matrix(size_t n) {
	if (n <= 2) { return 1; }
	else {
		Matrix ans;
		return (ans.stepen_n(n-1))._m[0];
	}
}
