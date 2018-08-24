[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
# Producer-Consumer problem
<img src="https://cdn-images-1.medium.com/max/800/1*38NMAj0WTa_LD3ojoWsytQ.png"> <br /> 

**One producer and n consumers with a buffer of only one element** <br />
In this simulation producer writes in a buffer. Producer has m elements(random int) to write. Buffer has 2 contents. Current number and a time stamp.
Time stamp is the date that the feeder writes the current number. There are n consumers. For each loop consumers should read the current number 
and then the producer should be informed to change current number. In the end consumers have m numbers and then they write the results in results.txt file.
In this file every consumer should write all m numbers, it's process id and it's running average time. Running average time is the average time that current cosnumer waits to receive all the numbers.

## How It Works
There are 3 semaphores: empty,full,mutex and at the beginning empty is 0, full is 0 and mutex is 1.
Empty and full range: [0,n]
* Producer: <br />
 Writes in the buffer one number and current time stamp per loop. At the end of every loop ups full and empty with the value of n.
In this way consumers can read the new content. Also feeder is blocked until empty has the value of 0. In this way feeder will write his new
content only when all the consumers have read the current content.

* Consumers: <br />
Every consumer has a loop that reads from buffer. At the beginning consumer down the full sem, reads from buffer, down empty sem and then waits until full sem is equal with 0. In this way every consumer reads only once the current content and then is blocked. Also the last consumer will down the empty semaphore. This
semaphore has value 1 and now after that the value 0. That meanens that the producer will unblocked and write the new content. Finally in the last loop consumer writes in 
results.txt. Every time only one consumer can write in this file. I use mutex semaphore to achieve this. <br />
Note: This algorithm is quite optimal as the number of semaphores are quite small.

## Compilation/Run
1. make
2. ./test

## Author
* Petropoulakis Panagiotis petropoulakispanagiotis@gmail.com
