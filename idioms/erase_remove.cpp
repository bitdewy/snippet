//erase-remove idioms is mentioned in <Effective STL> item 32

#include <algorithm>
#include <vector>

int main() {
  std::vector<int> v;
  // fill it up somehow

  // really remove all elements with value 99
  v.erase(std::remove(v.begin(), v.end(), 99), v.end());
  return 0;
}

