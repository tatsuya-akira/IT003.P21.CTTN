#!/usr/bin/python3
import numpy as np
import time

def analyze_numpy_sort(filename, outFile):
    data = np.loadtxt(filename)
    start_time = time.perf_counter()
    np.sort(np.array(data)) 
    end_time = time.perf_counter()
    duration = (end_time - start_time) * 1000
    outFile.write(f"{duration:.0f} ms\n")
    print(f"{duration:.0f} ms")

def run_numpy_sort(outFile):
    outFile.write("sort (Python)\n")
    print("sort (Python)")
    outFile.write("Ordered Asc: ")
    print("Ordered Asc: ", end="")
    analyze_numpy_sort("ordered_asc.txt", outFile)
    outFile.write("Ordered Desc: ")
    print("Ordered Desc: ", end="")
    analyze_numpy_sort("ordered_desc.txt", outFile)
    for i in range(1, 9):
        filename = f"unordered_{i}.txt"
        outFile.write(f"Unordered {i}: ")
        print(f"Unordered {i}: ", end="")
        analyze_numpy_sort(filename, outFile)
    outFile.write("\n")

with open("result.txt", "a") as outFile:
    run_numpy_sort(outFile)

