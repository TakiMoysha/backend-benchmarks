## Benchmarks

* [ ] HTTP Requests
* [ ] HTTP + schema validation

## Tools

В докере используется отедльная сеть для приложений. `docker network create backend-bench --driver bridge`

## Gateway Layer

## Server Layer

### Granian (RSGI)

- _workers_: processes holding a dedicated pythno interpreter
- _threads_: rust thread that will perform network I/O
- _blocking threads_: number Rust threads per worker. Mail role - to deal with blocking i/o, but synchronous protocols like wsgi.

### Robyn

## Persistance Layer

Слой хранения данных. И скрипты для генерации данных для них Сейчас в планах:

- [ ] Clickhouse
- [ ] Postgresql

### Postgresql

```shell
docker run -d --name postgresql \
 --network backend-bench \
 -v ~/linux-media/mockdata/postgres:/bitnami/postgresql \
 -e POSTGRES_PASSWORD=postgres \
 -e POSTGRES_USER=postgres \
 -e POSTGRES_DB=postgres \
 bitnami/postgresql:latest
```

### Clickhouse

```shell
docker run --name clickhouse \
 --network backend-bench \
 -v ~/linux-media/mockdata/clickhouse:/bitnami/clickhouse \
 -e CLICKHOUSE_ADMIN_PASSWORD=abc123 \
 -e CLICKHOUSE_ADMIN_USER=takimoysha \
bitnami/clickhouse:latest

```

## References

1. [granian - #Processes and Threads / github.com](https://github.com/emmett-framework/granian?tab=readme-ov-file#processes-and-threads)
2. [Types of Load Testing / grafana.com](https://grafana.com/load-testing/types-of-load-testing/)
