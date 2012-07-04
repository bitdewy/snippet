// Thin template idiom is used to reduce duplicate object code.
// It's mentioned in <Effective C++ (3rd edition)> item 44.
// Symbian OS relies on this idiom a lot.

// Not a template
class VectorBase
{
  void insert(void*);
  void* at(int index);
};

// Thin template
template <typename T>
class Vector<T*> : VectorBase
{
  inline void insert(T* t)
  {
    VectorBase::insert(t);
  }
  inline T* at(int index)
  {
    return VectorBase::at(index);
  }
};
