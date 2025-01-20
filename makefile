.DEFAULT_GOAL := dev

dev: export GRANIAN_THREADS=2
dev: export	GRANIAN_WORKERS=2
dev: export GRANIAN_BLOCKING_THREADS=4
dev: export GRANIAN_INTERFACE=rsgi

.PHONY: dev
dev:
	uv run granian src.aemmett.rsgi:app

.PHONY: build-aemmett
build-aemmett:
	docker build -t aemmett -f containers/aemmett.dockerfile .

.PHONY: build-aemmett
build-arobyn:
	docker build -t arobyn -f containers/arobyn.dockerfile .


.PHONY: stage-aemmett
stage-aemmett:
	docker run --rm --cpus 2 --name aemmett-test -p 8000:8000 aemmett-test

.PHONY: stage
stage:
	granian aemmett.rsgi:app

