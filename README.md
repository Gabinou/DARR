# DARR (Dynamic Arrays) 

Dynamic arrays for C99. A darr is a simple array with two additional elements: allocated length and number of active element, saved at positions -2 and -1 respectively. 

See ```darr.h``` for tutorial, all useful macros are listed.

Originally created for use in a game I am developping using C99: [Codename Firesaga](https://gitlab.com/Gabinou/firesagamaker). Title pending. 

## Installation
Add ```darr.h``` to your source code.

## Features
- Compatible: compiles with ```tcc```, ```gcc```, ```clang``` 
- Single file.
- Simple: a darr is an array.
- Short: < 100 lines
- Included in [nmath](https://gitlab.com/Gabinou/noursmath)

## Motivation
Make a very simple dynamic array. 
Be type agnostic.
C99.
Compileable with ```tcc```.

## Credits
Copyright (c) 2021 Average Bear Games, Made by Gabriel Taillon
