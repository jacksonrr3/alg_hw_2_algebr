#pragma once
//возведение в степень итеративное
double pow_iter(double a, long b);

//возведение в степь через степень двойки с домножением
double pow_2step(double a, long b);

//возведение в степнь через двоичное разложение показателя степени.
//сделал шаблонный вариант этой функции. 
template <typename T>
T pow_bin(T a, long b) {
	T res = 1;
	while (b > 0) {
		if (b % 2) {
			res *= a;
		}
		a *= a;
		b /= 2;
	}
	if (b > 0) { res *= a; }
	return res;
}

