echo 'Pinging server'
echo "Response:"
curl -X POST http://localhost:9001/public \
  -H "Content-Type: application/json" \
  -d '{
    "jsonrpc": "2.0",
    "method": "get",
    "params": {
      "key": "'${1}'"
    },
    "id": 1
  }'
echo
