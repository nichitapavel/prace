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
	for (int i = 1; i <= n; ++i) {
		pi += pi_n(n, i);
	}
	return 4.0 / n * pi;
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
	int n = 0;
	double pi_r = 0.0;

	clock_t start, end;
	start = clock();
	do {
		n++;
		pi_r = pi(n);
	} while (err_n_min < pi_r - M_PI);

	end = clock();
	printf(
			"[N: %d] - [pi(N): %.16lf] - [err(pi): %.16lf] - [time in sec: %.6f]\n",
			n, pi_r, pi_r - M_PI, (float) (end - start)/CLOCKS_PER_SEC
			);
	return 0;
}
