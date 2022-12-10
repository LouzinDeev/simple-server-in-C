all:
	cd build && cmake .. && cmake --build . && cd src && ./server
	gcc client.c -o client
