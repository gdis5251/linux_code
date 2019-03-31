Miutl=Triangle.o Main.o
main:$(Miutl)
	g++ $(Miutl) -o main
Triangle.o:Triangle.cpp
	g++ -c Triangle.cpp -o Triangle.o
Main.o:Main.cpp
	g++ -c Main.cpp -o Main.o

.PHONY:clean
clean:
	rm -rf $(Miutl) main
