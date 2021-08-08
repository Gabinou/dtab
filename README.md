# DTAB (Dynamic Table) 

Dynamic hash table for C99. 

A ```dtab``` is a ```struct``` that contains two arrays: ```keys``` and ```values```.
Both have ```len``` allocated length and ```num``` active elements.
```dtab``` also contains the value type's ```bytesize``` to move bytes around.

## Tutorial

Initiate a ```dtab```:
```c
struct Position {
    uint32_t x;
    uint32_t y;
};
struct dtab * dtab_test = DTAB_INIT(dtab_test2, struct Position);
```
Allocs memory for the ```dtab```, ```keys``` and ```values```. Sets bytesize to the input type. Initial  allocated length is ```DTAB_LEN_INIT```.

Add to a variable ```dtab```:
```c
struct Position temp_pos = {.x = 1, .y = 2};
DTAB_ADD(dtab_test, temp_pos, "Test1");
DTAB_ADDP(dtab_test, &temp_pos, "Test2");
```
If the key already exists, the value is updated. ```keys[0]``` and ```values[0]``` are reserved for ```NULL```.

Delete a ```dtab```:
```c
DTAB_DEL(dtab_test, "Test1");
DTAB_DELSCRAMBLE(dtab_test, "Test2");
```
Free a ```dtab```:
```c
DTAB_FREE(dtab_test);
```
Frees ```dtab->keys``` and ```dtab->values```, then the ```dtab``` itself. There is no magic.

## Installation
Add ```dtab.h``` and ```dtab.c``` to your source code.

## Features
- Compatible: compiles with ```tcc```, ```gcc```, ```clang``` 
- Single file.
- Simple: a darr is an array.
- Short: < 100 lines

## Motivation
Make a very simple hash table. 
Be type agnostic.
C99.
Compileable with ```tcc```.

## Credits
Copyright (c) 2021 Average Bear Games, Made by Gabriel Taillon
