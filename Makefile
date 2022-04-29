CPPFLAGS = -std=c++11

all: PA1.exe

PA1.exe: polynomial.o main.o
	g++ -o $@ $(CPPFLAGS) polynomial.o main.o

%.o: %.cpp
	g++ $(CPPFLAGS) -c $< -o $@ 

clean:
	del *.o *.exe