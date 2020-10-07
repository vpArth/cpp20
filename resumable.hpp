#pragma once

#include "handle.hpp"
#include <coroutine>

#include <cstdio>
#include <iostream> 
using std::terminate;

class resumable {
public:
  struct promise_type {
    auto get_return_object();
    auto initial_suspend();
    auto final_suspend();
    void return_void();
    void unhandled_exception();
    // auto yield_value();
    // auto return_value();
  };
  using coroutine_handle = std::coroutine_handle<promise_type>;

  resumable(coroutine_handle handle);
  resumable(resumable&) = delete;
  resumable(resumable &&rhs);
  ~resumable();

  bool resume();
private:
  coroutine_handle co_handle;
};

// implementation
resumable::resumable(resumable::coroutine_handle handle) : co_handle(handle) { assert(handle); }
resumable::resumable(resumable &&rhs): co_handle(rhs.co_handle) { rhs.co_handle = nullptr; }
resumable::~resumable() { co_handle.destroy(); }

bool resumable::resume() {
  printf("|  resume()\n");
  if (!co_handle.done()) {
    printf("|  Not done yet... resuming\n");
    co_handle.resume();
  } else {
    printf("|  Already done\n");
  }
  return !co_handle.done();
}


auto resumable::promise_type::get_return_object() {
  printf("|  get_return_object();\n");
  return resumable::coroutine_handle::from_promise(*this);
}
auto resumable::promise_type::initial_suspend() { 
  printf("|  initial_suspend();\n");
  return std::suspend_always(); 
}
auto resumable::promise_type::final_suspend() { 
  printf("|  final_suspend();\n");
  return std::suspend_always(); 
}

void resumable::promise_type::return_void() {
  printf("|  return_void();\n");
}
void resumable::promise_type::unhandled_exception() {
  printf("|  unhandled_exception();\n");
  terminate();
}
/*
 promise_type {
  auto get_return_object();

  auto initial_suspend();
  auto yield_value();
  auto final_suspend();
  auto return_value();
  auto return_void();
  auto unhandled_exception();

 }
 coroutine_handle<void> {
  address()
  from_address()
  done()
  resume()
  destroy()
 }
 coroutine_handle<T>: public coroutine_handle<void> {
  promise()
  return_object from_promise(promise_type)
 }

 co_yield <expr>    co_await promise.yield_value(<expr>)
 co_return          co_await promise.return_void(); end!
 co_return <expr>   co_await promise.return_value(<expr>); end!

Structure of coroutine lifetime:
gen natural_numbers() {
  promise_type promise;
  gen retobj = promise.get_return_object();
  co_await promise.initial_suspend();
  try {
    for(auto i=1;;++i) yield i; // co_await promise.yield_value(i);
  } catch(...) {
    promise.unhandled_exception();
  }
  final_suspend:
  co_await promise.final_suspend();
  end!
}

*/