# periodic_execution_test

Sample code for periodic execution on linux．

To reduce the variability of periodic execution, a kernel patched with RT_PREEMPT or a low-latency kernel is required.


## Usage

1. build sample

```
$ cmake .
$ make
```

2. run sample as root

```
$ sudo ./periodic_test
```
