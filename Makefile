default:
	/usr/bin/gcc --include-directory=includes -fdiagnostics-color=always -g src/main.c -lssl -lcrypto -o main
	./main
