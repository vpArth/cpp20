#include "resumable.hpp"
#include <cstdio>


gen<CoPValue<int>, int> natural_numbers() {
  for (auto i=0;; ++i) co_yield i;
}

int main(){
  auto r = natural_numbers();
  for (auto i=0; i<10; ++i) {
    for (auto li = 0; li < 30 && r.resume(); ++li) {
      printf("%4d", r.get_value());
    }
    printf("\n");
  }
}
