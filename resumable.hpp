#pragma once

#include "handle.hpp"
#include <coroutine>

class resumable {
public:
  struct promise_type {
    auto get_return_object();
    auto initial_suspend();
    auto final_suspend();
    void return_void();
    void unhandled_exception();
  };
  using coro_handle = std::coroutine_handle<promise_type>;

  resumable(coro_handle handle);
  resumable(resumable&) = delete;
  resumable(resumable&&) = delete;
  ~resumable();

  bool resume();
private:
  coro_handle handle_;
};

// implementation
#include <iostream> 
using std::terminate;

#include <coroutine>

resumable::resumable(resumable::coro_handle handle) : handle_(handle) { assert(handle); }
resumable::~resumable() { handle_.destroy(); }

bool resumable::resume() {
  if (not handle_.done())
    handle_.resume();
  return not handle_.done();
}


auto resumable::promise_type::get_return_object() {
  return resumable::coro_handle::from_promise(*this);
}
auto resumable::promise_type::initial_suspend() { return std::suspend_always(); }
auto resumable::promise_type::final_suspend() { return std::suspend_always(); }

void resumable::promise_type::return_void() {}
void resumable::promise_type::unhandled_exception() {
  terminate();
}
