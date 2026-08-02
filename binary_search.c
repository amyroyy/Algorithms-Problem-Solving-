/*  TASK 2 - Problem 2: BINARY SEARCH (Searching Algorithm)
   Binary Search finds a target value in a SORTED array by
   repeatedly cutting the search space in half:
     1. Look at the middle element
     2. If it matches the target, done
     3. If target is smaller, search the left half
     4. If target is larger, search the right half
     5. Repeat until found or search space is empty
 
   Time Complexity: O(log n) - this is what makes it fast;
                     doubling the input only adds ONE more step
   Space Complexity: O(1) - no extra memory needed (iterative version)
 
   Note: the array MUST be sorted first for binary search to work.
   This is why we run merge sort (or qsort) before searching. */
 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Returns the index of 'target' in arr[], or -1 if not found.
int binarySearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;              // found it
        } else if (arr[mid] < target) {
            low = mid + 1;           // search the right half
        } else {
            high = mid - 1;          // search the left half
        }
    }
    return -1;   // not found
}

void fillSortedRandom(int arr[], int n) {
    // fill with increasing values (already sorted, as binary search requires)
    arr[0] = rand() % 10;
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + (rand() % 10) + 1;
    }
}

//qsort comparator, used only for the small demo array below 
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    srand(time(NULL));

    //TEST CASE 1: small fixed array (to show correctness) 
    printf("=== Test Case 1: Small fixed array ===\n");
    int sample[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 72, 91};
    int sampleSize = sizeof(sample) / sizeof(sample[0]);
    qsort(sample, sampleSize, sizeof(int), compare); // ensure sorted

    int targets[] = {23, 100, 2, 91};
    for (int i = 0; i < 4; i++) {
        int result = binarySearch(sample, sampleSize, targets[i]);
        if (result != -1)
            printf("Target %d found at index %d\n", targets[i], result);
        else
            printf("Target %d NOT found in array\n", targets[i]);
    }

    //TEST CASE 2: runtime for different input sizes
    printf("\n=== Test Case 2: Runtime for different input sizes ===\n");
    int sizes[] = {1000, 100000, 10000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int* arr = (int*)malloc(n * sizeof(int));
        fillSortedRandom(arr, n);

        int target = arr[n / 2]; // search for a value we know exists

        clock_t start = clock();
        int result = binarySearch(arr, n, target);
        clock_t end = clock();

        double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Input size: %-9d Found at index: %-9d Time taken: %f seconds\n",
               n, result, timeTaken);

        free(arr);
    }

    return 0;
}
