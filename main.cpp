#include <cstdio>
#include <vector>
using std::vector;

vector<int> range(int start, int stop, int step = 1) {
    vector<int> numbers;

    for (auto i = start; i < stop; i += step) {
        numbers.push_back(i);
    }

    return numbers;
}
vector<int> range(int stop) {return range(0, stop, 1); }


#include <algorithm>
class Range {
  int m_start, m_stop, m_step;
  int m_current;
  int state = 0;
public:
  Range(int start, int stop, int step = 1)
  : m_start(start), m_stop(stop), m_step(step) {
  }
  Range(int stop) {
    Range(1, stop, 1);
  }    
    // member typedefs provided through inheriting from std::iterator
    class iterator: 
      public std::iterator< std::input_iterator_tag, int, int, const long*, long >{
        int num;
        int step;
    public:
        explicit iterator(int _num = 0, int _step = 1) : num(_num), step(_step) {}
        iterator& operator++() {num = num + step; return *this;}
        iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
        bool operator==(iterator other) const {return num == other.num;}
        bool operator!=(iterator other) const {return !(*this == other);}
        reference operator*() const {return num;}
    };
  iterator begin() {return iterator(m_start, m_step);}
  iterator end() {
    auto t = m_start;
    while ((m_step<0 && m_stop < t) || (t < m_stop && m_step>0)) {
      t += m_step;
    }

    return iterator(t);
  }
};


int main() {
 
  {
    const auto numbers = range(-10, 11);
    for (auto n : numbers) {
      printf("%3d ", n);
    }
    printf("\n");

    for (auto n : range(100)) {
    	printf("%3d ", n);
    	if ((n+1) % 20 == 0) printf("\n");
    }
	   printf("\n");
  }
  
  {
    int c;

    c = 0;
    Range odds{41, 100, 2};
    for (auto n: odds) {
        printf("%3ld ", n);
        if ((++c) % 20 == 0) printf("\n");
    }
  	printf("\n");
 
    c = 0;
    Range neg{99, 9, -3};
    for (auto n: neg) {
        printf("%3ld ", n);
        if ((++c) % 20 == 0) printf("\n");
    }
    printf("\n");
  }

  printf("\n");
}


