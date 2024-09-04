# RDMA Test Project

This project is a simple RDMA (Remote Direct Memory Access) test application designed to demonstrate basic RDMA functionality on Ubuntu Linux.

## Prerequisites

Before you begin, ensure you have met the following requirements:
* You have a Ubuntu Linux machine with RDMA-capable hardware.
* You have installed the necessary RDMA libraries and tools:
  ```
  sudo apt-get update
  sudo apt-get install libibverbs-dev librdmacm-dev
  ```
* You have CMake installed (version 3.10 or later):
  ```
  sudo apt-get install cmake
  ```

## Building the Project

To build the project, follow these steps:

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/rdma_test.git
   cd rdma_test
   ```

2. Create a build directory and navigate to it:
   ```
   mkdir build && cd build
   ```

3. Run CMake and build the project:
   ```
   cmake ..
   make
   ```

## Running the Tests

After building the project, you can run the RDMA test application:

* To run as a server:
  ```
  ./rdma_test s <port>
  ```

* To run as a client:
  ```
  ./rdma_test c <port> <server_ip>
  ```

Replace `<port>` with the desired port number and `<server_ip>` with the IP address of the server when running in client mode.

## Project Structure

- `rdma_test.c`: Main source file containing the RDMA test code.
- `CMakeLists.txt`: CMake configuration file for building the project.
- `.gitignore`: Specifies intentionally untracked files to ignore.
- `README.md`: This file, providing project information and instructions.

## Contributing

Contributions to this project are welcome. Please feel free to submit a Pull Request.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contact

If you have any questions or feedback, please contact:

Your Name - your.email@example.com

Project Link: https://github.com/yourusername/rdma_test
