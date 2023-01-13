# Multi-threaded element queue in C++

## Build and run instructions

- To build the project:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

- To run the tests:

```bash
# inside 'build' folder 
ctest
```

- To run the app:

```bash
# inside 'build' folder 
./app
```

>All these commands where tested using zsh on masOS Monterey (version 12.6.1), cmake (version 3.25.0) and AppleClang (version 14.0.0.1400029).

## Problem formalization

#### 1. Develop a class from scratch to queue a finite number of elements. This class will be used for multi-threaded communication as follows:

- Reading thread pops elements while writing thread pushes elements.
- If the queue is empty, reading thread will block and wait for the next element.
- If the queue is full, writing thread will block and wait for another thread to remove an item.

Extra: The reading/writing threads should optionally block for a certain period of time. If the action is successful within this time, true is returned, otherwise false.

The class interface should look like this:

```c++
class Queue<T> {
    Queue(int size) {...}
    void Push(T element) {...}
    T Pop() {...}
    int Count() {...} // Amount of elements stored now
    int Size() {...} // Max number of elements
}
```

As an example implement the following in `main()`:

```
Writing Thread      |   Queue   |   Reading Thread
--------------------+-----------+----------------------
New Queue<int>(2)
Push(1)                 1
                                    Pop() -> 1
Push(2)                 2
Push(3)                 2,3
Push(4) // blocks
                        3           Pop() -> 2
// is released          3,4
                        4           Pop() -> 3
                                    Pop() -> 4
                                    Pop() // blocks
Push(5)                 5
                                    -> 5 // is released
```
Notes:
- An instance of std::queue may be used internally, but race conditions must be avoided.
- Do not forget to document your code. Preferably use Doxygen style.
- Performance issues are optional.

#### 2. Develop unit tests for the Queue class with support of a framework (e.g. cppunit, googletest, catch).

#### 3. Develop a CMake configuration file to ease the build process (inc. tests).