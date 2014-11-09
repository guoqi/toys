/*
 * =====================================================================================
 *
 *       Filename:  insertion_sort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/09/2014 05:01:43 PM
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

void insertion_sort(int *a, int len);
void print_array(int *a, int len);

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

void insertion_sort(int *a, int len)
{
    for(int i=0; i<len; i++) {
        int t = a[i];
        int j = i-1;
        while(j >=0 && t < a[j]) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = t;
    }
}
