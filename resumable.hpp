#pragma once

#include "handle.hpp"
#include <coroutine>

#include <cstdio>
#include <iostream> 
using std::terminate;


/* promise_type */
struct CoPromiseAlways {
  auto get_return_object();
  auto initial_suspend();
  auto final_suspend();
  void return_void();
  void unhandled_exception();
  // auto yield_value();
  // auto return_value();
};
auto CoPromiseAlways::get_return_object() {
  return std::coroutine_handle<CoPromiseAlways>::from_promise(*this); 
}
auto CoPromiseAlways::initial_suspend() {return std::suspend_always(); }
auto CoPromiseAlways::final_suspend() {return std::suspend_always(); }
void CoPromiseAlways::return_void() {} 
void CoPromiseAlways::unhandled_exception() {terminate(); }

/* return_object */
template <typename Promise=CoPromiseAlways>
class gen {
public:
  using coroutine_handle = std::coroutine_handle<Promise>;
  using promise_type = Promise;

  gen(coroutine_handle handle);
  gen(gen&) = delete;
  gen(gen &&rhs);
  ~gen();

  bool resume();
private:
  coroutine_handle co_handle;
};
template <typename Promise> gen<Promise>::gen(gen<Promise>::coroutine_handle handle) : co_handle(handle) { assert(handle); }
template <typename Promise> gen<Promise>::gen(gen &&rhs): co_handle(rhs.co_handle) { rhs.co_handle = nullptr; }
template <typename Promise> gen<Promise>::~gen() { co_handle.destroy(); }
template <typename Promise> bool gen<Promise>::resume() {
  bool alive = !co_handle.done();
  if (alive) co_handle.resume();
  return alive;
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