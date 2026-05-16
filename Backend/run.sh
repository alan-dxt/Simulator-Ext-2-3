OUTPUT=server

echo "Compilando..."

g++ -std=c++17 \
-I src \
-I src/Routes \
$(find src -name "*.cpp") \
-o $OUTPUT

if [ $? -ne 0]; then
    echo "[Error] The server was not compiled"
    exit 1
fi

echo "The server was compiled succesfully"
./$OUTPUT