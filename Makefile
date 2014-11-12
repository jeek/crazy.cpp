COMPILER = g++ -std=gnu++0x

SRC = crazyfast.cpp
# SRC = crazy.cpp
# SORT = | sort -n

OPTIONS = -D"UPPERLIMIT = 1000000000" \
	-DADDITION \
	-DDISCARDDUPES \
	-DCONCATENATION \
	-DMULTIPLICATION \
	-DEXPONENTS \
	-DSUBTRACTION \
	-DDIVISION \
	-DSQUAREROOT \
	-DFACTORIAL \
	-DUNITARYNEGATION \
	-DREVERSEDIVISION \
	# -DSHOWQUEUESTEPS \
	# -DDEBUG
	# -DSHOWNEGATIVES \

all:	crazy crazy.exe

test:	out out.exe new.out

new.out:	$(SRC) crazy new.py
	make clean
	make crazy
	python new.py|bash|tee new.out

crazy.exe:	$(SRC)
	i586-mingw32msvc-g++ -g $(OPTIONS) -o crazy.exe $(SRC)

crazy:	$(SRC)
	$(COMPILER) -g $(OPTIONS) -o crazy $(SRC)

crazy.increasing.out:	crazy
	./crazy 1 2 3 4 5 6 7 8 9 $(SORT) > crazy.increasing.out

crazy.decreasing.out:	crazy
	./crazy 9 8 7 6 5 4 3 2 1 $(SORT) > crazy.decreasing.out

crazy.exe.increasing.out:	crazy.exe
	wine ./crazy.exe 1 2 3 4 5 6 7 8 9 > crazy.exe.increasing.out

crazy.exe.decreasing.out:	crazy.exe
	wine ./crazy.exe 9 8 7 6 5 4 3 2 1 > crazy.exe.decreasing.out

out:	crazy.increasing.out crazy.decreasing.out

out.exe:	crazy.exe.increasing.out crazy.exe.decreasing.out

clean:
	rm -rf crazy crazy.exe crazy.*.out *~ new.out
