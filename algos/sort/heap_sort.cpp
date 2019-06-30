/*
 * =====================================================================================
 *
 *       Filename:  heap_sort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  02/01/2015 04:54:12 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qi Guo (gq), uniqueguoqi@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>

#define BUFSIZE 100001

using namespace std;

void maintain_max_heap(int *array, int n, int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest;

    if (left < n && array[left] > array[i]) {
        largest = left;
    }
    else {
        largest = i;
    }

    if (right < n && array[right] > array[largest]) {
        largest = right;
    }
    if (largest != i) {
        int t = array[largest];
        array[largest] = array[i];
        array[i] = t;
        maintain_max_heap(array, n, largest);
    }
}


void build_max_heap(int *array, int n)
{
    for (int i=(n-1)/2; i>=0; i--) {
        maintain_max_heap(array, n, i);
    }
}


void heap_sort(int *array, int n)
{
    build_max_heap(array, n);
    for (int i=n-1; i>0; i--) {
        int t = array[0];
        array[0] = array[i];
        array[i] = t;
        maintain_max_heap(array, i, 0);
    }
}


void print_array(int *array, int n)
{
    for (int i=0; i<n; i++) {
        cout << array[i] << endl;
    }
}


int main()
{
    int array[BUFSIZE];
    int n;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> array[i];
    }

    heap_sort(array, n);
    print_array(array, n);
    return 0;
}
