FROM python:3.12-slim-bookworm AS builder

## Install uv
COPY --from=ghcr.io/astral-sh/uv:latest /uv /uvx /bin/
WORKDIR /workspace/app/

RUN apt-get update && apt-get upgrade -y && apt-get install --no-install-recommends -y \
  build-essential \
  python3-dev \
  git

## Install Project
COPY . /workspace/app/
# COPY pyproject.toml uv.lock ./
# COPY ./src/aemmett ./
# COPY ./src/shared ./

ENV UV_COMPILE_BYTECODE=1
ENV UV_LINK_MODE=copy
ENV UV_NO_CACHE=1
ENV UV_COMPILE_BYTECODE=1
ENV UV_SYSTEM_PYTHON=1
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1
ENV PYTHONFAULTHANDLER=1
ENV PYTHONHASHSEED=random

RUN uv venv && \
  export PATH="/workspace/app/.venv/bin:$PATH" && \
  uv sync --frozen && \
  python -m compileall /workspace/app/


FROM python:3.12-slim-bookworm

WORKDIR /workspace/app/
RUN groupadd urunners && useradd --home-dir /workspace/app -g urunners urunner && chown -R urunner:urunners /workspace/app
RUN install -d -o urunner -g urunners /workspace/app/data

COPY --from=builder --chown=user:user /workspace/app/.venv /workspace/app/.venv
COPY --chown=urunner:urunners src makefile pyproject.toml uv.lock .python-version /workspace/app/

USER urunner

ENV PATH="/workspace/app/.venv/bin:$PATH"
ENV PYTHONPATH=/workspace/app

## Run Application
EXPOSE 8000

CMD ["python", "-m", "arobyn", "--host", "0.0.0.0", "--port", "8000"]
