#include "range.hpp"
#include <cstdio>

int main() {
  {
    printf("range(10): ");
    auto gen = range<int>(10);
    while (gen.next()) {
      printf("%d ", gen.getValue());
    }
    printf("\n");
  }

  {
    printf("range(a, z+1): ");
    auto gen = range<char>('a', 'z'+1);
    while (gen.next()) {
      printf("%c ", gen.getValue());
    }
    printf("\n");
  }

  {
    printf("range(Z, A-1, -3): ");
    auto gen = range<char>('Z', 'A'-1, -3);
    while (gen.next()) {
      printf("%c ", gen.getValue());
    }
    printf("\n");
    return 0;
  }
}
