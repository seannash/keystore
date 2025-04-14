# JSON-RPC Ping API

A simple Flask application that implements a JSON-RPC API with a Ping method.

## Setup

### Option 1: Local Setup
1. Create a virtual environment (optional but recommended):
```bash
python -m venv venv
source venv/bin/activate  # On Linux/Mac
# or
.\venv\Scripts\activate  # On Windows
```

2. Install dependencies:
```bash
pip install -r requirements.txt
```

### Option 2: Docker Setup
1. Build the Docker image:
```bash
docker build -t jsonrpc-ping-api .
```

2. Run the container:
```bash
docker run -p 9002:9002 jsonrpc-ping-api
```

## Running the Application

### Local Run
Start the server:
```bash
python app.py
```

### Docker Run
The server will start automatically when you run the Docker container as shown above.

The server will start on port 9002.

## API Usage

The API endpoint is available at `http://localhost:9002/api`

Example request:
```json
{
    "jsonrpc": "2.0",
    "method": "Ping",
    "params": {
        "message": "Hello, World!"
    },
    "id": 1
}
```

Example response:
```json
{
    "jsonrpc": "2.0",
    "result": {
        "message": "Hello, World!"
    },
    "id": 1
}
``` 