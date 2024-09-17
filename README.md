

---

# Mini Operating System

## Overview

This project implements a mini operating system using key OS concepts like process synchronization, resource allocation, multitasking, and process scheduling. It is built in C language and offers two modes of operation: **Kernel Mode** and **User Mode**. The system allows users to execute applications like file management, games, and system utilities, while handling resource management efficiently.

## Features

### 1. Welcome Screen
When the system is launched using `./main`, users are greeted with a welcome screen and prompted to choose between:

- **User Mode**: Allows running basic tasks as in a typical operating system.
- **Kernel Mode**: Enables the user to modify system hardware requirements such as RAM, storage, and CPU cores.

### 2. Kernel Mode
By default, the system operates with the following configuration:
- RAM: 8 GB
- Storage: 256 GB
- CPU Cores: 8

In **Kernel Mode**, users can customize these hardware settings interactively.

### 3. User Mode
**User Mode** provides a variety of applications and system utilities:

- **File Management/Text Editor**:
  - `Copy`: Create a copy of a file.
  - `Compress`: Compress a file.
  - `Delete`: Delete a specified file.
  - `File`: Displays the location of a file, similar to the `ls` command in Linux.

- **Games**:
  - Hangman
  - Random Number Generator
  - Tic Tac Toe

- **Music Player**: Users can play `.mp3` files from the terminal.

- **System Utilities**:
  - **Time**: Display current system time.
  - **Stopwatch**: Basic stopwatch functionality.
  - **Calculator**: Perform arithmetic calculations.
  - **Calendar**: View the system calendar.

### 4. Process Synchronization
The system uses semaphores to manage process synchronization and ensure mutual exclusion when accessing shared resources like RAM, storage, and CPU cores. Only one thread can access the shared resources at a time, ensuring that concurrent processes do not conflict.

### 5. Resource Allocation
Resources such as RAM, storage, and CPU cores are allocated based on user input. The system tracks the usage of these resources and enforces limits using semaphores to prevent resource conflicts.

### 6. Multitasking
The system supports multitasking by running each application in a separate terminal using threads. If the system resources are fully utilized, new tasks are queued in the **ready queue** until resources are available.

### 7. Process Scheduling
Tasks are enqueued and executed based on their priority and the availability of system resources. The system automatically handles task execution and resource management to ensure efficient multitasking.

## Code Structure
The code is implemented in C, utilizing libraries such as `pthread`, `semaphore`, and `unistd` for thread management, process synchronization, and system operations. The core functions include:

- `runCommands()`: Executes a command in a separate thread, ensuring proper resource allocation.
- `killTerminals()`: Terminates all running terminals when the OS shuts down.
- `AddProcessToLog()` / `RemoveProcessFromLog()`: Manages a log of currently running processes.
- `GetCountProcessLog()`: Retrieves the count of active processes for resource monitoring.

## How to Run

1. Compile the code using `g++`:
   ```bash
   g++ -o main main.cpp
   ```

2. Run the mini OS:
   ```bash
   ./main
   ```

3. Follow the prompts to select **Kernel Mode** or **User Mode** and start using the system.

### Example Commands:
- Copy a file: Select the copy option in the feature menu.
- Play music: Choose the music player and follow the prompts.
- Run multiple tasks: Select multiple applications from the feature menu, and the system will handle multitasking.

## Dependencies

- g++
- pthread
- semaphore
- zlib (for file compression)
- mpg123 (for music playback)

## Contributors
- M. Tayyab Khan (22F-3440)
- M. Ahmad (22F-8814)
- Taha Saadat (22F-3439)

---
