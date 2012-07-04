// Guideline #1: Prefer to make interfaces nonvirtual, using Template Method
// design pattern.
// Guideline #2: Prefer to make virtual functions private.
// Guideline #3: Only if derived classes need to invoke the base
// implementation of a virtual function, make the virtual function protected.
// Guideline #4: A base class destructor should be either public and virtual,
// or protected and nonvirtual.

// NOTICE Fragile Base Class (FBC) interface problem

// NVI (Non-Virtual Interface) idioms is mentioned in
// <Effective C++ (3rd edition)> item 35.

#include <set>

class Set
{
  std::set<int> s_;
public:
  void add(int i)
  {
    s_.insert(i);
    add_impl(i); // Note virtual call.
  }
  void addAll(int* begin, int* end)
  {
    s_.insert(begin, end);
    addAll_impl(begin, end); // Note virtual call.
  }
private:
  virtual void add_impl(int i) = 0;
  virtual void addAll_impl(int* begin, int* end) = 0;
};

class CountingSet : public Set
{
private:
  int count_;
  virtual void add_impl(int i)
  {
    count_++;
  }
  virtual void addAll_impl(int* begin, int* end)
  {
    count_ += std::distance(begin, end);
  }
};

