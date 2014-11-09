/*
 * =====================================================================================
 *
 *       Filename:  insertion_sort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/01/2014 12:47:30 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qi Guo (gq), uniqueguoqi@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

void print_array(int *a, int len); 
void quick_sort(int *a, int start, int end);
int quick_sort_partition(int *a, int p, int q);

int main()
{
    int a[1000];
    int n;
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }
    /* insertion_sort(a, n); */
    quick_sort(a, 0, n-1);
    print_array(a, n);
    return 0;
}


void print_array(int *a, int len) {
    for(int i=0; i<len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}


int quick_sort_partition(int *a, int p, int q)
{
    int key = a[q];
    for(int i=p; i<q; i++) {
        if(a[i] <= key) {
            int t = a[p];
            a[p] = a[i];
            a[i] = t;
            p++;
        }
    }
    int t = a[p];
    a[p] = key;
    a[q] = t;
    return p;
}

void quick_sort(int *a, int start, int end)
{
    if(start >= end) {
        return;
    }
    else {
        int mid = quick_sort_partition(a, start, end);
        quick_sort(a, start, mid-1);
        quick_sort(a, mid+1, end);
    }
}
