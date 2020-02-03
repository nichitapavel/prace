e1.c = pi.e1.c
e2.c = pi.e2.c
e3.c = pi.e3.c

e1 = e1
e2 = e2
e3 = e3

omp = omp
dbg = dbg

e1_omp_dbg = $(e1)-$(omp)-$(dbg)
e1_omp = $(e1)-$(omp)
e1_dbg = $(e1)-$(dbg)

e2_omp_dbg = $(e2)-$(omp)-$(dbg)
e2_omp = $(e2)-$(omp)
e2_dbg = $(e2)-$(dbg)

e3_omp_dbg = $(e3)-$(omp)-$(dbg)
e3_omp = $(e3)-$(omp)
e3_dbg = $(e3)-$(dbg)

all: e1_omp_dbg e1_omp e1_dbg e1 e2_omp_dbg e2_omp e2_dbg e2 e3_omp_dbg e3_omp e3_dbg e3

e1_omp_dbg:
	gcc -g -fopenmp $(e1.c) -o prace-pi.$(e1_omp_dbg) -lm
e1_omp:
	gcc -fopenmp $(e1.c) -o prace-pi.$(e1_omp) -lm
e1_dbg:
	gcc -g $(e1.c) -o prace-pi.$(e1_dbg) -lm
e1:
	gcc $(e1.c) -o prace-pi.$(e1) -lm

e2_omp_dbg:
	gcc -g -fopenmp $(e2.c) -o prace-pi.$(e2_omp_dbg) -lm
e2_omp:
	gcc -fopenmp $(e2.c) -o prace-pi.$(e2_omp) -lm
e2_dbg:
	gcc -g $(e2.c) -o prace-pi.$(e2_dbg) -lm
e2:
	gcc $(e2.c) -o prace-pi.$(e2) -lm

e3_omp_dbg:
	gcc -g -fopenmp $(e3.c) -o prace-pi.$(e3_omp_dbg) -lm
e3_omp:
	gcc -fopenmp $(e3.c) -o prace-pi.$(e3_omp) -lm
e3_dbg:
	gcc -g $(e3.c) -o prace-pi.$(e3_dbg) -lm
e3:
	gcc $(e3.c) -o prace-pi.$(e3) -lm

clean:
	rm prace*
