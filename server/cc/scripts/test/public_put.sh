echo 'Pinging server'
echo "Response:"
curl -X POST http://localhost:9001/public \
  -H "Content-Type: application/json" \
  -d '{
    "jsonrpc": "2.0",
    "method": "put",
    "params": {
        "key": "'${1}'",
        "value": "'${2}'"
      },
    "id": 1
  }'
echo
