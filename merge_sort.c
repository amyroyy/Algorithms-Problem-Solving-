/*  TASK 2 - Problem 1: MERGE SORT (Sorting Algorithm)
  Merge Sort works by:
     1. Splitting the array into two halves (divide)
     2. Sorting each half recursively (conquer)
     3. Merging the two sorted halves back together (combine)
 
   Time Complexity: O(n log n) in all cases (best/average/worst)
   Space Complexity: O(n) - needs extra array space to merge   */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Merge two sorted sub-arrays: arr[left..mid] and arr[mid+1..right] 
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;   // size of left sub-array
    int n2 = right - mid;      // size of right sub-array

    // Temporary arrays to hold the two halves
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Merge the two temp arrays back into arr[left..right], in sorted order
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // Copy any remaining elements
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }

    free(L);
    free(R);
}

// Recursively divide the array and sort each half 
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);       // sort left half
        mergeSort(arr, mid + 1, right);  // sort right half
        merge(arr, left, mid, right);    // merge the sorted halves
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// Fill an array with random numbers, for performance testing
void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = rand() % 100000;
}

int main() {
    srand(time(NULL));

    //TEST CASE 1: small, fixed array (to show correctness) 
    printf("=== Test Case 1: Small fixed array ===\n");
    int sample[] = {38, 27, 43, 3, 9, 82, 10};
    int sampleSize = sizeof(sample) / sizeof(sample[0]);
    printf("Before sorting: ");
    printArray(sample, sampleSize);
    mergeSort(sample, 0, sampleSize - 1);
    printf("After sorting:  ");
    printArray(sample, sampleSize);

    //TEST CASE 2: runtime for different input sizes
    printf("\n=== Test Case 2: Runtime for different input sizes ===\n");
    int sizes[] = {1000, 10000, 100000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        int* arr = (int*)malloc(n * sizeof(int));
        fillRandom(arr, n);

        clock_t start = clock();
        mergeSort(arr, 0, n - 1);
        clock_t end = clock();

        double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Input size: %-7d Time taken: %f seconds\n", n, timeTaken);

        free(arr);
    }

    return 0;
}
