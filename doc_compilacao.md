huina@xubuntu-pc:~/CPPChat_server$ cmake -S . -B build
-- The CXX compiler identification is GNU 13.3.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/huina/CPPChat_server/build
huina@xubuntu-pc:~/CPPChat_server$ cmake --build build
[ 50%] Building CXX object CMakeFiles/chat_server.dir/src/server/main.cpp.o
[100%] Linking CXX executable chat_server
[100%] Built target chat_server
huina@xubuntu-pc:~/CPPChat_server$ g++ -std=c++20 src/server/main.cpp -o chat_server
huina@xubuntu-pc:~/CPPChat_server$ ./chat_server
================================
CPPChat Server v1.0
================================
Initializing network...
Waiting for connections...
huina@xubuntu-pc:~/CPPChat_server$ ^C
huina@xubuntu-pc:~/CPPChat_server$ 

comandos:

cmake -S . -B build
cmake --build build

g++ -std=c++20 src/server/main.cpp -o chat_server

./chat_server
ou
./build/chat_server

sempre que alterar o main executa cmake --build build e ./build/chat_server


----crair uma pasta pelo terminal----
mkdir -p src/network

---criar um arquivo pelo terminal----
touch network/tcp_server.cpp