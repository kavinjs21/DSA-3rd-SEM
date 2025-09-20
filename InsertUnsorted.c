//CH.SC.U4CSE24119
#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("CH.SC.U4CSE24119\n");

    int n, insert, pos;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid size.\n");
        return 1;
    }

    int *arr = (int *)malloc((n + 1) * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the number to insert: ");
    scanf("%d", &insert);

    printf("Enter the position to insert (0 to %d): ", n);
    scanf("%d", &pos);

    if (pos < 0 || pos > n) {
        printf("Invalid position.\n");
        free(arr);
        return 1;
    }

    for (int i = n; i > pos; i--) {
        arr[i] = arr[i - 1];
    }

    arr[pos] = insert;
    n++;

    printf("Array after insertion: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
