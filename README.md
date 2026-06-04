# Thread-Safe Matching Engine (C++)

This project implements an **exchange-style matching engine** in C++, focusing on **correctness, data structures, thread safety, and clean object-oriented design**.  


---

##  Features

- Limit and market order matching
- Price–time priority (FIFO at each price level)
- Multi-symbol order books
- Efficient order cancellation using an order index
- Thread-safe core using mutex-based RAII

---

##  Design Overview (Initial try  )

### Core Components

- **Order**
  - Represents a single order with side, price, quantity, and sequence number
  - Encapsulates order state and quantity updates

- **OrderBook**
  - Manages buy and sell orders for a single symbol
  - Uses ordered maps and FIFO queues to enforce price–time priority
  - Protected by a mutex for safe shared access
  - Supports O(1) cancellation using an auxiliary order index

- **MatchingEngine**
  - Manages multiple order books (one per symbol)
  - Routes orders to the appropriate order book
  - Designed to be safely accessed from multiple threads

- **CLI**
  - Provides an interactive interface to submit and manage orders
  - Keeps input/output logic separate from core matching logic

---

## Thread Safety

- Each order book is protected by a mutex
- Mutexes are managed using **RAII** (`std::lock_guard`) to ensure exception-safe locking
- The engine is designed to support safe access from multiple threads and can be extended for network-based clients

---

##  Supported Commands

LIMIT |symbol| |BUY/SELL| |price| |quantity|

MARKET |symbol| |BUY|SELL| |quantit|

CANCEL |symbol| |order_id|

BEST_BID |symbol|

BEST_ASK |symbol|

EXIT

### Example
LIMIT AAPL BUY 100 10

LIMIT AAPL SELL 100 5

BEST_BID AAPL

BEST_ASK AAPL

---

##  Build Instructions

### Requirements
- C++17 or later
- CMake (≥ 3.10)

### Build
```bash
mkdir build
cd build
cmake ..
cmake --build .
./matching_engine
```

### Benchmark Observation

While benchmarking the system, I noticed that the **multi-thread version is 2 - 4 times faster than the single-thread version**.
When the number of threads is approximately equal to the number of symbols (low contention), the system exhibits near-linear scaling, achieving up to ~x× speedup for x symbols.
Under contention (multiple threads targeting the same symbol), performance degrades, and the speedup reduces to approximately ~2×, due to lock contention within the same OrderBook.

Example result:

```
Single thread
ORDERS : 10000000
TIME : 8.52237
THROUGHPUT : 1.17338e+06

Multi thread
THREADS : 4
SYMBOLS : 4
ORDERS : 4000000
TIME : 0.87488
THROUGHPUT : 4.57206e+06
```

After investigating this, I found that the main reason is the use of **`string` symbols with `unordered_map` lookups**.
Each order requires:

* hashing the symbol string
* performing a map lookup
* doing string comparisons

This creates extra overhead, and in the multi-thread version multiple threads access the same hash table, which increases memory contention.

To fix this, the engine will switch to using **integer `symbol_id` values** internally and store the order books in a `vector<OrderBook>`.
This removes string hashing and map lookups from the hot path.

### IMPROVED DESIGN -- (OPTIMIZING AND LEARNING FROM THE BENCHMARKS RESULTS)

## Project Status

Core matching engine: ✅ Complete

Thread-safe design: ✅ Implemented

CLI interface: ✅ Complete

Networking support: ⏳ In progress

Persistence (WAL / recovery): ⏳ Planned



##  What I Learned

- Designing thread-safe systems using mutex-based RAII  
- Applying object-oriented design principles in a non-trivial C++ system  
- Using STL containers to maintain ordering and performance guarantees  
- Structuring a codebase for extensibility and future features  




