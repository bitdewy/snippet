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
