#include "resumable.hpp"

#include <iostream>
using std::cout;

#include <coroutine>
using std::suspend_always;

gen<> bar() {
  cout << 1;
  co_await suspend_always();
  cout << 2;
}

int main(){
  auto r = bar();
  while (r.resume()) {
    cout << '.';
  }
  cout << "\n";
}
