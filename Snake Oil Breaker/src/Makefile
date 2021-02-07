# Compile with debug option and all warnings on. ------------
CXXFLAGS = -g -Wall -O1 -std=c++17 -I $(INCLDIR)
INCLDIR = /usr/include/botan-2
LIBDIR = /usr/lib64/botan-2
LDFLAGS = -L $(LIBDIR)
LIBS = -lbotan-2

# Object modules comprising this application ----------------
OBJ = aes.o bytearray.o dist.o prng.o
OBJ-SO = $(OBJ) snakeoil.o main.o
OBF-BF = $(OBJ) bruteforce.o analyze.o

# Build targets
TARGETS = snakeoil bruteforce

.PHONY: all clean
all: $(TARGETS)

snakeoil: $(OBJ-SO)
	$(CXX) -o $@ $(OBJ-SO) $(LDFLAGS) $(LIBS)

bruteforce: $(OBF-BF)
	$(CXX) -o $@ $(CXXFLAGS) $(OBF-BF) $(LDFLAGS) $(LIBS)

# Delete .o and exe files and force recompilation. ----------
clean:
	rm -f $(OBJ-SO) $(OBF-BF) $(TARGETS)

# Dependencies ----------------------------------------------
aes.o: aes.cpp aes.hpp bytearray.hpp prng.hpp exception.hpp
analyze.o: analyze.cpp analyze.hpp aes.hpp bytearray.hpp prng.hpp \
 dist.hpp exception.hpp
bruteforce.o: bruteforce.cpp analyze.hpp aes.hpp bytearray.hpp prng.hpp \
 dist.hpp
bytearray.o: bytearray.cpp bytearray.hpp prng.hpp exception.hpp
dist.o: dist.cpp dist.hpp exception.hpp
main.o: main.cpp snakeoil.hpp aes.hpp bytearray.hpp prng.hpp
prng.o: prng.cpp prng.hpp
snakeoil.o: snakeoil.cpp snakeoil.hpp aes.hpp bytearray.hpp prng.hpp \
 exception.hpp
