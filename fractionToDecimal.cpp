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
  typedef long long int NType;
  typedef vector< NType > NList;
  typedef NList::iterator NListIt;
public:
  string fractionToDecimal( NType num, NType den ) {
    if ( den == 0 )
      return "INF";
    stringstream ss;
    if ( num * den < 0 )
      ss << "-";
    num = abs(num);
    den = abs(den);
    ss << num / den;
    cout << ss.str() << endl;
    map< NType, bool > hashMap;
    NType remain = abs( num % den );
    if ( remain == 0 )
      return ss.str();
    NList digits;
    while ( remain != 0 and !hashMap.count( remain ) ) {
      remain *= 10;
      hashMap[ remain ] = true;
      digits.push_back( -1 * remain );
      cout << "remain " << remain << endl;

      while ( remain < den ) {
	digits.push_back( 0 );
	remain *= 10;
      }
      digits.push_back( remain / den );
      remain = ( remain % den );
    }
    cout << "here" << endl;
    ss << ".";
    bool close = false;
    for (  NListIt it = digits.begin(); it != digits.end(); it++ ) {
      cout << "here" << *it << endl;
      if ( remain != 0 and *it == -1 * remain ) {
	ss << "(";
	close = true;
      }
      it++;
      while ( *it == 0 ) {
	ss << *it;
	it++;
      }
      ss << *it;
    }
    if (close)
      ss << ")";
    return ss.str();
  }
};


int main() {
  long long int num, den;
  Solution sol;
  cout << -1 / -2147483648 << " " << -1 % -2147483648 << endl;
  ///*
  while( cin >> num ) {
    cin >> den;
    cout << sol.fractionToDecimal( num, den ) << endl;
  }
  // */
  return 1;
}
