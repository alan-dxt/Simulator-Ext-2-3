OUTPUT=server

echo "Compilando..."

g++ -std=c++17 \
-I src \
$(find src -name "*.cpp") \
-o $OUTPUT

if [$? -ne 0]; then
    echo "[Error] The server was not compiled"
    exit 1
fi

echo "The server was compiled succesfully"
./$OUTPUT