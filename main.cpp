#include "resumable.hpp"

#include <iostream>
using std::cout;

#include <coroutine>
using std::suspend_always;


resumable foo() {
  cout << "Hello\n";
  co_await suspend_always();
  cout << "Coroutine\n";
}


int main(){
  resumable res = foo();

  int i = 0;
  while (res.resume()) {
    cout << ++i << "\n";
  }
}
