# Packet Sniffer

A simple network packet sniffer developed in C++ for Linux systems. This project uses Raw Sockets (`AF_PACKET`) to intercept network traffic directly at the data link layer (`Ethernet`).

## Features

- Continuous capture of raw packets from the network interface.

- Real-time display of captured packet sizes.

- Automated compilation using a Makefile.

- A solid foundational structure to expand into parsing specific headers (IP, TCP, UDP, etc.).

## Prerequisites

To compile and run this project, you need a Linux environment (e.g., Debian/Ubuntu) with the standard build tools installed:

- *C++ Compiler (g++ or c++)*

- *make utility*

To install the necessary tools on Debian/Ubuntu, run:
```
sudo apt update
sudo apt install build-essential
```

## How to Build and Run

### 1. Clone the repository to your local machine
```
git clone git@github.com:alexis6859/PacketSniffer.git
cd PacketSniffer
```

### 2. Compile to an executable
Simply run the following command in the root directory of the project:
```
make
```

This will automatically read the Makefile, create a build/ directory, and generate the executable file inside it.

### 3. Run the application
Because capturing raw network packets requires superuser privileges, you must execute the program using sudo:
```
sudo ./build/sniffer
```

To stop the packet capture at any time, press `Ctrl + C`.

### 4. Project Structure
```
PacketSniffer/
├── Makefile         # Build automation script
├── README.md        # Project documentation
└── src/             # Main project folder for the packet sniffer
    └── *.cpp        
```

### 5. Cleaning Up

If you want to remove the compiled executable and the build/ directory, simply run:

```
make clean
```
<br>
<hr>
<br>

# ⚠️ <ins>Legal & Ethical Disclaimer</ins>

***This project was created strictly for educational purposes and network protocol study. Intercepting network packets on networks you do not own or without explicit authorization is illegal. Please use this software responsibly, only on your own equipment or on networks where you have clear permission to monitor traffic.***