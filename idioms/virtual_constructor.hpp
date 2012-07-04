// Virtual Constructor idioms is mentioned in <More Effective C++> item 25

// implement in google protocol buffer
// http://code.google.com/p/protobuf/source/browse/trunk/src/google/protobuf/message.h
// virtual Message* New() const = 0;

class Employee
{
public:
  virtual ~Employee() { }  // Native support for polymorphic destruction
  virtual Employee* create() const = 0; // Virtual constructor (creation)
  virtual Employee* clone() const = 0;  // Virtual constructor (copying)
};

class Manager : public Employee     // "is-a" relationship
{
public:
  ~Manager() { }                // Destructor
  Manager* create() const       // Virtual constructor (creation)
  {
    return new Manager();       // Default constructor
  }
  Manager* clone() const        // Virtual constructor (copying)
  {
    return new Manager(*this);  // Default copy constructor
  }
};

class Programmer : public Employee
{
public:
  ~Programmer() { }
  Programmer* create() const
  {
    return new Programmer();
  }
  Programmer* clone() const
  {
    return new Programmer(*this);
  }
};

Employee* duplicate(const Employee& e)
{
  return e.clone();  // Using virtual constructor idiom
}
