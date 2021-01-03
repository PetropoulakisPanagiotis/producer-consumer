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
* semOpN(semaphore, value): &nbsp; Set semaphore's value
* semWaitUntilZero(semaphore): Block process till semaphore's value becomes zeros
* semDown(semaphore): &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Reduce semaphore's value by one

<strong>Producer:</strong>
Writes in the buffer one number and the current time stamp per loop. At the end of every loop ups full and empty sems with the value of n.
In this way consumers can read the new content. Also producer is blocked until empty has the value of 0. In this way feeder will write his new
content only when all the consumers have read the current content.

<strong>Consumers:</strong>
Every consumer has a loop that reads from buffer. At the beginning consumer down the full sem, reads from buffer, down empty sem and then waits until full sem is equal with 0. In this way every consumer reads only once the current content and then is blocked. Also the last consumer will down the empty semaphore. This
semaphore has value 1 and now after that the value 0. That means that the producer will unblocked and write the new content. Finally in the last loop consumer writes in 
results.txt. Every time only one consumer can write in this file. I use mutex semaphore to achieve this. <br />
Note: This algorithm is quite optimal as the number of semaphores is quite small.

## Replicate the results
1. make
2. ./test

##### Author
* Petropoulakis Panagiotis petropoulakispanagiotis@gmail.com
