#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double evaluate_polynomial(double *coeff, int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += coeff[i] * pow(x, i);
    }
    return result;
}

double *get_coefficients(int degree) {
    double *coeff = malloc((degree + 1) * sizeof(double));
    if (coeff == NULL) return NULL;

    printf("Enter coefficients (a0, a1, a2, ... an):\n");
    for (int i = 0; i <= degree; i++) {
        printf("Enter coefficient for x^%d: ", i);
        scanf("%lf", &coeff[i]);
    }
    return coeff;
}

int main() {
    int degree = -1;
    double *coefficients = NULL;
    int choice = 1;

    while (choice != 0) {
        printf("\n1. Set/Change Polynomial Degree\n");
        printf("2. Evaluate P(x)\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int new_degree;
            printf("Enter new polynomial degree (n): ");
            scanf("%d", &new_degree);
            
            if (new_degree < 0) {
                printf("Degree must be non-negative.\n");
                continue;
            }

            double *new_coeff = realloc(coefficients, (new_degree + 1) * sizeof(double));
            if (new_coeff == NULL) {
                printf("Reallocation failed.\n");
                continue;
            }
            coefficients = new_coeff;
            degree = new_degree;

            printf("Enter coefficients (starting from a0):\n");
            for (int i = 0; i <= degree; i++) {
                printf("Enter coefficient for x^%d: ", i);
                scanf("%lf", &coefficients[i]);
            }

        } else if (choice == 2) {
            if (degree == -1) {
                printf("Please set the polynomial degree first (Option 1).\n");
                continue;
            }
            
            double x_val;
            printf("Enter x value for evaluation: ");
            scanf("%lf", &x_val);
            
            double result = evaluate_polynomial(coefficients, degree, x_val);
            printf("P(%.2lf) = %.2lf\n", x_val, result);

        } else if (choice == 0) {
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    if (coefficients != NULL) {
        free(coefficients);
        coefficients = NULL;
    }

    printf("\nProgram terminated. Memory freed. \n");
    return 0;
}