// Pimpl (pointer to implementation) idioms is mentioned in
// <Effective C++ (3rd edition)> item 25 & item 31.

// handle.h
class Handle
{
private:
  struct CheshireCat;            // Not defined here
  CheshireCat* smile;            // Handle

public:
  Handle();                      // Constructor
  Handle(const Handle&);         // Copy constructor
  const Handle& operator=(Handle);     // Copy assignment operator
  ~Handle();                     // Destructor
  // Other operations...
};

// handle.cc
#include "handle.h"
#include <algorithm>  // std::swap

struct Handle::CheshireCat
{
  int a;
  int b;
};

Handle::Handle()
  : smile(new CheshireCat())
{
  // do nothing
}

Handle::Handle(const Handle& other)
  : smile(new CheshireCat(*(other.smile)))
{
  // do nothing
}

const Handle& Handle::operator=(Handle other)
{
  std::swap(this->smile, other.smile);
  return *this;
}

Handle::~Handle()
{
  delete smile;
}
