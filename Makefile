COMPILER = clang++

OPTIONS = -D"UPPERLIMIT = 1000000000" \
	-DADDITION \
	-DDISCARDDUPES \
	-DCONCATENATION \
	-DMULTIPLICATION \
	-DEXPONENTS \
	-DSUBTRACTION \
	-DDIVISION \
	-DSQUAREROOT \
	# -DFACTORIAL \
	# -DUNITARYNEGATION \
	# -DSHOWNEGATIVES \
	# -DDEBUG

all:	crazy crazy.exe crazybig # crazybig.exe

test:	out out.exe

crazy.exe:	crazy.cpp
	i686-w64-mingw32-g++ -g $(OPTIONS) -o crazy.exe crazy.cpp -ftemplate-depth=1048576

crazy:	crazy.cpp
	$(COMPILER) -g $(OPTIONS) -o crazy crazy.cpp -ftemplate-depth=1048576

crazybig.exe:	crazy.cpp
	i686-w64-mingw32-g++ -g -DUSESTXXL $(OPTIONS) -o crazybig.exe \
	crazy.cpp -lstxxl -ftemplate-depth=1048576

crazybig:	crazy.cpp
	$(COMPILER) -g -DUSESTXXL $(OPTIONS) -o crazybig crazy.cpp \
	-lstxxl -lpthread -ftemplate-depth=1048576

crazy.increasing.out:	crazy
	echo 1 2 3 4 5 6 7 8 9 | ./crazy > crazy.increasing.out

crazy.decreasing.out:	crazy
	echo 9 8 7 6 5 4 3 2 1 | ./crazy > crazy.decreasing.out

crazy.exe.increasing.out:	crazy.exe
	echo 1 2 3 4 5 6 7 8 9 | wine ./crazy.exe > crazy.exe.increasing.out

crazy.exe.decreasing.out:	crazy.exe
	echo 9 8 7 6 5 4 3 2 1 | wine ./crazy.exe > crazy.exe.decreasing.out

crazybig.increasing.out:	crazybig
	echo 1 2 3 4 5 6 7 8 9 | ./crazybig > crazybig.increasing.out

crazybig.decreasing.out:	crazybig
	echo 9 8 7 6 5 4 3 2 1 | ./crazybig > crazybig.decreasing.out

crazybig.exe.increasing.out:	crazybig.exe
	echo 1 2 3 4 5 6 7 8 9 | wine ./crazybig.exe > crazybig.exe.increasing.out

crazybig.exe.decreasing.out:	crazybig.exe
	echo 9 8 7 6 5 4 3 2 1 | wine ./crazybig.exe > crazybig.exe.decreasing.out

out:	crazy.increasing.out crazy.decreasing.out crazybig.increasing.out \
	crazybig.decreasing.out

bigout:	crazybig.increasing.out crazybig.decreasing.out

out.exe:	crazy.exe.increasing.out crazy.exe.decreasing.out \
	# crazybig.exe.increasing.out crazybig.exe.decreasing.out

clean:
	rm -rf crazy crazy.exe crazy.*.out *~ crazybig crazybig.exe crazybig.*.out