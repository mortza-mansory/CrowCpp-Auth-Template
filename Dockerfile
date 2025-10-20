# ---------- Stage 1: Build ----------
FROM ubuntu:24.04 AS build

ENV DEBIAN_FRONTEND=noninteractive

# نصب ابزارهای build
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    wget \
    ca-certificates \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . /app

# ساخت برنامه
RUN mkdir -p build \
    && cd build \
    && cmake .. \
    && cmake --build . --config Release

# ---------- Stage 2: Runtime ----------
FROM ubuntu:24.04 AS runtime

ENV DEBIAN_FRONTEND=noninteractive

# نصب فقط چیزهای لازم برای اجرای برنامه
RUN apt-get update && apt-get install -y --no-install-recommends \
    libssl3 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build/crow_auth_server /app/crow_auth_server
COPY users.json /app/users.json

EXPOSE 8080
CMD ["./crow_auth_server"]
