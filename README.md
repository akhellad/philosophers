# Philosophers Project

## Introduction

This repository is dedicated to the Philosophers project, part of the 42 school curriculum, which focuses on the problem of dining philosophers. The challenge is to simulate a scenario where multiple philosophers sit around a table, alternating between eating, thinking, and sleeping, without running into deadlocks. The project aims to teach students about process synchronization, mutexes, and semaphores, ensuring that no philosopher starves.

## Features

- Simulation of the dining philosophers problem.
- Avoidance of deadlocks and starvation.
- Use of threads and mutexes (or semaphores) for synchronization.
- Logging of philosopher actions with precise timestamps.

## Dependencies

The Philosophers project is written in C and depends on the following:

- GCC or Clang compiler
- Make (for compiling)
- POSIX threads (pthread library)
- A Unix-based operating system (Linux or MacOS)

## Installation

To compile the Philosophers project, please follow these steps:

1. Clone the repository to your local machine:

```bash
git clone git@github.com:akhellad/philosophers.git
```
2. Navigate to the cloned directory:

```bash
cd philosophers
```

3. Compile the project:

```bash
make
```

This command compiles the philosopher program, ready to be executed to simulate the dining philosophers problem.

## Usage

To start the simulation, execute the program with the following command format:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The total number of philosophers around the table.
- `time_to_die`: The time (in milliseconds) a philosopher can spend without eating before dying.
- `time_to_eat`: The time (in milliseconds) it takes for a philosopher to eat.
- `time_to_sleep`: The time (in milliseconds) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): The simulation will stop if all philosophers eat at least this number of times.

## Example

```bash
./philo 5 800 200 200 5
```

This example starts a simulation with 5 philosophers, where each philosopher must eat within 800 milliseconds, spends 200 milliseconds eating, and 200 milliseconds sleeping. The simulation ends once each philosopher has eaten at least 5 times.

## Credits

This project was developed by Ahmed Khelladi, a student at Ecole 42. It demonstrates a practical application of threads and synchronization mechanisms to solve the classic problem of the dining philosophers.
