# Deterministic Fast Parsing (DFP)

## Basic information and technical example

Deterministic fast parsing is derivated from deterministic finite automaton 

DFP work very simply, is singlecore process where input is string of big length (or stream of data), parser will go char by char and determine if state is correct or should be skipped to next potentional substring.

If all chars satisfy all states, subchar is returned (in few cases like ipv4 can be returned int representation of ip address).

For example DFP/ipv4:

```Hello 127.0.0.1 IP```

![ipv4](./doc/ipv4.png)

## Installation

```bash
$ git clone https://github.com/lukasbalazik123/dfp.git
$ cd dfp
$ make
```

### Tests

Testing machine stats:

```bash
Processor Name: Quad-Core Intel Core i7
Processor Speed: 2,8 GHz
Number of Processors: 1
```
Now run benchmark:

```bash
$ ./build/benchmark_with_vectors log_examples/suricata.log
Benchmark with vectors parsing takes: 0.021117
```

when we get size of logfile we can calculate per second speed of parsing:

```bash
$ ls -la log_examples/suricata.log
-rw-r--r--  1 regusr  staff  26214400 Jul 21 09:19 log_examples/suricata.log
$ echo "1/0.021117*26214400" | bc
1232076800
```

And 1232076800 bytes is **9.18** Gb per second on singlecore parser

## Usage

TODO

