## Synopsis

Server Listner, is a software designed to run both on embedded devices
and PC and provide a way of communication via secure socket

## Motivation

on many embedded devices, both Linux based and Android based we need to control low level functions 

on the embedded board form a PC

this software allows exactlly that, the server installed on the embedded device and runs as a deamon, 

while the send software runs on the PC


## Installation

in order to run on a PC do the following: 

vi Makefile:

#CC=    $(CROSS_COMPILE_ANDROID)gcc

CC = gcc

save changes

make send

./server_daemon_send ip_address

in order to run on an embedded device do the following: 

vi Makefile:

CC=    $(CROSS_COMPILE_ANDROID)gcc

#CC = gcc

save changes

make server_daemon



# motor_embedded
