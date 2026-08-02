/*  TASK 2 - Problem 3: 0/1 KNAPSACK (Dynamic Programming) 
    The problem: You have a bag that can carry weight W. You have several items, each with a weight and a value. You want to choose items to MAXIMIZE total value 
    without exceeding W.
    "0/1" means each item is either taken whole or not at all
    (you can't take half an item).
  
    Why Dynamic Programming (DP)? A greedy approach (e.g. always take the most valuable item first) does NOT always give the best answer for this problem. 
    DP guarantees the optimal answer by building up a table of best-possible-values for every (item, remaining-capacity) combination.
    Time Complexity: O(n * W)  where n = number of items,  W = knapsack capacity  Space Complexity: O(n * W) for the DP table  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Returns the max value achievable with given weights/values and capacity W.
int knapsack(int W, int weights[], int values[], int n) {
    // dp[i][w] = best value using the first i items, with capacity w
    int** dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; i++) {
        dp[i] = (int*)calloc((W + 1), sizeof(int)); // calloc = auto-fills with 0
    }

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (weights[i - 1] <= w) {
                // Option A: don't take item i -> dp[i-1][w]
                // Option B: take item i -> value[i-1] + best value with remaining capacity
                int notTake = dp[i - 1][w];
                int take = values[i - 1] + dp[i - 1][w - weights[i - 1]];
                dp[i][w] = (take > notTake) ? take : notTake;
            } else {
                // item too heavy to even consider
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int result = dp[n][W];

    for (int i = 0; i <= n; i++) free(dp[i]);
    free(dp);

    return result;
}

int main() {
    srand(time(NULL));

    //TEST CASE 1: small fixed example (to show correctness)
    printf("=== Test Case 1: Small fixed example ===\n");
    int weights1[] = {2, 3, 4, 5};
    int values1[]  = {3, 4, 5, 6};
    int n1 = 4;
    int capacity1 = 5;

    printf("Items (weight, value): (2,3) (3,4) (4,5) (5,6)\n");
    printf("Knapsack capacity: %d\n", capacity1);
    printf("Maximum value achievable: %d\n", knapsack(capacity1, weights1, values1, n1));
    // Expected: taking items (2,3) and (3,4) = weight 5, value 7 -> best answer is 7

    //TEST CASE 2: runtime for different input sizes 
    printf("\n=== Test Case 2: Runtime for different input sizes ===\n");
    int itemCounts[] = {100, 500, 1000};
    int numTests = sizeof(itemCounts) / sizeof(itemCounts[0]);
    int capacity2 = 1000; // fixed capacity for this test

    for (int t = 0; t < numTests; t++) {
        int n = itemCounts[t];
        int* w = (int*)malloc(n * sizeof(int));
        int* v = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            w[i] = (rand() % 50) + 1;   // weight between 1-50
            v[i] = (rand() % 100) + 1;  // value between 1-100
        }

        clock_t start = clock();
        int best = knapsack(capacity2, w, v, n);
        clock_t end = clock();

        double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Items: %-6d Capacity: %-6d Best value: %-6d Time taken: %f seconds\n",
               n, capacity2, best, timeTaken);

        free(w);
        free(v);
    }

    return 0;
}
