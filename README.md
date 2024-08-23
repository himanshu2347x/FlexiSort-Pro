# FlexiSort Pro: Advanced Dynamic Sorting Library with Parallel Processing

## Overview

FlexiSort Pro is a highly customizable and efficient C++ sorting library designed to meet advanced sorting needs. It allows users to:

- **Plug in custom comparator functions** to define custom sorting logic.
- **Dynamically select between various sorting algorithms** based on data characteristics and algorithm efficiency.
- **Handle special cases** such as nearly sorted data or large datasets with optimized solutions.
- **Utilize parallel processing capabilities** to enhance performance for large datasets.

## Concept

The library provides:

- **Custom Comparator Functions**: Define your own comparison logic to sort different data types.
- **Dynamic Algorithm Selection**: Automatically chooses the most suitable sorting algorithm based on data characteristics.
- **Special Case Handling**: Optimized solutions for nearly sorted data and large datasets.

## Why It Stands Out

Sorting is a fundamental operation in computer science. FlexiSort Pro distinguishes itself by offering a highly customizable and efficient sorting solution. It demonstrates a deep understanding of algorithm optimization and practical application in real-world scenarios. The inclusion of parallel processing capabilities further enhances its performance for large datasets.

## Features

- **Multiple Sorting Algorithms**: Includes QuickSort, MergeSort, HeapSort, BubbleSort, SelectionSort, InsertionSort, and TimSort.
- **Dynamic Algorithm Selection**: Selects the best sorting algorithm based on data inversion count, data size, and dataset nature.
- **Custom Comparator Functions**: Sort various data types with user-defined comparison logic.
- **Support for Different Data Types**: Compatible with primitive as well as user-defined data types and structures.
- **Parallel Sorting**: Uses multi-threading to handle large datasets efficiently.

## How to Use This Library

### 1. Include the Header

Add the `sorter.h` header file to your project:
```cpp
#include "sorter.h"
```

### 2. Create an Instance

Instantiate the `sorter` class with the desired data type:
```cpp
sorter<int> mySorter;
```

### 3. Define a Comparator

Write a comparator function for custom sorting logic:
```cpp
bool compare(int a, int b) {
    return a < b;
}
```

### 4. Sort Data

Use the `sort` method to sort your data. Optionally, specify a sorting algorithm:
```cpp
vector<int> data = {5, 2, 9, 1, 5, 6};
mySorter.sort(data, compare);  
```

## Example Usage for Primitive Data Types

```cpp
#include "sorter.h"
#include <iostream>
#include <vector>
using namespace std;

bool compare(int a, int b) {
    return a < b;
}

int main() {
    sorter<int> mySorter;
    vector<int> data = {5, 2, 9, 1, 5, 6};
    
    // Sort using dynamic algorithm selection
    mySorter.sort(data, compare, "MergeSort");
    
    for (int num : data) {
        cout << num << " ";
    }
    
    return 0;
}
```

## Example Usage for User-defined Data Types

```cpp
#include <iostream>
#include <vector>
#include <string>
#include "sorter.h"

using namespace std;

struct Person
{
    string name;
    int age;
    double height;

    Person(string name = "", int age = 0, double height = 0.0)
       : name(name), age(age), height(height) {}
};

bool compareByAge(const Person &a, const Person &b) {
    return a.age < b.age;
}

bool compareByHeight(const Person &a, const Person &b) {
    return a.height > b.height;
}

bool compareByName(const Person &a, const Person &b) {
    return a.name.length() < b.name.length();
}

int main() {
    vector<Person> people = {
        Person("Alice", 30, 5.5),
        Person("Bob", 25, 6.0),
        Person("Charlie", 22, 5.7),
        Person("David", 35, 5.8)
    };

    sorter<Person> mySorter;

    mySorter.sort(people, compareByAge);
    cout << "Sorted by age:" << endl;
    for (const auto &p : people) {
        cout << "Name: " << p.name << ", Age: " << p.age << ", Height: " << p.height << endl;
    }

    mySorter.sort(people, compareByHeight);
    cout << "Sorted by height:" << endl;
    for (const auto &p : people) {
        cout << "Name: " << p.name << ", Age: " << p.age << ", Height: " << p.height << endl;
    }

    mySorter.sort(people, compareByName);
    cout << "Sorted by name:" << endl;
    for (const auto &p : people) {
        cout << "Name: " << p.name << ", Age: " << p.age << ", Height: " << p.height << endl;
    }

    return 0;
}
```

## NOTE

Build your project with a C++ compiler that supports C++11 or higher.

## Contributing

If you have suggestions for improvements or find any issues, please feel free to open an issue or submit a pull request.

