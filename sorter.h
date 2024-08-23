#include <vector>
#include <functional>
#include <algorithm>
#include <string>
#include <iostream>
#include <thread>
using namespace std;

#ifndef SORTER_H
#define SORTER_H

template <typename T>
class sorter
{
public:
    using Comparator = function<bool(const T &, const T &)>;

    void sort(vector<T> &data, Comparator comp, const string &algorithm = "QuickSort")
    {
        if (algorithm.empty())
        {
            // Automatically choose algorithm based on inversion count
            long long inversionCount = countInversions(data, comp);
            if (inversionCount < data.size() * 0.1)
            {
                // Use TimSort for nearly sorted data
                timSort(data, comp);
            }
            else
            {
                // Use a general sorting algorithm
                quickSort(data, 0, data.size() - 1, comp);
            }
        }
        else
        {
            // Check for unknown algorithm before any sorting is attempted
            if (algorithm != "QuickSort" &&
                algorithm != "MergeSort" &&
                algorithm != "InsertionSort" &&
                algorithm != "HeapSort" &&
                algorithm != "BubbleSort" &&
                algorithm != "SelectionSort" &&
                algorithm != "TimSort")
            {
                // Throw exception for unknown algorithm
                throw invalid_argument("Unknown sorting algorithm: " + algorithm + ". Please enter a valid algorithm.");
            }

            try
            {
                if (algorithm == "QuickSort")
                {
                    quickSort(data, 0, data.size() - 1, comp);
                }
                else if (algorithm == "MergeSort")
                {
                    mergeSort(data, 0, data.size() - 1, comp);
                }
                else if (algorithm == "InsertionSort")
                {
                    insertionSortRange(data, 0, data.size() - 1, comp);
                }
                else if (algorithm == "HeapSort")
                {
                    heapSort(data, comp);
                }
                else if (algorithm == "BubbleSort")
                {
                    bubbleSort(data, comp);
                }
                else if (algorithm == "SelectionSort")
                {
                    selectionSort(data, comp);
                }
                else if (algorithm == "TimSort")
                {
                    timSort(data, comp);
                }
            }
            catch (const invalid_argument &e)
            {
                // Handle known exceptions
                cerr << "Error: " << e.what() << endl;
            }
            catch (const exception &e)
            {
                // Handle other exceptions
                cerr << "An error occurred: " << e.what() << endl;
            }
        }
    }

private:
    long long InversionCountMerge(vector<T> &data, vector<T> &temp, int low, int mid, int high, Comparator comp)
    {
        int left = low;
        int right = mid + 1;
        long long cnt = 0;
        int k = low;

        // Merge the two halves into temp
        while (left <= mid && right <= high)
        {
            if (comp(data[left], data[right]))
            {
                temp[k++] = data[left++];
            }
            else
            {
                temp[k++] = data[right++];
                cnt += (mid - left + 1); // Count inversions
            }
        }

        // Copy remaining elements of left half, if any
        while (left <= mid)
        {
            temp[k++] = data[left++];
        }

        // Copy remaining elements of right half, if any
        while (right <= high)
        {
            temp[k++] = data[right++];
        }

        // Copy merged elements back to data
        for (int i = low; i <= high; i++)
        {
            data[i] = temp[i - low];
        }

        return cnt;
    }

    long long inversionMergeSort(vector<T> &data, vector<T> &temp, int low, int high, Comparator comp)
    {
        long long cnt = 0;
        if (low < high)
        {
            int mid = low + (high - low) / 2;
            cnt += inversionMergeSort(data, temp, low, mid, comp);
            cnt += inversionMergeSort(data, temp, mid + 1, high, comp);
            cnt += InversionCountMerge(data, temp, low, mid, high, comp);
        }
        return cnt;
    }

    long long countInversions(vector<T> &data, Comparator comp)
    {
        vector<T> temp(data.size());
        return inversionMergeSort(data, temp, 0, data.size() - 1, comp);
    }

    void quickSort(vector<T> &data, int low, int high, Comparator comp)
    {
        if (low < high)
        {
            int pi = partition(data, low, high, comp);

            // Create two threads for parallel sorting
            thread leftThread([this, &data, low, pi, comp]()
                              { quickSort(data, low, pi - 1, comp); });
            thread rightThread([this, &data, pi, high, comp]()
                               { quickSort(data, pi + 1, high, comp); });

            // Wait for both threads to finish
            leftThread.join();
            rightThread.join();
        }
    }

    int partition(vector<T> &data, int low, int high, Comparator comp)
    {
        T pivot = data[high];
        int i = (low - 1);
        for (int j = low; j < high; j++)
        {
            if (comp(data[j], pivot))
            {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[high]);
        return (i + 1);
    }

    void mergeSort(vector<T> &data, int left, int right, Comparator comp)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;

            // Create two threads for parallel sorting
            thread leftThread([this, &data, left, mid, comp]()
                              { mergeSort(data, left, mid, comp); });

            thread rightThread([this, &data, mid, right, comp]()
                               { mergeSort(data, mid + 1, right, comp); });

            // Wait for both threads to finish
            leftThread.join();
            rightThread.join();

            // Merge the sorted halves
            merge(data, left, mid, right, comp);
        }
    }

    void merge(vector<T> &data, int left, int mid, int right, Comparator comp)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<T> L(n1), R(n2);
        for (int i = 0; i < n1; i++)
            L[i] = data[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = data[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (comp(L[i], R[j]))
            {
                data[k++] = L[i++];
            }
            else
            {
                data[k++] = R[j++];
            }
        }

        while (i < n1)
        {
            data[k++] = L[i++];
        }

        while (j < n2)
        {
            data[k++] = R[j++];
        }
    }

    void heapSort(vector<T> &data, Comparator comp)
    {
        int n = data.size();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(data, n, i, comp);

        // One by one extract elements
        for (int i = n - 1; i >= 0; i--)
        {
            swap(data[0], data[i]);
            heapify(data, i, 0, comp);
        }
    }

    void heapify(vector<T> &data, int n, int i, Comparator comp)
    {
        int largest = i;
        int l = 2 * i + 1; // left = 2*i + 1
        int r = 2 * i + 2; // right = 2*i + 2

        // Check if left child is larger than root
        if (l < n && comp(data[largest], data[l]))
            largest = l;

        // Check if right child is larger than largest so far
        if (r < n && comp(data[largest], data[r]))
            largest = r;

        // If largest is not root
        if (largest != i)
        {
            swap(data[i], data[largest]);
            // Recursively heapify the affected sub-tree
            heapify(data, n, largest, comp);
        }
    }

    void bubbleSort(vector<T> &data, Comparator comp)
    {
        int n = data.size();
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++)
            {
                if (comp(data[j + 1], data[j]))
                {
                    swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            // If no two elements were swapped by inner loop, then break
            if (!swapped)
                break;
        }
    }

    void selectionSort(vector<T> &data, Comparator comp)
    {
        int n = data.size();
        for (int i = 0; i < n - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (comp(data[j], data[minIndex]))
                {
                    minIndex = j;
                }
            }
            swap(data[i], data[minIndex]);
        }
    }

    // Implementation of TimSort
    void timSort(vector<T> &data, Comparator comp)
    {
        const int RUN = 32;
        int n = data.size();
        for (int i = 0; i < n; i += RUN)
            insertionSortRange(data, i, min((i + RUN - 1), n - 1), comp);

        for (int size = RUN; size < n; size = 2 * size)
        {
            for (int left = 0; left < n; left += 2 * size)
            {
                int mid = min(left + size - 1, n - 1);
                int right = min((left + 2 * size - 1), (n - 1));

                if (mid < right)
                    merge(data, left, mid, right, comp);
            }
        }
    }

    void insertionSortRange(vector<T> &data, int left, int right, Comparator comp)
    {
        for (int i = left + 1; i <= right; i++)
        {
            T key = data[i];
            int j = i - 1;
            while (j >= left && comp(key, data[j]))
            {
                data[j + 1] = data[j];
                j--;
            }
            data[j + 1] = key;
        }
    }
};

#endif
