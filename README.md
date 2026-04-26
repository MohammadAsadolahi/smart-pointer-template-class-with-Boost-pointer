# SmartVector

**A zero-leak, template-based linked list built entirely on C++ smart pointers.**

---

## Overview

`SmartVector` is a generic, dynamically-sized container implemented as a singly linked list where every allocation is owned by `std::shared_ptr`. There are no raw `new`/`delete` pairs to manage — memory is reclaimed automatically when nodes leave scope, making this data structure inherently leak-proof by design.

This project demonstrates a disciplined approach to modern C++ memory management: replacing manual allocation with RAII-compliant smart pointers at every level of the data structure — node linkage, element storage, and exception propagation.

## Architecture

```
SmartVector<Type>
│
├── root ──► shared_ptr<Node>
│               ├── data ──► shared_ptr<Type>
│               └── nextNode ──► shared_ptr<Node>
│                                   ├── data ──► shared_ptr<Type>
│                                   └── nextNode ──► shared_ptr<Node>
│                                                       └── ...
└── count (int)
```

**Key design decisions:**

| Concern | Approach |
|---|---|
| Node ownership | `std::shared_ptr<Node>` — automatic cascade destruction on removal |
| Element storage | `std::shared_ptr<Type>` — deep copy on insert, reference access via `operator[]` |
| Error handling | `std::unique_ptr<Exception>` — heap-allocated exceptions with exclusive ownership semantics |
| Generic typing | C++ templates — works with any copyable type |

## API

```cpp
SmartVector<int> vec;

vec.add(42);              // Append element to the end of the list
vec.add(7);

int count = vec.getCount(); // → 2

int& val = vec[0];          // → 42 (returns by reference)

vec.remove(1);              // Remove element at index 1
```

| Method | Signature | Description |
|---|---|---|
| `add` | `void add(Type data)` | Appends a deep-copied element to the tail of the list |
| `remove` | `void remove(int index)` | Removes the node at the given index; throws on out-of-bounds |
| `getCount` | `int getCount()` | Returns the current number of elements |
| `operator[]` | `Type& operator[](int index)` | Returns a mutable reference to the element at the given index; throws on out-of-bounds |

## Exception Handling

Bounds violations throw a `unique_ptr<Exception>` carrying a human-readable description string:

```cpp
try {
    vec[999];
} catch (unique_ptr<Exception>& e) {
    cout << e->getDescription(); // "can't access object, index out of vector"
}
```

## Build

Requires a C++11 (or later) compiler.

```bash
g++ -std=c++11 -o smartvector SmartVector.cpp
```

## File Structure

```
├── SmartVector.h      # Template class declaration + Exception class
├── SmartVector.cpp    # Template method implementations
└── README.md
```

## License

Released for educational and reference purposes.
