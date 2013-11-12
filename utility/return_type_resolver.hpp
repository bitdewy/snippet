#include <list>
#include <set>
#include <vector>
#include <random>

class GetRandomN {
 public:
  GetRandomN(int n = 1) : count(n) {}

  template <class Container>
  operator Container() {
    Container c;
    for (size_t i = 0; i < count; ++i) {
      c.insert(c.end(), rand()); // push_back is not supported by all standard containers.
    }
    return c;
  }
 private:
  size_t count;
};

// int main() {
//   std::set<int> random_s = GetRandomN(10);
//   std::vector<int> random_v = GetRandomN(10);
//   std::list<int> random_l = GetRandomN(10);
//   return 0;
// }
