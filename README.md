[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
# Producer-Consumer problem
<img src="https://cdn-images-1.medium.com/max/800/1*38NMAj0WTa_LD3ojoWsytQ.png"> <br /> 
In this program feeder writes in a buffer. Feeder has m elements(random int) to write. Buffer has 2 contents. Current number and a time stamp.
Time stamp is the moment that the feeder writes current number. We have n consumers. Every time all consumers should read the current number 
and then the reeder should be informed to change current number. In the end consumers have m numbers and write some results in results.txt file.
In this file every consumer should write all n numbers his process id and his running average time. Running average time is the average time that 
current cosnumer waits to receive all the numbers.

## How It Works
There are 3 semaphores: empty,full,mutex and at the beginning empty is 0, full is 0 and mutex is 1.
Empty and full range: [0,n]
Feeder:
* In a loop he writes in buffer one number and current time stamp per loop. At the end of every loop ups full and empty with the value of n.
In this way consumers can read the new content. Also feeder is blocked until empty has the value of 0. In this way feeder will write his new
content only if all consumers have read current content.

Consumers:
* Every consumer has a loop that reads from buffer. At the beginning consumer down full, reads from buffer, down empty and then waits until full
is 0. In this way every consumer reads only once the current content and then is blocked. Also the last consumer will down the empty semaphore. This
semaphore has value 1 and now has value 0. That meanw feeder should write new content and is realesed. Finally in the last loop consumer writes in 
results.txt. Every time only one consumer can write in this file. I use mutex semaphore to achieve this. 

## Compilation/Run
1. make: compile files
2. ./test

## Helpful Links: 
1. http://matlabtricks.com/post-5/3x3-convolution-kernels-with-online-demo
2. http://setosa.io/ev/image-kernels/
3. https://docs.gimp.org/en/plug-in-convmatrix.html

## Author
* Petropoulakis Panagiotis petropoulakispanagiotis@gmail.com
