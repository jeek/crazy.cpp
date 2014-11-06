all:	crazy crazy.increasing.out crazy.decreasing.out

crazy:	crazy.cpp
	g++ -o crazy crazy.cpp

crazy.increasing.out:	crazy
	echo 1 2 3 4 5 6 7 8 9 | ./crazy > crazy.increasing.out

crazy.decreasing.out:	crazy
	echo 9 8 7 6 5 4 3 2 1 | ./crazy > crazy.decreasing.out

clean:
	rm -rf crazy *~ crazy.*.out