# rtos-2

Build and run with:
```
module load Boost/1.71.0-gompi-2019b
module load OpenMPI/3.1.4-GCC-8.3.0
make
mpirun -np <number of processors> mastermind <number of spaces> <number of colors>
```

Tests are run using [Catch](https://github.com/catchorg/Catch2).
