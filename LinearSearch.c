//CH.SC.U4CSE24119
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("CH.SC.U4CSE24119\n");

    int n, target, found = 0;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to search: ");
    scanf("%d", &target);

    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            printf("Number %d found at index %d.\n", target, i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Number %d not found in the array.\n", target);
    }

    free(arr);
    return 0;
}
