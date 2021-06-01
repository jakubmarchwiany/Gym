CC=g++
CFLAGS=-pthread -std=c++17 -lncurses

all: main

run: main
	gnome-terminal -- ./main

main: main.cpp
	$(CC) -o main main.cpp gym.cpp client.cpp reception.cpp receptionist.cpp sync_channel.cpp place_in_line.cpp screen_printer.cpp locker.cpp crossfit.cpp trainer.cpp bench.cpp $(CFLAGS)
	gnome-terminal -- ./main


clean: main.cpp
	rm main
	$(CC) -o main main.cpp gym.cpp client.cpp reception.cpp receptionist.cpp sync_channel.cpp place_in_line.cpp screen_printer.cpp locker.cpp crossfit.cpp trainer.cpp bench.cpp $(CFLAGS)
	gnome-terminal -- ./main