#include <cmath>
#include <vector>
#include <algorithm>
#include "pow.h"


//ïîèñê n-ãî ÷èñëà Ôèáîíà÷è ÷åðåç ðåêóðñèþ.
double fib_rec(size_t n) {
	if (n <= 2) { return 1; }
	else { return fib_rec(n - 1) + fib_rec(n - 2); }
}

//ïîèñê n-ãî ÷èñëà Ôèáîíà÷è ÷åðåç ðåêóðñèþ, ñ óëó÷øåíèåì àëãîðèòìà. 
//äîáàâëÿåì ìàññèâ â êîòîðûé ñîõðàíÿþòñÿ âû÷èñëåííûå çíà÷åíèÿ ÷èñåë Ôèáîíà÷è,
//òåì ñàìûì èçáàâëÿåìñÿ îò ïîâòîðíûõ âû÷èñëåíèé è óìåíüøàåì êîëè÷åñòâî âåòîê
//â òåñòàõ âðåìÿ èòåðàöèîííûå àëãîðèòìû ïîêàçûâàþò îäèíàêîâîå, òàê êàê ñêîðå åâñåãî 
//êîìïèëÿòîð ñàì îïòèìèçèðóåò îáû÷íûé ðåêóðñèâíûé àëãîðèòì, èçáàâëÿÿ åãî îò ïîâòîðíûõ âû÷èñëåíèé
double fib_rec_upgrade(size_t n) {
	static std::vector<double> m(1000, 0);
	if (m[n] != 0) { return m[n]; }
	else {
		if (n <= 2) { return 1; }
		else { return fib_rec(n - 1) + fib_rec(n - 2); }
	}
}


//ïîèñê n-ãî ÷èñëà Ôèáîíà÷è ÷åðåç èòåðàöèþ. ãîðàçäî áûñòðåå, ÷åì ðåêóðñèâíûé àëãîðèòì. 
//ýêîíîìèò ïàìÿòü, âñåãî òðè ïåðåìåííûå long double
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

//ïîèñê n-ãî ÷èñëà Ôèáîíà÷è ÷åðåç ôîðìóëó çîëîòîãî ñå÷åíèÿ. 
//äëÿ âû÷èñëåíèÿ ñòåïåíè èñïîëüçóåòñÿ ôóíêöèÿ âû÷èñëåíèÿ ñòåïåíè ÷åðåç äâîè÷íîå ðàçëîæåíèå ïîêàçàòåëÿ ñòåïåíè
double fib_gold(size_t n) {
	double f = (1 + std::sqrt(5)) / 2;
	return double((pow_bin<double>(f, n)) / std::sqrt(5) + 0.5);
}

//Äîïîëíèòåëüíûé êëàññ äëÿ âîçâåäåíèÿ â ñòåïåíü ìàòðèö ðàçìåðíîñòè 2 õ 2
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

//Àëãîðèòì ïîèñêà ÷èñåë Ôèáîíà÷÷è ÷åðåç óìíîæåíèå ìàòðèö
double fib_matrix(size_t n) {
	if (n <= 2) { return 1; }
	else {
		Matrix ans;
		return (ans.stepen_n(n-1))._m[0];
	}
}
