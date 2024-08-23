# FlexiSort Pro: Advanced Dynamic Sorting Library with Parallel Processing

## Overview

FlexiSort Pro is a highly customizable and efficient C++ sorting library designed for advanced sorting needs.
It allows users to plug in custom comparator functions, dynamically select between various sorting algorithms, and handle special cases such as nearly sorted data or large datasets.
The library also features parallel processing capabilities to enhance performance.

## Concept

The library provides:

Custom Comparator Functions: Users can define their own comparison logic to sort different data types.

Dynamic Algorithm Selection: Automatically chooses the most suitable sorting algorithm based on data characteristics and algorithm efficiency.

Special Case Handling: Optimized solutions for nearly sorted data and large datasets.

## Why It Stands Out

Sorting is a fundamental operation in computer science. FlexiSort Pro stands out by offering a highly customizable, efficient sorting solution that demonstrates a deep understanding of algorithm optimization and practical application in real-world scenarios. The addition of parallel processing capabilities further enhances its performance for large datasets.

## Features

Multiple Sorting Algorithms: Includes QuickSort, MergeSort, HeapSort, BubbleSort, SelectionSort, InsertionSort, and TimSort.

Dynamic Algorithm Selection: Automatically selects the best sorting algorithm based on data inversion count, data size and nature of the dataset to ensure efficient performance.

Custom Comparator Functions: Allows sorting of various data types with user-defined comparison logic.

Support for Custom Data Types: Enhance compatibility with user-defined data types and structures.

Parallel Sorting: Utilizes multi-threading to efficiently handle large datasets.

## How to use this library

1.Include the Header:
Add the sorter.h header file to your project.
#include "sorter.h"

2.Create an Instance: Instantiate the sorter class with the desired data type.
sorter<int> mySorter;

3.Define a Comparator: Write a comparator function for custom sorting logic.
bool compare(int a, int b) {
    return a < b;
}

4.Sort Data: Use the sort method to sort your data. Optionally, specify a sorting algorithm.
vector<int> data = {5, 2, 9, 1, 5, 6};
mySorter.sort(data, compare);  

## NOTE

Build your project with a C++ compiler that supports C++11 or higher.

## Example Usage for Primitive data Type

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
    mySorter.sort(data, compare,"MergeSort");
    
    for (int num : data) {
        cout << num << " ";
    }
    
    return 0;
}

## Example Usage for User-defined data Type

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

    // Default constructor with default values
    Person(string name = "", int age = 0, double height = 0.0)
       {
        this->name=name;
        this->age = age;
        this->height = height;
       }
};

// Comparator to sort by age (ascending)
bool compareByAge(const Person &a, const Person &b)
{
    return a.age < b.age;
}

// Comparator to sort by height (descending)
bool compareByHeight(const Person &a, const Person &b)
{
    return a.height > b.height;
}

// Comparator to sort by name (lexicographically)
bool compareByName(const Person &a, const Person &b)
{
    return a.name.length() < b.name.length();
}

int main()
{
    vector<Person> people = {
        Person("Alice", 30, 5.5),
        Person("Bob", 25, 6.0),
        Person("Charlie", 22, 5.7),
        Person("David", 35, 5.8)};

    sorter<Person> mySorter;

    // Sort by age
    mySorter.sort(people, compareByAge);
    cout << "Sorted by age:" << endl;
    for (const auto &p : people)
    {
        cout << "Name: " << p.name << ", Age: " << p.age << ", Height: " << p.height << endl;
    }

    // Sort by height
    mySorter.sort(people, compareByHeight);
    cout << "Sorted by height:" << endl;
    for (const auto &p : people)
    {
        cout << "Name: " << p.name << ", Age: " << p.age << ", Height: " << p.height << endl;
    }

    // Sort by name length
    mySorter.sort(people, compareByName);
    cout << "Sorted by name:" << endl;
    for (const auto &p : people)
    {
        cout << "Name: " << p.name << ", Age: " << p.age << ", Height: " << p.height << endl;
    }

    return 0;
}



