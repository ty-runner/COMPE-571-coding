# Virtual Memory Simulation Tool

## Overview

In this project, you will develop a virtual memory simulation tool to analyze various page replacement algorithms. The simulation reads memory references from an input file and tracks key statistics such as page faults, disk references, and dirty page writes.

---

## Features

- Simulates virtual memory using **1-level page tables**.
- Supports multiple page replacement algorithms:
  1. **Random (RAND)**
  2. **First In First Out (FIFO)**
  3. **Least Recently Used (LRU)**
  4. **Periodic Reference Reset (PER)**
- Tracks the following statistics:
  - Total **page faults**
  - Total **disk accesses**
  - Total **dirty page writes**
- Allows custom page replacement algorithms for extra credit.

---

## Input File Format

Each input file contains a series of memory references.  
**Format**: `<process_number> <memory_address> <R/W>`  
- `process_number`: Integer denoting the process.  
- `memory_address`: 16-bit virtual address (0–65535).  
- `R/W`:  
  - **R** - Read  
  - **W** - Write (modifies the memory address).  

**Example Input**:
```
1 12345 R
2 54321 W
1 12340 R
```

---

## Address Space and Memory Details

- **Virtual Address Space**: 64 KB (16-bit addresses, range: `0–65535`).  
- **Page Size**: 512 bytes (2^9).  
- **Page Table Entries**: 128 (2^16 / 2^9).  
- **Physical Memory**: 32 pages * 512 bytes/page = 16 KB.  

---

## Page Replacement Algorithms

### 1. Random (RAND)
- Chooses a random page to replace.

### 2. First In First Out (FIFO)
- Replaces the oldest page in memory.

### 3. Least Recently Used (LRU)
- Replaces the least recently used page.  
- If a tie occurs:
  - Replace the non-dirty page first.
  - If both are dirty or neither is dirty, replace the lower-numbered page.

### 4. Periodic Reference Reset (PER)
- Sets the reference bit to 1 whenever a page is used.  
- After every **200 memory references**, all reference bits are reset to 0.  
- Replacement order (when a page fault occurs):  
  1. Unused pages.  
  2. Unreferenced and clean pages.  
  3. Unreferenced and dirty pages.  
  4. Referenced and clean pages.  
  5. Referenced and dirty pages.  
- If ties occur, the lowest-numbered page is replaced.

---

## Custom Algorithm (Extra Credit)

- Optionally, implement your own algorithm.  
- Compare its performance to the standard algorithms in terms of:
  - Page faults
  - Disk accesses
  - Dirty page writes

---

## How to Run

1. **Setup**:  
   - Install any dependencies required for your programming language.  
2. **Run the Program**:  
   - Example command:  
     ```bash
     python virtual_memory_simulation.py data1.txt
     ```
3. **Input File**:  
   - Ensure your input file (`data1.txt` or `data2.txt`) follows the specified format.  

4. **Output**:  
   - The program will output statistics for each algorithm:  
     - Total Page Faults  
     - Total Disk Accesses  
     - Total Dirty Page Writes  

---

## Report Guidelines

Your project report (4–5 pages) must include:

1. **Code Details**:
   - Page table representation.
   - Virtual to physical address translation.
   - Page fault handling and page replacement logic.
   - Explanation of your custom algorithm (if applicable).

2. **Results**:
   - Statistics for each algorithm:
     - Total page faults.
     - Total disk accesses.
     - Total dirty page writes.
   - Graphs comparing:
     1. Page Faults
     2. Disk Accesses
     3. Dirty Page Writes

3. **Deliverables**:
   - A ZIP file containing your program and this **README**.
   - A report in **PDF** or **DOCX** format.

---

## Deliverables

1. **Program**: Submit a ZIP file containing:
   - All code/scripts.  
   - A **README** file with instructions to execute the program.

2. **Report**: Submit a PDF or DOCX document (4–5 pages).

---

## Notes

- Ensure the program runs on your chosen language.  
- Test thoroughly with `data1.txt` and `data2.txt`.  
- If attempting extra credit, justify your custom algorithm's performance.

---

## Grading Criteria

- Functional program with correct results.  
- Detailed and concise report.  
- Clear explanation of algorithms and code logic.  
- Extra credit for a custom page replacement algorithm.