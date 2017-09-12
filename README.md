# ArielsSequitur
Implementation of the *sequitur* algorithm following the Craignm Ideas (C++). The hash table's implementation was copied from the Craig's original implementation available at: [https://github.com/craignm/sequitur](https://github.com/craignm/sequitur)

The *sequitur* algorithm is a grammar based compression algorithm meaning that it generates a context-free grammar which unique derived string is the comprimed text.

At running this implementation recieves its text input from stdin or file and prints the output grammar and some stats.

## To compile
- On the repo directory
```
$ make
```

## To run tests
- compile
- On the repo directory
```
./TestSequitur
```

## To run sequitur
- compile
- run tests
- On the repo directory
  - From stdin
      `./Sequitur`
  - From file
      `./Sequitur -f <filename>`

## Example
```
...$cat data 
abcdbcabcd...$ ./Sequitur -f data

Sequitur succeeded

Grammar

S0->S3 S1 S3 
S3->a S1 d 
S1->b c 
Original chars: 10
Number of rules: 3
Grammar Size: 8
Compression ratio: 90.00%
```
The derivation of the grammar output from the example is S0 -> S3 S1 S3 -> a S1 d S1 a S1 d -> a b c d b c a b c d
