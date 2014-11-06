all:	crazy crazy.out

crazy:	crazy.cpp
	g++ -o crazy crazy.cpp

crazy.out:	crazy
	./crazy > crazy.out

clean:
	rm -rf crazy *~ crazy.out