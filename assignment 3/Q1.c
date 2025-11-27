
#include <stdio.h>
#include <math.h>

double calculateRepayment(double loan, double interestRate, int years) {
    static int currentYear = 1;

    if (years == 0 || loan <= 0.1) {
        currentYear = 1; 
        return 0;
    }

    double payment = (loan * interestRate) / (1 - pow(1 + interestRate, -years));
    
    double interest = loan * interestRate;
    double principalPaid = payment - interest;
    double remainingLoan = loan - principalPaid;

    if (remainingLoan < 1.0) remainingLoan = 0;

    printf("Year %d: Remaining loan = %.2f (Paid: %.2f)\n", 
           currentYear, remainingLoan, payment);

    currentYear++; 

    return payment + calculateRepayment(remainingLoan, interestRate, years - 1);
}

int main() {
    double loanAmount, rateInput;
    int duration;

    printf("--- Loan Calculator ---\n");
    
    printf("Enter Loan Amount: ");
    scanf("%lf", &loanAmount);

    printf("Enter Annual Interest Rate (%%): ");
    scanf("%lf", &rateInput);

    printf("Enter Duration (Years): ");
    scanf("%d", &duration);

    double decimalRate = rateInput / 100.0;

    printf("\n--- Repayment Schedule ---\n");
    double totalRepayment = calculateRepayment(loanAmount, decimalRate, duration);
    
    printf("--------------------------\n");
    printf("Total Amount Repaid: %.2f\n", totalRepayment);
    printf("Total Interest Paid: %.2f\n", totalRepayment - loanAmount);

    return 0;
}
