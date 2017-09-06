# ArielsSequitur
Implementation of the sequitur algorithm following the Craignm Ideas (C++). The hash table's implementation was copied from the Craig's original implementation available at: [https://github.com/craignm/sequitur](https://github.com/craignm/sequitur)

At running this implementation prints the output grammar and some stats.

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
```
./Sequitur
```
   - From file
```
./Sequitur -f <filename>
```

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
