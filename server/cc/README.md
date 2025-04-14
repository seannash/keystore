# Crow Server

A simple HTTP server built with C++ and the Crow library that implements a Ping API endpoint.

## Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler with C++23 support
- Git (for downloading dependencies)

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Running the Server

After building, run the server:
```bash
./crow_server
```

The server will start listening on port 9001.

## API Endpoint

### Ping
- **URL**: `/ping`
- **Method**: `POST`
- **Request Body**:
```json
{
    "message": "your message here"
}
```
- **Response**:
```json
{
    "message": "your message here"
}
```

## Error Responses

- 400 Bad Request: Invalid JSON or missing 'message' parameter
- 500 Internal Server Error: Server-side error 