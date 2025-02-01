## Benchmarks

* [ ] HTTP Requests
* [ ] HTTP + schema validation


## Tools

- Check number of available core in your machine `nproc`

## Granian (RSGI)

- _workers_: processes holding a dedicated pythno interpreter
- _threads_: rust thread that will perform network I/O
- _blocking threads_: number Rust threads per worker. Mail role - to deal with blocking i/o, but synchronous protocols like wsgi.

## Robyn

## References

1. [granian - #Processes and Threads / github.com](https://github.com/emmett-framework/granian?tab=readme-ov-file#processes-and-threads)
2. [Types of Load Testing / grafana.com](https://grafana.com/load-testing/types-of-load-testing/)
