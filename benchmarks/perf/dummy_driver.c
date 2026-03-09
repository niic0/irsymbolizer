#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if(argc != 2) {
        printf("Usage: %s <size>\n", argv[0]);
        printf("- size: vector size\n");
        return 0;
    }

    int size = atoi(argv[1]);

    printf("- Start\n");

    printf("Malloc 3 * sizeof(double) * %d...\n", size);

    double *x = (double *)malloc(sizeof(double) * size);
    double *y = (double *)malloc(sizeof(double) * size);
    double *z = (double *)malloc(sizeof(double) * size);

    srand(420);

    printf("Initialisation of size %d...\n", size);

    for(int i = 0; i<size; i++) {
        x[i] = rand();
        y[i] = rand();
        z[i] = rand();
    }

    printf("Compute...\n");

    for(int i = 0; i<size; i++) {
        x[i] -= y[i]/z[i];
        for(int j = 0; j<size; j++) {
            y[j] += x[j] * x[i];
            for (int k = 0; k<size; k++) {
                z[k] += x[k] * y[i] * z[j];
	    }
	}
    }

    printf("Free...\n");

    free(x);
    free(y);
    free(z);

    printf("- Ended\n");

    return 0;
}
