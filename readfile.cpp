#include <bits/stdc++.h>

using std::cout, std::cin, std::ios;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0); 
  freopen("input.txt", "r", stdin);

  double x{};
  double tot=0.0;
  printf("x starting val = %le\n",x);
  while(cin >> x) {
    tot += x;
  }
  cout << "running sum: " << tot << "\n";
  return 0;
}
