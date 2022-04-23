## Example usage
```
$ ./main fib.jm
$ ./main subroutine.jm
```

## Build
```
$ make clean && make
```

## Extras
- Stack
- Subroutines
- More instructions
  - mov regA regB
    - regA = regB
  - rload regA regB
    - loads regA with value read from memory at address held in regB
  - rstore regA regB
    - stores the value in regA into memory at address held in regB
