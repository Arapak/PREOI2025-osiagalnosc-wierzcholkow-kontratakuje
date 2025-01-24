CPPFLAGS = -std=c++20 -pedantic -Wall -Wextra -Wformat-security -Wduplicated-cond -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wvla -g3 -O2

all: owk.e

owklib-debug.o: owklib.cpp owklib.h communication.h config.h
	g++ $(CPPFLAGS) -D__NOPASSWORD -D__DEBUG_COMMUNICATION owklib.cpp -c -o owklib-debug.o

owklib-nodebug.o: owklib.cpp owklib.h communication.h config.h
	g++ $(CPPFLAGS) -D__NOPASSWORD owklib.cpp -c -o owklib-nodebug.o

owk.e: owk.cpp owklib-debug.o owklib-nodebug.o
	if [ "$(DEBUG)" = "1" ]; then\
	    g++ $(CPPFLAGS) owklib-debug.o owk.cpp -o owk.e;\
	else\
	    g++ $(CPPFLAGS) owklib-nodebug.o owk.cpp -o owk.e;\
    fi

clean:
	rm -f *.e *.o
