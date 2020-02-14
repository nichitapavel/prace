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
	for (int i = 0; i < n; i++) {
		pi += pi_n(n, i+1);
	}
	return 4.0 / n * pi;
}

int main(const int argc, const char** argv) {
	printf("Max int is: %d\n", INT_MAX);
	int n_list[N_ARRAY] = {1, 2, 10, 50, 100, 500, INT_MAX};
	for (int i = 0; i < N_ARRAY; ++i) {
		double pi_r = pi(n_list[i]);
		printf("[N: %d] - [pi(N): %.50lf] - [err(pi): %.50lf]\n", n_list[i], pi_r, pi_r - M_PI);
	}
	return 0;
}
