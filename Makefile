COMPILER = g++

OPTIONS = -D"UPPERLIMIT = 1000000000" \
	-DADDITION \
	-DDISCARDDUPES \
	-DCONCATENATION \
	-DMULTIPLICATION \
	-DEXPONENTS \
	-DSUBTRACTION \
	-DDIVISION \
	# -DSQUAREROOT \
	# -DFACTORIAL \
	# -DUNITARYNEGATION \
	# -DSHOWNEGATIVES \
	# -DDEBUG

all:	crazy crazy.increasing.out crazy.decreasing.out crazy.exe crazy.exe.increasing.out crazy.exe.decreasing.out

crazy.exe:	crazy.cpp
	i586-mingw32msvc-g++ $(OPTIONS) -o crazy.exe crazy.cpp

crazy:	crazy.cpp
	$(COMPILER) $(OPTIONS) -o crazy crazy.cpp

crazy.increasing.out:	crazy
	echo 1 2 3 4 5 6 7 8 9 | ./crazy > crazy.increasing.out

crazy.decreasing.out:	crazy
	echo 9 8 7 6 5 4 3 2 1 | ./crazy > crazy.decreasing.out

crazy.exe.increasing.out:	crazy.exe
	echo 1 2 3 4 5 6 7 8 9 | wine ./crazy.exe > crazy.exe.increasing.out

crazy.exe.decreasing.out:	crazy.exe
	echo 9 8 7 6 5 4 3 2 1 | wine ./crazy.exe > crazy.exe.decreasing.out

out:	crazy.increasing.out crazy.decreasing.out

out.exe:	crazy.exe.increasing.out crazy.exe.decreasing.out

clean:
	rm -rf crazy crazy.exe crazy.*.out *~