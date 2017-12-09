/*
 * =====================================================================================
 *
 *       Filename:  heapsort.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/23/2014 11:38:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Qi Guo (gq), uniqueguoqi@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <cstring>

using namespace std;

const int bufsize = 100001;

int main() {
    int data[bufsize];
    int a[bufsize];
    int result[bufsize];
    int n;
    memset(a, 0, bufsize * sizeof(int));

    cin >> n;
    for(int i=0; i<n; i++) {
        cin >> data[i];
        a[data[i]]++;
    }

    for(int i=1; i<bufsize; i++) {
        a[i] += a[i-1];
    }

    for(int i=0; i<n; i++) {
        result[a[data[i]]-1] = data[i];
        a[data[i]]--;
    }

    for(int i=0; i<n; i++) {
        cout << result[i] << endl;
    }
    return 0;
}
