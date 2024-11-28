# Team: Matthew Schlatter

To compile, just type "make" in the terminal. 

Running with ./ReaderWriterSem_exe 0 1 0 0 1 0 0 0 0 1 returns
the expected output from the txt files given on the Nuros server.

# Pseudocode
## Reader Pseudocode
Lock mutex, increment readerId, unlock mutex
Join queue using wait and queueSem

Lock mutex, increment readCount
If readCount is 1, use wait on rwSem to block writers
Unlock mutex
Post queueSem to allow the next thread

Print "Reader (id) starts reading"
Simulate reading with a delay
Print "Reader (id) ends reading"

Lock mutex, decrement readCount
If readCount is 0, post rwSem to unblock writers
Unlock mutex

## Writer Psuedocode
Lock mutex, increment writerId, unlock mutex

Join queue using wait and queueSem
Lock the shared resource using wait and rwSem
Post queueSem to allow the next thread

Print "Writer (id) starts writing"
Simulate writing with a delay
Print "Writer (id) ends writing"

Post rwSem to unlock the shared resource

## Main Psuedocode
Collect and store command line inputs
Initialize semaphores and mutex

Create 10 threads, reader for 0 and writer for 1
Join all threads

Destroy semaphores and mutex