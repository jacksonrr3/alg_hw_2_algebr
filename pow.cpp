#include <iostream>
#include <chrono>

//возведение в степень итеративное
double pow_iter(double a, long b) {
	long double res = 1;
	for (long i = 1; i <= b; i++) {
		res *= a;
	}
	return res;
}

//возведение в степь через степень двойки с домножением
double pow_2step(double a, long b) {
	long st = 1;
	long double res = a;
	while (st < b / 2) {
		res *= res;
		st += st;
	}
	while (st < b) {
		res *= a;
		++st;
	}
	return res;
}

//возведение в степнь через двоичное разложение показателя степени. 
double pow_bin(double a, long b) {
	long double res = 1;
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

//функция тестирования и определения времени работы алгоритмов возведения в степень
//выводит на экран название функции возведения в степень, аргументы, результат и время работы.
void test_pow(double(*f)(double, long), const std::string& s, double d, long l) {
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	start = std::chrono::high_resolution_clock::now();
	auto ans = f(d, l);
	end = std::chrono::high_resolution_clock::now();
	std::cout << s << "( " << d << ", " << l << "):\n " << "-" << ans << " ("<< std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << " ms)" << std::endl;
}


int main() {

	std::string s1 = "pow_iter";
	std::string s2 = "pow_2step";
	std::string s3 = "pow_bin";

	test_pow(pow_iter, s1, 1.0000001, 1000000000); //  -2.6881у+43    4112 мс
	test_pow(pow_2step, s2, 1.0000001, 1000000000); // -2.6881у+43    2035 мс
	test_pow(pow_bin, s3, 1.0000001, 1000000000); //   -2.6881у+43    0 мс
	   
	return 0;
}
