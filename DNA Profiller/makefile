build:
	rm -f application.exe 
	g++ -std=c++14 -Wall main.cpp -o application.exe

run: 
	./application.exe

leaks:
	leaks --atExit -- ./application.exe

debug:
	gdb ./application