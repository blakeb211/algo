// std algorithm scratch file
#include <bits/stdc++.h>

using vi = std::vector<int>;
using vpi = std::vector<std::pair<int, int>>;
using std::cout, std::endl, std::vector;

auto print_veci(std::vector<int> in) -> void {
  for (const auto& i : in) cout << i << " ";
  cout << endl;
}

auto print_vecpi(vpi in) -> void {
  for (const auto& i : in)
    cout << "( " << i.first << " , " << i.second << " )"
         << "\n";
  cout << endl;
}

auto main() -> int {
  vi a;
  a.resize(20);
  std::iota(a.begin(), a.end(), 1);

  std::random_device rd;
  std::mt19937 g(rd());

  vi b;
  b.resize(a.size());
  cout << "vec a size " << a.size() << endl
       << "vec b size " << b.size() << endl;

  auto sqr = [](const int& i) -> int { return i * i; };
  std::transform(a.begin(), a.end(), b.begin(), sqr);

  print_veci(a);
  print_veci(b);

  std::random_shuffle(a.begin(), a.end());
  std::random_shuffle(b.begin(), b.end());

  // create vector of pairs using an algorithm
  vpi c;
  c.resize(a.size());
  std::transform(a.begin(), a.end(), b.begin(), c.begin(),
                 std::make_pair<int&, int&>);

  // print vec of pairs created using std::transform on
  // two input vectors
  print_vecpi(c);

  return 0;
}
