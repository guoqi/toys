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

#define BUFSIZE 100001

using namespace std;

void insertion_sort(int *a, int len);
void print_array(int *a, int len);

int main()
{
    int a[BUFSIZE];
    int n;
    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> a[i];
    }
    insertion_sort(a, n);
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

void print_array(int *a, int len) {
    for(int i=0; i<len; i++) {
        cout << a[i] << endl;
    }
}
