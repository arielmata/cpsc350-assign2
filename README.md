# Game of Life
A copy of the mtchat repo with updated docker files.

This repo contains programs to implement a multi-threaded TCP chat server and client

* MtClient.java handles keyboard input from the user.
* ClientListener.java receives responses from the server and displays them.
* MtServer.java listens for client connections and creates a ClientHandler for each new client.
* ClientHandler.java receives messages from a client and relays it to the other clients.


## Identifying Information
* Name: Ariel Gutierrez
* Student ID: 2318163
* Email: arigutierrez@chapman.edu
* Course: CPSC 350-01
* Assignment: Assignment 2

## Source Files
* assign2.h
* assign2.cpp
* main.cpp

## References
* Converting string of int to int type - https://www.geeksforgeeks.org/converting-strings-numbers-cc/
* String to double - http://www.cplusplus.com/reference/string/stod/
* How to know if user pressed enter key - https://stackoverflow.com/questions/42818899/detecting-enter-key-in-c 
* Sleep function because system("pause") didn't work for me - https://www.softwaretestinghelp.com/cpp-sleep/
* Class Notes and Textbook

## Known Errors
* None that I know of

## Build and Execution Instructions
* Clone repository to computer
* Start and attach compsci docker container
* Go to the directory/repository you cloned on computer
* Compile program: make all
* Run program: ./assign2.out
* Clear .out files: make realclean
