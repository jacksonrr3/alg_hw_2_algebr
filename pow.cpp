
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

/*
//реализовал эту функцию в виде шаблона, определение функции в заголовочном файле
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
}*/
