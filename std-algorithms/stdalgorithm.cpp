// std algorithm scratch file
//
// TODO:
//      inclusive_scan
//      exclusive_scan
//      count_if
//      nth_element
//
// Examples below for:
//      transform_reduce
//      transform
//      reduce
//
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

auto demo1_create_pairs() -> void {
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

  // reduce first, last, init, binary_op
  // default std::reduce sums the elements
  // but can do a different operation too
  cout << "std::reduce a: " << std::reduce(a.begin(), a.end(), 0) << endl;
}

auto demo2_rms_with_transform_reduce() -> void {
  // implement RMS with transform_reduce
  // transform_reduce. args: first last first_2 init reduce_op transform_op
  vi d;
  d.resize(5);
  std::iota(d.begin(), d.end(), 1);

  // rms is defined as sqrt(sum(x^2)/N)
  auto sum_squares = std::transform_reduce(d.begin(), d.end(), d.begin(), 0,
                                           std::plus{}, std::multiplies{});
  auto rms = sqrt(sum_squares / d.size());
  cout << "sum squares expected: 55 actual: " << sum_squares << endl
       << "rms expected: 3.316625 actual: " << rms << endl;
}

auto demo3_adjacent_difference() -> void {
  // adjacent_difference args: first, last, first_2, binary_op
  vi a{1, 2, 12, 22, 5};
  vi b(a.size());
  cout << "adjacent difference result" << endl;
  print_veci(a);
  std::adjacent_difference(a.begin(), a.end(), b.begin(), std::minus{});
  print_veci(b);
}

auto main() -> int {
  demo1_create_pairs();
  demo2_rms_with_transform_reduce();
  demo3_adjacent_difference();
  return 0;
}
