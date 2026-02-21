*This project has been created as part of the 42 curriculum by **ls-phabm***

# Description
> the project, including its goal and a brief overview

### Project
Create a communication program in the form of a client and a server.

### Goal
Develop a simple program that allows processes (= programs running on a computer) to communicate with each other using a communication protocol called "minitalk", using a series of signals over a single wire. 

### Means
- Communication between the client and server must exclusively use UNIX signals
- Only use these two signals: SIGUSR1 and SIGUSR2

### Constraints 
- 2 programs / execs : client + server
- Error handling : under no circumstances should the program quit unexpectedly (segmentation fault, bus error, double free, and so forth)
- One global var per program

# Instructions
> any relevant information about compilation, installation, and/or execution

1. Server must be started first. Upon launch, it must print its PID
2. Client takes two parameters: server PID + string to send
3. The client must send the specified string to the server
4. Once received, the server must print it without delay -if it seems slow, it is likely too slow
    1. ⚠️ If displaying 100 characters takes 1 second, the program is too slow!
5. server should be able to receive strings from several clients in a row without
needing to restart
    1. Linux system does NOT queue signals when you already have pending
    signals of this type! Bonus time?

Commands to execute program:



# Resources
> listing classic references related to the topic (documentation, articles, tutorials, etc.)
> a description of how AI was used — which tasks and which parts of the project.

* Signals :
	* [<https://koor.fr/C/csignal/signal.wp>](https://koor.fr/C/csignal/signal.wp)
	* [http://brunogarcia.chez.com/Unix/Docs/Signaux.html](http://brunogarcia.chez.com/Unix/Docs/Signaux.html)
* funcheck : <https://github.com/froz42/funcheck>

AI was used to break down *...*