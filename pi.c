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
	int n = 0;
	double pi_r = 0.0;
	do {
		n++;
		pi_r = pi(n);
	} while (err_n_min < pi_r - M_PI);

	printf("[N: %d] - [pi_N: %.16lf] - [err(pi): %.16lf]\n", n, pi_r, pi_r - M_PI);
	return 0;
}
