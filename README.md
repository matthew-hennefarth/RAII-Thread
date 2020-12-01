# RAII-Thread
Header only file for a C++ RAII thread that joins upon destruction. It has the same interface as a std::thread.

## Example
To create a RAII Thread with a lambda, we can do the following:
```cpp
#include "RAIIThread"
#include <iostream>

int main()
{

  {
    RAIIThread thread([](){
      std::cout << "Hello from RAII Thread" << '\n';
    });
  }

  /* Thread is auto joined upon leaving inner scope */

  return 0;
}
```

Similarly for functions:
```cpp
#include "RAIIThread"
#include <iostream>

void threadUnsafeFunction( int i ){
  std::cout << "This function is not thread safe because of lack of mutex" << '\n';
  std::cout << "The number is " << i << '\n';
}

int main()
{

  {
    RAIIThread thread(threadUnsafeFunction, 5);
  }

  /* Thread is auto joined upon leaving inner scope */

  return 0;
}
```
