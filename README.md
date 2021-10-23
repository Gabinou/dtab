# DTAB (Dynamic Table) 

Dynamic hash table for C99. 

A ```dtab``` is a ```struct``` that contains two arrays: ```keys``` and ```values```.
Both have ```len``` allocated length and ```num``` active elements.
```dtab``` also contains the value type's ```bytesize``` to move bytes around.

## Installation
Add ```dtab.h``` and ```dtab.c``` to your source code.

## Tutorial
Initiate a ```dtab```:
```c
struct Position {
    uint32_t x;
    uint32_t y;
};
struct dtab * dtab_test = DTAB_INIT(dtab_test, struct Position);
```
Allocs memory for the ```dtab```, ```keys``` and ```values```. Sets bytesize to the input type. Initial  allocated length is ```DTAB_LEN_INIT```.

Add to a variable ```dtab``` with a string key (H for hash, S for stringify):
```c
struct Position temp_pos = {.x = 1, .y = 2};
DTAB_ADDH(dtab_test, &temp_pos, "Test1");
DTAB_ADDSH(dtab_test, &temp_pos, Test1);
```

Add to a variable ```dtab``` with a positive integer key:
```c
struct Position temp_pos = {.x = 2, .y = 4};
int key = 1;
DTAB_ADD(dtab_test, &temp_pos, key);
```

If the key already exists, the value is updated. ```keys[0]``` and ```values[0]``` are reserved for ```NULL```.

Delete a ```dtab```:
```c
DTAB_DEL(dtab_test, "Test1");
DTAB_DELSCRAMBLE(dtab_test, "Test2");
```
```DTAB_DELSCRAMBLE``` might be faster because it does not copy all elements over, just the top one to the deleted element.

Free a ```dtab```:
```c
DTAB_FREE(dtab_test);
```
Frees ```dtab->keys``` and ```dtab->values```, then the ```dtab``` itself. There is no magic.

## Features
- Compatible: compiles with ```tcc```, ```gcc```, ```clang``` 
- Simple: a ```dtab``` is a struct, ```keys``` and ```values``` are arrays.
- Short: < 200 lines
- Included in [nmath](https://gitlab.com/Gabinou/noursmath)

## Motivation
Make a very simple hash table. 
Be type agnostic.
C99.
Compileable with ```tcc```.

## Credits
Copyright (c) 2021 Average Bear Games, Made by Gabriel Taillon
