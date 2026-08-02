# Task 2: Algorithms & Problem Solving

## 📌 Overview
Three algorithmic problems implemented in C, covering **sorting**,
**searching**, and **dynamic programming** — as required by the task.

| # | Problem | Category | File |
|---|---|---|---|
| 1 | Merge Sort | Sorting | `merge_sort.c` |
| 2 | Binary Search | Searching | `binary_search.c` |
| 3 | 0/1 Knapsack | Dynamic Programming | `knapsack.c` |

## ⚙️ Environment
- **Language:** C (C99 standard)
- **Compiler:** GCC, compiled with `-O2` optimization
- **Editor used:** VS Code
- **OS tested on:** Windows 11

## 🔨 Build & Run Instructions
Each file is compiled and run independently:
```bash
gcc merge_sort.c -o merge_sort -O2
.\merge_sort

gcc binary_search.c -o binary_search -O2
.\binary_search

gcc knapsack.c -o knapsack -O2
.\knapsack
```

---

## 1️⃣ Merge Sort

**Why this algorithm:** Merge Sort guarantees O(n log n) performance in
every case (best, average, worst) — unlike Quick Sort, which can degrade
to O(n²) on unlucky inputs. It's a reliable, predictable choice.

**How it works:** Recursively splits the array in half until each piece
has 1 element (already "sorted"), then merges pairs of sorted pieces
back together in order.

**Complexity:**
- Time: **O(n log n)** — array is split log n times, and merging at
  each level takes O(n) total
- Space: **O(n)** — needs a temporary array to merge into

**Test results (runtime vs input size):**
| Input Size | Time Taken |
|---|---|
| 1,000 | ~0.0002 sec |
| 10,000 | ~0.0013 sec |
| 100,000 | ~0.015 sec |

The runtime growth closely follows the expected n log n pattern.

---

## 2️⃣ Binary Search

**Why this algorithm:** When data is already sorted, binary search is
dramatically faster than checking every element one by one (linear
search, O(n)).

**How it works:** Repeatedly checks the middle element of the search
range; discards the half that can't contain the target; repeats on the
remaining half.

**Requirement:** The array **must be sorted first** — binary search
doesn't work on unsorted data.

**Complexity:**
- Time: **O(log n)** — the search space is halved every step
- Space: **O(1)** — iterative version uses no extra memory

**Test results (runtime vs input size):**
| Input Size | Time Taken |
|---|---|
| 1,000 | ~0.000001 sec |
| 100,000 | ~0.000001 sec |
| 10,000,000 | ~0.000002 sec |

Even a **10,000x increase** in input size barely changed the runtime —
this is the practical payoff of O(log n).

---

## 3️⃣ 0/1 Knapsack (Dynamic Programming)

**Why this algorithm:** A greedy approach (e.g., always pick the most
valuable item) does **not** guarantee the optimal answer for this
problem, since it ignores weight trade-offs. Dynamic Programming
guarantees the mathematically best answer by building a table of
best-possible-values for every combination of items and remaining
capacity.

**How it works:** Builds a 2D table `dp[i][w]` = best value achievable
using the first `i` items with capacity `w`. For each item, decides
whether including it (if it fits) gives a better result than excluding
it.

**Complexity:**
- Time: **O(n × W)** — n = number of items, W = knapsack capacity
- Space: **O(n × W)** — for the DP table

**Test results (runtime vs number of items, capacity fixed at 1000):**
| Items | Best Value Found | Time Taken |
|---|---|---|
| 100 | 3550 | ~0.0005 sec |
| 500 | 7285 | ~0.0020 sec |
| 1000 | 11203 | ~0.0037 sec |

Runtime grows roughly linearly with item count here, since capacity
was held fixed — matching the O(n × W) expectation.

---

## 💡 Summary: Algorithm Choice Reasoning

| Problem Type | Algorithm Chosen | Why |
|---|---|---|
| Sorting | Merge Sort | Guaranteed O(n log n), stable, predictable |
| Searching | Binary Search | O(log n) on sorted data — far faster than linear scan |
| Optimization | 0/1 Knapsack (DP) | Greedy fails here; DP guarantees the true optimal answer |
