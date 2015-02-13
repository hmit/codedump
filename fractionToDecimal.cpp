/*
 * Solution to https://oj.leetcode.com/problems/fraction-to-recurring-decimal/
 */

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Solution {
  typedef vector< int > NList;
  typedef NList::iterator NListIt;
public:
  int numTens( int n ) {
    int r = 1;
    while( n > 1 ) {
      n /= 10;
      r *= 10;
    }
    return r;
  }

  string fractionToDecimal( int num, int den ) {
    if ( den == 0 )
      return "INF";
    stringstream ss;
    ss << num / den;
    map< int, bool > hashMap;
    int remain = num % den;
    if ( remain == 0 )
      return ss.str();
    NList digits;
    while ( remain != 0 and !hashMap.count( remain ) ) {
      hashMap[ remain ] = true;
      digits.push_back( remain );
      while ( remain < den ) remain *= 10;
      digits.push_back( remain / den );
      remain = remain % den;
    }
    ss << ".";
    bool close = false;
    for (  NListIt it = digits.begin(); it != digits.end(); it++ ) {
      if ( remain != 0 and *it == remain ) {
	ss << "(";
	close = true;
      }
      it++;
      ss << *it;
    }
    if (close)
      ss << ")";
    return ss.str();
  }
};

int main() {
  int num, den;
  Solution sol;
  while( cin >> num ) {
    cin >> den;
    cout << sol.fractionToDecimal( num, den ) << endl;
  }
  return 1;
}
