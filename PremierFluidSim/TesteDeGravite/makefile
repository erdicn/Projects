CC = g++
#CFLAGS = -Wall -Wextra 

CFLAGS = -std=c++20 -Wall -Wextra -Wfloat-equal -Wundef -Wshadow -Wcast-align  -Wcast-qual -Wunreachable-code -Wfloat-equal -Wunsafe-loop-optimizations -O2 #-O 1 2 3 fast g s# -Wconversion  -fsanitize=address -Wstrict-prototypes#-fsanitize=thread -fsanitize=undefined -fstack-protector
LNAME = -lm 
EXEC = gravity.exe
SRC= $(wildcard *.cpp) # $(wildcard */*.cpp) #si on peux regarde dans les dossiers 
OBJ= $(SRC:.c=.o)

all: $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $^

$(EXEC) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LNAME)
	chmod +x $(EXEC)
	@echo compilation terminee

vis:
	python3 visualisation.py

clean:
	rm -rf *.o
	rm -rf donnees.txt
	ls

u:
	make clean
	make 
	time ./$(EXEC)