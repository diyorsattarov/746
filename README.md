# Sample Web API with C++ using httplib and spdlog

This is a sample C++ application that demonstrates how to create a simple web API using the [httplib](https://github.com/yhirose/cpp-httplib) library for handling HTTP requests and [spdlog](https://github.com/gabime/spdlog) for logging. The application provides basic routes to retrieve user information in JSON format.

## Prerequisites

- [CMake](https://cmake.org/)
- [httplib](https://github.com/yhirose/cpp-httplib) (included as an external dependency)
- [spdlog](https://github.com/gabime/spdlog)

## Usage

1. Clone this repository:

```
   git clone https://github.com/yourusername/your-repo.git
   cd your-repo
```
Build the project using CMake:

```
mkdir build
cd build
cmake ..
make
```
Run the server:

```
./your-web-api
```
Access the following routes:

http://localhost:8080/hi: Returns "Hello World!" in plain text.
http://localhost:8080/json/user/{id}: Returns user data in JSON format for a given user ID.
http://localhost:8080/json/users: Returns a list of all users in JSON format.
Routes
/hi: Returns a simple "Hello World!" message in plain text.
/json/user/{id}: Retrieves user data in JSON format based on the provided user ID.
/json/users: Retrieves a list of all users in JSON format.
License
This project is licensed under the MIT License - see the LICENSE file for details.