#include <iostream>
#include <string>
#include <cstdio>
#include <sys/time.h>

using namespace std;

int cal_next(const char * p, int plen);

void print_array(int * arr, int len)
{
    for(int i=0; i<len; ++i)
    {
        printf("arr[%d]=%d, ", i, arr[i]);
    }
    printf("\n");
}

int find(const char * s, int slen, const char * p, int plen)
{
    int * next = new int[plen];
    next[0] = 0;
    for (int i=1; i<=plen; ++i)
    {
        next[i] = cal_next(p, i);
    }
    // print_array(next, plen);

    int i = 0;
    int j = 0;
    int idx = -1;
    while (i < slen)
    {
        while (j < plen && i < slen && s[i] == p[j])
        {
            ++i;
            ++j;
        }

        if (j == plen)
        {
            idx = i - j;
            break;
        }

        if (j > 0)
        {
            j = next[j]; 
        }
        else
        {
            ++i;
        }
    }

    delete[] next;

    return idx;
}

int hfind(const char * s, int slen, const char * p, int plen)
{
    int i = 0;
    int j = 0;
    int idx = -1;
    while (i < slen)
    {
        int k = i;
        while (k < slen && j < plen && s[k] == p[j])
        {
            ++k;
            ++j;
        }

        if (j == plen)
        {
            idx = k - j;
            break;
        }

        ++i;
        j = 0;
    }

    return idx;
}

int cal_next(const char * p, int plen)
{
    int i = 0;
    int j = i + 1; 
    while (j < plen)
    {
        if (p[i] == p[j])
        {
            ++j;
            ++i;
        }
        else
        {
            j += i == 0 ? 1 : 0;
            i = 0;
        }
    }
    return i;
}

string random_str(int len)
{
    string s;
    while(len-- > 0)
    {
        char c = rand() % 10 + 65;
        s.push_back(c);
    }
    return s;
}

void print_statis(struct timeval * start, struct timeval * end)
{
    printf("Time cost: %lfms\n", (end->tv_sec - start->tv_sec) * 1000 + (end->tv_usec - start->tv_usec) / double(1000));
}

int main()
{
    srand(time(NULL));
    assert(find("abcdef", 6, "abc", 3) == 0);
    assert(find("abcdef", 6, "1", 1) == -1);
    assert(find("abcdef", 6, "de", 2) == 3);
    assert(find("abcdef", 6, "abcdef", 6) == 0);
    assert(find("abcdef", 6, "abcdefghi", 6) == 0);
    assert(find("abcdef", 6, "bcdg", 4) == -1);
    assert(find("abababacaefg", 12, "ababaca", 7) == 2);
    assert(find("hijabababacaefg", 15, "ababaca", 7) == 5);
    assert(find("bbc abcdab abcdabcdabde", 23, "abcdabd", 7) == 15);

    assert(hfind("abcdef", 6, "abc", 3) == 0);
    assert(hfind("abcdef", 6, "1", 1) == -1);
    assert(hfind("abcdef", 6, "de", 2) == 3);
    assert(hfind("abcdef", 6, "abcdef", 6) == 0);
    assert(hfind("abcdef", 6, "abcdefghi", 6) == 0);
    assert(hfind("abcdef", 6, "bcdg", 4) == -1);
    assert(hfind("abababacaefg", 12, "ababaca", 7) == 2);
    assert(hfind("hijabababacaefg", 15, "ababaca", 7) == 5);
    assert(hfind("bbc abcdab abcdabcdabde", 23, "abcdabd", 7) == 15);

    string s = random_str(100000000);
    string p = random_str(10000);

    struct timeval start;
    struct timeval end;

    gettimeofday(&start, NULL);
    int r1 = s.find(p);
    gettimeofday(&end, NULL);

    print_statis(&start, &end);

    gettimeofday(&start, NULL);
    int r2 = find(s.c_str(), s.length(), p.c_str(), p.length());
    gettimeofday(&end, NULL);

    print_statis(&start, &end);

    gettimeofday(&start, NULL);
    int r3 = hfind(s.c_str(), s.length(), p.c_str(), p.length());
    gettimeofday(&end, NULL);

    print_statis(&start, &end);

    assert(r1 == r2);
    assert(r2 == r3);
    
    return 0;
}
