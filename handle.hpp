#pragma once
#include <cstddef> // typedef decltype(nullptr) nullptr_t;

#include <cassert>

template <typename Promise = void> struct coroutine_handle;

template <> struct coroutine_handle<void>{
  constexpr coroutine_handle() noexcept;
  constexpr coroutine_handle(nullptr_t) noexcept;
  coroutine_handle& operator=(nullptr_t) noexcept;
  constexpr void* address() const noexcept;
  constexpr static coroutine_handle from_address(void* addr);
  constexpr explicit operator bool() const noexcept;
  bool done() const;
  void operator()();
  void resume();
  void destroy();
private:
  void* ptr;
};

template <typename Promise> struct coroutine_handle : coroutine_handle<> {
  using coroutine_handle<>::coroutine_handle;
  static coroutine_handle from_promise(Promise&);
  coroutine_handle& operator=(nullptr_t) noexcept;
  constexpr static coroutine_handle from_address(void* addr);
  Promise& promise() const;
};
