#include <stdio.h>
#include <limits.h>
#include <math.h>

#define N_ARRAY 7

double pi_n(int n, int i) {
	return 1.0 / (1 + pow(((i - 0.5) / n), 2));
}

double pi(int n) {
	double pi = 0.0;

	#pragma omp parallel for reduction (+ : pi)
	for (int i = 1; i <= n; ++i) {
		pi += pi_n(n, i);
	}
	return 4.0 / n * pi;
}

int main(const int argc, const char** argv) {
	double err_n_min = pow(10, -6);
	int n = 1, n_min = 0, n_max = 0;
	double pi_r = 0.0, err_n = 0.0;
	do {
		pi_r = pi(n);
		err_n = pi_r - M_PI;
		if (err_n_min < err_n) {
			n_min = n;
			n *= 2;
		} else {
			n_max = n;
		}
	} while (n_max == 0);

	while (n_max - n_min != 1) {
		int n_tmp = n_min + (n_max - n_min) / 2;
		pi_r = pi(n_tmp);
		err_n = pi_r - M_PI;
		if (err_n_min < err_n) {
			n_min = n_tmp;
		} else {
			n_max = n_tmp;
		}

	}

	printf("[N: %d] - [pi_N: %.16lf] - [err(pi): %.16lf]\n", n_max, pi_r, pi_r - M_PI);
	return 0;
}
