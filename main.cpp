#include "resumable.hpp"

#include <iostream>
using std::cout;

#include <coroutine>
using std::suspend_always;


resumable foo() {
  cout << "#\t\t## Hello\n";
  co_await suspend_always();
  cout << "#\t\t## Coroutine\n";
}


int main(){
  resumable res = foo();
  cout << "> initially suspended" << "\n";
  res.resume();
  cout << "> co_await suspended" << "\n";
  res.resume();
  cout << "> final suspended" << "\n";
  res.resume();
}
