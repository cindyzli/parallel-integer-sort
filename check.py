#!/usr/bin/env python3

import sys
import random
import subprocess
import time

def main():
    DEFAULT_NUM_INTS = 100_000
    DEFAULT_PROGRAM = "sort/sort_numbers"

    if len(sys.argv) > 1:
        try:
            n = int(sys.argv[1])
        except ValueError:
            print(f"Invalid integer for number_of_ints: {sys.argv[1]}")
            sys.exit(1)
    else:
        n = DEFAULT_NUM_INTS
    
    if len(sys.argv) > 2:
        program = sys.argv[2]
    else:
        program = DEFAULT_PROGRAM

    print(f"Generating {n} signed 32-bit integers...")
    original_ints = [random.randint(-2147483648, 2147483647) for _ in range(n)]
    
    input_data = "\n".join(str(x) for x in original_ints) + "\n"
    
    print(f"Running program: {program}")
    start_time = time.time()

    process = subprocess.Popen(
        [program],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    
    out, err = process.communicate(input_data)

    elapsed_time = time.time() - start_time
    
    if process.returncode != 0:
        print(f"ERROR: Program {program} exited with non-zero status {process.returncode}.")
        print("stderr:", err)
        sys.exit(process.returncode)

    output_str = out.strip()
    if not output_str:
        output_ints = []
    else:
        output_ints = list(map(int, output_str.split()))
    
    if sorted(original_ints) == output_ints:
        print("SUCCESS: Output is sorted correctly and contains the same elements.")
    else:
        print("FAIL: Output is not a correctly sorted version of the original list.")
    
    print(f"Sorting took {elapsed_time:.4f} seconds.")

if __name__ == "__main__":
    main()