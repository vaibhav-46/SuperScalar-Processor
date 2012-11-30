SuperScalar-Processor
=====================

A fully equipped Super Scalar Processor for the MIPS architecture. At the end of the project , it will include the following features

    - Implementation of almost all MIPS command functionalities.
    - A Centralized reservation station
    - Out-of-order Execution
    - Re-order buffer
    - Register renaming
    - Multi-latency functional units with Pipelining

Points Not taken care of :

1. Floating point operations
2. Mul with no destination specified
3. Jalr and Jr .. i.e jump instructions of R type are not considered. It is assumed that all R type instructions are just computative
4. In case of a branch instruction, instruction fetch is stalled till the next branch address is found.
