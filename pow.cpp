#include <iostream>
#include <chrono>

//возведение в степень
double pow_iter(double a, long b) {
	long double res = 1;
	for (long i = 1; i <= b; i++) {
		res *= a;
	}
	return res;
}


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

	test_pow(pow_iter, s1, 1.0000001, 1000000000);
	test_pow(pow_2step, s2, 1.0000001, 1000000000);
	test_pow(pow_bin, s3, 1.0000001, 1000000000);
	   
	return 0;
}
