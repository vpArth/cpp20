#pragma once

#include <memory>
#include <coroutine>


template <typename T>
class Generator {
public:
  struct promise_type;
  using handle_type = std::coroutine_handle<promise_type>;
private:
  std::shared_ptr<T> value;
  handle_type coro;
public:
  Generator(handle_type h);
  Generator(const Generator &) = delete;
  Generator(Generator &&other);
  ~Generator();

  Generator& operator=(const Generator &) = delete;
  Generator& operator=(Generator &&other);

  T getValue();
  bool next();
};
template <typename T>
struct Generator<T>::promise_type {
  promise_type() = default;
  ~promise_type() = default;
  
  auto initial_suspend() {return std::suspend_always{}; }
  auto final_suspend() {return std::suspend_always{}; }
  auto get_return_object() {return Generator<T>{handle_type::from_promise(*this)}; }
  auto return_void() {return std::suspend_never{}; }
  void unhandled_exception() {std::exit(1); }

  auto yield_value(T value) {
    current_value = value;
    return std::suspend_always{};
  }
  T current_value;
};


template <typename T> Generator<T>::Generator(handle_type h) : coro(h) {}
template <typename T> Generator<T>::Generator(Generator &&other) : coro(other.coro) {
  other.coro = nullptr;
}
template <typename T> Generator<T>::~Generator() {
  if (coro) {
    coro.destroy();
  }
}
template <typename T> Generator<T>& Generator<T>::operator=(Generator &&other) {
  coro = other.coro;
  other.coro = nullptr;
  return *this;
}
template <typename T> T Generator<T>::getValue() {
  return coro.promise().current_value;
}
template <typename T> bool Generator<T>::next() {
  coro.resume();
  return not coro.done();
}
