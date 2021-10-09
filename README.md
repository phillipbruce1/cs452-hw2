# Homework 2 - The Mole, The Programmer, and His Mental Health

##### CS 452 - Prof. Buffenbarger

###### Phillip Bruce

## Purpose

This program implements an autonomous game of _Whack-a-Mole_ where the computer acts as both the player and the game. This is because the computer is lonely and has no one to play games with.

## Function

The moles are represented as green circles. Each mole then turns red (i.e. is _whacked_). The variable `n` determines how many moles are created, and subsequently whacked. I have set the default value to `100` moles. The game ends after all moles have been _whacked_.

## Challenges

I started this project with the intent to rid this program of all pesky moles. I set to work with purpose and drive, working hard to squash all bugs and moles. As I worked though, mole after mole appeared. Their numbers grew exponentially, until I became overwhelmed, cowering in fear under my desk to hide from the moles as they took over my computer. My monitor was a horrifying sight, crawling with moles and bugs galore.

I grew more and more anxious by the second, worrying that I may never rid myself of these pests. I lived in fear for several days. I had to leave the safety of my desk eventually, venturing out for necessities such as food and water. The moles knew that, waiting until the right moment to strike me down and claim my computer as theirs forever. 

Fear not though, dear reader, as I have evidently lived on to tell this tale.

One lonely afternoon, I developed the courage to fight back. These moles have no right to my computer - it's **mine**! I jumped up, grabbed my keyboard, and got to work. I worked hard, eliminating mole after mole and squashing bug after bug. At the end of it all, I sat back and sighed in relief, proud of my work. No more moles or bugs remained - I was free!

... or so I thought. Unfortunately, some live on in the form of memory leaks. They can be seen in the included screenshot results after running Valgrind. I was unable to rid myself of these bugs, but I think that getting the program to at least run is still an achievement.

Other than that, I definitely struggled with threads and things and stuff at first as I worked to understand mutexes, locks, and condition variables. By the end of it all, I feel that I have learned from this assignment though.