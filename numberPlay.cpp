/**********************************************************************************
**  Problem Statement
**
**  You are given an array of size N. You need to answer Q queries. Each Query contains 1 number x.
**  For each query,you need to add x to each element of the array and then report the sum of absolute values in the array.
**
**  Note : Changes to the array are permanent.See Sample for more clarification.
**
**  Input Format
**
**  First line contains N , number of elements in the array.
**  Next line contains N space separated integers of the array.
**  Next line contains Q(number of queries).
**  Next line contains Q space separated integers(the number x).
**
**  Output Format
**
**  For each query , output the sum in a newline.
**
**  Constraints
**
**  1 ≤ N ≤ 500000
**  1 ≤ Q ≤ 500000
**  -2000 ≤ number in each Query ≤ 2000
**  -2000 ≤ value of the array element ≤ 2000
**
**  Sample Input
**
**  3
**  -1 2 -3
**  3
**  1 -2 3
**  Sample Output
**
**  5
**  7
**  6
**  Explanation
**
**  After Query 1 : [ 0 , 3 , -2 ] => sum = 0 + 3 + 2 = 5
**  After Query 2 : [ -2 , 1 , -4 ] => sum = 2 + 1 + 4 = 7
**  After Query 3 : [ 1 , 4 , -1 ] => sum = 1 + 4 + 1 = 6
**
**  NOTE : There is large input output in the problem .Be carefull with slow Input Output.
**********************************************************************************/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<int> T;


int main() {
  int N, Q, query;
  long long int negs = 0, poss = 0;
  cin >> N;
  T arr(N);
  for( int i = 0; i < N; ++i ) {
    cin >> arr[i];
    sum += abs(arr[i]);
  }
  sort(arr.begin(), arr.end());
  cin >> Q;
  int num = -1, pos;
  int prev_pos = upper_bound(arr.begin(), arr.end(), num) - arr.begin();
  for( int i = 0, start = -1; i < Q; ++i ) {
    cin >> query;
    num -= query;
    pos = upper_bound(arr.begin(), arr.end(), num) - arr.begin();
    int sign = query / abs(query);
    // half-baked here but something like that!!!
    sum += -1 * query * pos +
      (prev_pos - pos) * sign +
      query + (N - prev_pos);
    cout << sum << endl;
    prev_pos = pos;
  }
  return 0;
}
