# DTAB (Dynamic Table) 

Dynamic hash table for C99. 

A ```dtab``` is a ```struct``` that contains two arrays: ```keys``` and ```values```.
Both have ```len``` allocated length and ```num``` active elements.
```dtab``` also contains the value type's ```bytesize``` to move bytes around.


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
