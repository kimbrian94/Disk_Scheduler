# Disk Scheduler

Design and Implementation of Disk Scheduling Algorithms

1)FCFS
2)SCAN
3)C-SCAN

This program will service a disk with 100 cylinders numbered 0 to 99. 
This program will read a random series of 25 unique cylinder requests from a file called input.txt 
and service them according to each of the algorithms listed above. This program will be passed the 
initial position of the disk head and write the seek sequence and the total amount of head movement 
required by each algorithm in a file called output.txt.

To compile, create executable and execute run following commands:
	make
	./diskScheduler input.txt
