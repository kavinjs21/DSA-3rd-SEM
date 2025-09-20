//CH.SC.U4CSE24119
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("CH.SC.U4CSE24119\n");

    int n, deleteElement, i, j, found = 0;

    printf("Enter the Number of elements: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the numbers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to delete from the array: ");
    scanf("%d", &deleteElement);

    for (i = 0; i < n; i++) {
        if (arr[i] == deleteElement) {
            for (j = i; j < n - 1; j++) {
                arr[j] = arr[j + 1];
            }
            n--;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("The array after deletion is:\n");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Element not found in the array.\n");
    }

    free(arr);
    return 0;
}
