dev-aemmett: export GRANIAN_THREADS=4
dev-aemmett: export	GRANIAN_WORKERS=2
dev-aemmett: export GRANIAN_BLOCKING_THREADS=2
dev-aemmett: export GRANIAN_INTERFACE=rsgi

.PHONY: dev-aemmett
dev-aemmett:
	uv run granian src.aemmett.rsgi:app

.PHONY: dev-arobyn
dev-arobyn:
	uv run python -m arobyn

.PHONY: memray-aemmett
memray-aemmett:
	uv run memray run --live -m aemmett aemmett.rsgi:app

.PHONY: memray-arobyn
memray-arobyn:
	uv run memray run --live -m arobyn

.PHONY: build-docker-aemmett
build-docker-aemmett:
	docker build -t aemmett -f containers/aemmett.dockerfile .

.PHONY: build-docker-arobyn
build-docker-arobyn:
	docker build -t arobyn -f containers/arobyn.dockerfile .

.PHONY: docker-stage-aemmett
docker-stage-aemmett:
	docker run --rm --cpus 4 --name aemmett-test -p 8000:8000 aemmett

.PHONY: docker-stage-arobyn
docker-stage-arobyn:
	docker run --rm --cpus 4 --name arobyn-test -p 8000:8000 arobyn

.PHONY: stage-eammett
stage-eammett:
	granian aemmett.rsgi:app

.PHONY: benchmark
benchmark:
	ab -c 10 -n 100000 -g reports/raw-data.csv http://127.0.0.1:8000/api/orders 

.PHONY: loadtest
loadtest:
	k6 run loadtest.js

.PHONY: htserver
htserver-build:
	gcc ht/server.c -o api_server
