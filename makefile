all:
	rm -rf build && mkdir build
	cd build && cmake .. && cmake --build . && cd src && ./server
	gcc client.c -o client
