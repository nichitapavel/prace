#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <time.h>

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

void find_range(double err_n_min, int* n_min, int* n_max) {
	double pi_r = 0.0, err_n = 0.0;
	for (int i = 1; *n_max == 0; i *= 2) {
		pi_r = pi(i);
		err_n = pi_r - M_PI;
		if (err_n_min < err_n) {
			*n_min = i;
		} else {
			*n_max = i;
		}
	}
}

int find_n(double err_n_min, int n_min, int n_max, double *pi_r, double err_n) {
	int n_tmp = 0;
	while (n_max - n_min != 1) {
		n_tmp = n_min + (n_max - n_min) / 2;
		*pi_r = pi(n_tmp);
		err_n = *pi_r - M_PI;
		if (err_n_min < err_n) {
			n_min = n_tmp;
		} else {
			n_max = n_tmp;
		}
	}
	return n_max;
}

int parse_args(const int argc, char** const argv, int* base, int* exp) {
	int arg, set_base = 0, set_exp = 0;

	while ((arg = getopt (argc, argv, "b:e:")) != -1) {
		switch (arg) {
		  case 'b':
			*base = atoi(optarg);
			set_base = 1;
			break;
		  case 'e':
			*exp = atoi(optarg);
			set_exp = 1;
			break;
		  default:
			return -1;
		  }
	}

	if( set_base ^ set_exp == 1) {
		return -1;
	}
	return 0;
}

int main(const int argc, char** const argv) {
	int base = 10, exp = -6;
	if (parse_args(argc, argv, &base, &exp) == -1) {
		printf("Set base and exponent... exiting\n");
		return -1;
	};
	double err_n_min = pow(base, exp);
	int n = 1, n_min = 0, n_max = 0;
	double pi_r = 0.0, err_n = 0.0;

	clock_t start, end;
	start = clock();
	find_range(err_n_min, &n_min, &n_max);
	n = find_n(err_n_min, n_min, n_max, &pi_r, err_n);
	end = clock();

	printf(
			"[N: %d] - [pi(N): %.50lf] - [err(pi): %.50lf] - [time in sec: %.6f]\n",
			n, pi_r, pi_r - M_PI, (float) (end - start)/CLOCKS_PER_SEC
			);
	return 0;
}
