from flask import Flask, request, jsonify
from jsonrpc import JSONRPCResponseManager, dispatcher

app = Flask(__name__)

@dispatcher.add_method
def Ping(message: str) -> dict:
    """
    Echoes back the provided message
    """
    if not isinstance(message, str):
        raise ValueError("Message must be a string")
    return {"message": message}

@app.route('/api', methods=['POST'])
def jsonrpc_endpoint():
    response = JSONRPCResponseManager.handle(request.data, dispatcher)
    return jsonify(response.data)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=9002, debug=True) 