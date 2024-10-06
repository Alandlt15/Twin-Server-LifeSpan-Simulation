# 3360HW2-Q5
This repo is for HW2 in my Computing System Fundamentals (3360) course with Dr. Mina Guirguis. Fall 2024.

Description: A computing system is composed of two servers that are mirrors of each other (for redundancy, so if one
fails, it can be restored from the other). Assume that each server has an MTBF of 500 hours that follows an
exponential distribution. Furthermore assume that when a server fails, it takes exactly 10 hours to restore
the data from the mirror.

Function a:
Write a program that generates synthetic data showing the failure and restoration times for each server
over 20 years.

Function b:
Find out how long it would take until the whole computing system fails (that is when both servers
happen to fail within the 10 hours restoration time). You would need to simulate this multiple times with
different seeds and compute the average.
