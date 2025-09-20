#include <stdio.h>

int a = 1000, b, c, d;

int bse() {
    printf("Enter the amount you want to deposit: ");
    scanf("%d", &c);
    a = a + c;
    printf("\nYour balance is %d\n", a);
    return 0;
}

int wid() {
    printf("Enter the amount you want to withdraw: ");
    scanf("%d", &c);
    if (a >= c) {
        a = a - c;
        printf("\nYour balance is %d\n", a);
    } else {
        printf("\nInsufficient balance\n");
    }
    return 0;
}

int chkbal() {
    printf("Your balance is %d\n", a);
    return 0;
}

void main() {
    printf("CH.SC.U4CSE24119_Kavin\n");
    while (1) {
        printf("\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &b);

        switch (b) {
            case 1:
                bse();
                break;
            case 2:
                wid();
                break;
            case 3:
                chkbal();
                break;
            case 4:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
