#include <thread>

class ThreadRAII {
public:
  using RAIIAction = void (std::thread::*)();  // dtor action
  ThreadRAII(std::thread&& thread, RAIIAction a)
    : t(std::move(thread)), action(a) {}

  ~ThreadRAII() {
    if (t.joinable()) { (t.*action)(); }
  }

  std::thread& get() { return t; }
private:
  RAIIAction action;
  std::thread t;
};

void doThisWork() {}
void doThatWork() {}

int main(int argc, char* argv[]) {
  ThreadRAII t1(std::thread(doThisWork), &std::thread::join);
  ThreadRAII t2(std::thread(doThatWork), &std::thread::detach);
  return 0;
}
