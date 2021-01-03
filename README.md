[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
# Producer-Consumer Problem
<img src="https://cdn-images-1.medium.com/max/800/1*38NMAj0WTa_LD3ojoWsytQ.png"> <br /> 

<strong>One producer and n consumers with shared memory</strong>
<p>In this simulation, one producer sends m elements to n consumers. These elements are stored in a shared memory segment with a capacity of one element. Each element contains a random int and a time stamp. At the end of this simulation, each consumer writes its pid, the m elements and the running average time in a shared results.txt file. 
  
Note: running average time = the time needed to collect all the m items.
</p>

## How It Works
<strong>Semaphores:</strong> 
* full: &nbsp;&nbsp;&nbsp;&nbsp;  [0, n], initial value is 0
* empty: [0, n], initial value is 0
* mutex:&nbsp;&nbsp;0||1, &nbsp;initial value is 1(for the shared results.txt file)

<strong>Operations:</strong> 
* semDown(semaphore): Reduce semaphore's value by one
* semOpN(semaphore, value): Set semaphore's value
* semWaitUntilZero(semaphore): Block process till semaphore's value becomes zeros

<strong>Producer:</strong><br />
Publish a new element to the shared memory segment, set(semOpN) full and empty semaphores to n per loop and wait(semWaitUntilZero) empty semaphore to become zero(aka wait all consumers to read the current element). Repeat this process m times.

<strong>Consumers:</strong><br />
Per loop: reduce(semDown) full semaphore, get an element from the shared memory segment, wait(semWaitUntilZero) full semaphore to become zero(aka wait all consumers to read the current element) and then reduce(semDown) the empty semaphore. Repear this process m times. 

* When empty semaphore becomes zero, producer publish a new element and 

## Replicate the results
1. make
2. ./test

##### Author
* Petropoulakis Panagiotis petropoulakispanagiotis@gmail.com
