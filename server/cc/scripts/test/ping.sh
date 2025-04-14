echo 'Pinging server'
echo "Response:"
curl -X POST http://localhost:9001/ \
  -H "Content-Type: application/json" \
  -d '{
    "jsonrpc": "2.0",
    "method": "Ping",
    "params": {
      "message": "Hello, World!"
    },
    "id": 1
  }'
echo