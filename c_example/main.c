#include "krome.h"
#include "krome_user.h"

#include <stdlib.h>
#include <stdio.h>

int main()
{
	krome_init();
	int i;
	double Tgas, dt, t;
	double* x = (double*)calloc(krome_nmols, sizeof(double));

	x[krome_idx_FK1] = 1.;

	Tgas = 100.;
	dt = 1.e-5;
	t = 0.;

	while(t < 5.)
	{
		dt = dt * 1.1;
		krome(x, &Tgas, &dt);
		printf("%f ", t);
		for (i = 0; i < krome_nmols; i += 1)
			printf("%f ", x[i]);
		printf("\n");
		t = t + dt;
	}

	printf("Test OK");
}
