echo 'Pinging server: {"message": "Hello, World!"}'
echo "Response:"
curl -X POST http://localhost:9001/ping \
  -H "Content-Type: application/json" \
  -d '{"message": "Hello, World!"}'
echo