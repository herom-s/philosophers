# Philosophers

A 42 School project implementing the classic **Dining Philosophers Problem** using threads and mutexes in C.

## 📋 Table of Contents

- [About](#about)
- [The Problem](#the-problem)
- [Installation](#installation)
- [Usage](#usage)
- [Arguments](#arguments)
- [Implementation Details](#implementation-details)
- [Project Requirements](#project-requirements)
- [Testing](#testing)
- [Resources](#resources)

## 🎯 About

The Philosophers project is a concurrent programming exercise that explores thread synchronization, mutexes, and resource sharing. The goal is to simulate a group of philosophers sitting at a round table, where they must share forks to eat without starving or encountering deadlocks.

This project teaches fundamental concepts in:
- Multi-threading
- Mutex locks and synchronization
- Race conditions and deadlock prevention
- Time management in concurrent systems

## 🍝 The Problem

Philosophers sit at a circular table with a bowl of spaghetti in the center. Each philosopher alternates between three activities:

1. **Eating** - Requires two forks (one on each side)
2. **Sleeping** - After finishing a meal
3. **Thinking** - After waking up

### Constraints

- There are as many forks as philosophers
- A philosopher needs **two forks** to eat
- Each fork can only be used by one philosopher at a time
- Philosophers don't communicate with each other
- The simulation stops when a philosopher dies of starvation
- Philosophers must avoid dying at all costs

## 🚀 Installation

Clone the repository and compile the project:

```bash
git clone https://github.com/herom-s/philosophers.git
cd philosophers/philo
make
```

This will create the `philo` executable in the `philo` directory.

## 💻 Usage

Run the program with the following syntax:

```bash
cd philo
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Example

```bash
./philo 5 800 200 200
```

This starts a simulation with:
- 5 philosophers
- 800ms time until death
- 200ms eating time
- 200ms sleeping time

### With Optional Argument

```bash
./philo 5 800 200 200 7
```

The simulation will stop when all philosophers have eaten at least 7 times.

## 📝 Arguments

| Argument | Description | Unit |
|----------|-------------|------|
| `number_of_philosophers` | Number of philosophers (and forks) at the table | count |
| `time_to_die` | Time before a philosopher dies without eating | milliseconds |
| `time_to_eat` | Time a philosopher spends eating | milliseconds |
| `time_to_sleep` | Time a philosopher spends sleeping | milliseconds |
| `[number_of_times_each_philosopher_must_eat]` | Optional: simulation stops when all philosophers have eaten this many times | count |

**Note:** All time arguments must be positive integers representing milliseconds.

## 🔧 Implementation Details

### Mandatory Part

- Each **philosopher** is a thread
- Each **fork** is protected by a mutex
- Philosophers are numbered from 1 to N
- Philosopher 1 sits next to philosopher N (circular arrangement)
- A philosopher takes the forks to their immediate left and right

### Output Format

The program logs each philosopher's action with timestamps:

```
[timestamp_in_ms] [philosopher_number] has taken a fork
[timestamp_in_ms] [philosopher_number] is eating
[timestamp_in_ms] [philosopher_number] is sleeping
[timestamp_in_ms] [philosopher_number] is thinking
[timestamp_in_ms] [philosopher_number] died
```

**Requirements:**
- Messages must not be intertwined
- Death must be reported within 10ms of occurrence
- Timestamps are in milliseconds since simulation start

## ✅ Project Requirements

- Written in C
- Follows the 42 Norm
- No memory leaks
- No crashes or undefined behavior
- No global variables
- Proper error handling

### Allowed Functions

- `memset`, `printf`, `malloc`, `free`, `write`
- `usleep`, `gettimeofday`
- `pthread_create`, `pthread_detach`, `pthread_join`
- `pthread_mutex_init`, `pthread_mutex_destroy`
- `pthread_mutex_lock`, `pthread_mutex_unlock`

## 🧪 Testing

### Basic Tests

```bash
# Should not die
./philo 5 800 200 200

# Should not die
./philo 4 410 200 200

# Should die
./philo 4 310 200 100

# Should not die with meal limit
./philo 5 800 200 200 7
```

### Edge Cases

```bash
# One philosopher (should die)
./philo 1 800 200 200

# Invalid arguments
./philo 0 800 200 200
./philo 5 -1 200 200
./philo 5 800 abc 200
```

## 📚 Resources

### Concepts

- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Thread (computing) - Wikipedia](https://en.wikipedia.org/wiki/Thread_(computing))
- [Mutex - Wikipedia](https://en.wikipedia.org/wiki/Mutual_exclusion)

### Functions

- `pthread_create()` - Create a new thread
- `pthread_join()` - Wait for thread termination
- `pthread_mutex_lock()` - Lock a mutex
- `pthread_mutex_unlock()` - Unlock a mutex
- `gettimeofday()` - Get current time
- `usleep()` - Suspend execution for microseconds

## 📄 License

This project is part of the 42 School curriculum.

## 👤 Author

**herom-s**

---

*Note: This project is for educational purposes. If you're a 42 student, please implement your own solution rather than copying code. Understanding the concepts is crucial for your learning.*
