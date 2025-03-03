#!/usr/bin/python3 
import matplotlib.pyplot as plt
import numpy as np

def res(filename):
    results = {}
    current = None

    with open(filename, "r", encoding="utf-8") as file:
        for algo in file:
            algo = algo.strip()
            if not algo or "Average time" in algo:
                continue

            if algo in ["QuickSort", "HeapSort", "MergeSort", "sort (C++)", "sort (Python)"]:
                current = algo
                results[current] = []
            else:
                parts = algo.split(":")
                if len(parts) == 2:
                    label = parts[0].strip()
                    time = float(parts[1].split()[0]) 
                    results[current].append((label, time))
    
    return results

filename = "result.txt" 
data = res(filename)

categories = [label for label, _ in data["QuickSort"]]
quickSort = [time for _, time in data["QuickSort"]]
heapSort = [time for _, time in data["HeapSort"]]
mergeSort = [time for _, time in data["MergeSort"]]
sortC = [time for _, time in data["sort (C++)"]]
sortPy = [time for _, time in data["sort (Python)"]]

x = np.arange(len(categories))
width = 0.15 

fig, ax = plt.subplots(figsize=(12, 6))

ax.bar(x - 2*width, quickSort, width, label="QuickSort", color="blue")
ax.bar(x - width, heapSort, width, label="HeapSort", color="orange")
ax.bar(x, mergeSort, width, label="MergeSort", color="gray")
ax.bar(x + width, sortC, width, label="sort (C++)", color="red")
ax.bar(x + 2*width, sortPy, width, label="sort (Python)", color="green")

ax.set_ylabel("Thời gian thực nghiệm (ms)")
ax.set_title("Kết quả thử nghiệm trên bộ dữ liệu")
ax.set_xticks(x)
ax.set_xticklabels(categories, rotation=45, ha="right")
ax.legend()

plt.tight_layout()
plt.show()
