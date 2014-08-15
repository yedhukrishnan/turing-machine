Turing Machine
==============

A turing machine simulator that can accept a string and process it according to a given set of transitions.

### Usage

You can invoke the program in any of these three methods:

1. turingmachine
1. turingmachine <input file>
1. turingmachine <input file> <input string>
 
Here *turingmachine* is the program name.

#### Input Format

`<current state> <input symbol> <new symbol> <movement> <new state>`

* A single transition should occupy a single line
* input symbol, new symbol and movement are single characters.
* <current state> and <new state> can be any combination of characters within a limit of 5
* First <current state> will be considered as your initial state
* Use '_' for blank, '#' for halting state
* Use '$' as current state to stop.
