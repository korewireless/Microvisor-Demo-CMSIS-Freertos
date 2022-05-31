FROM ubuntu:20.04 AS builder
ARG USERNAME=mvisor
ARG UID=1000
ARG GID=1000
RUN groupadd -g $GID -o $USERNAME
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $USERNAME

# Dependencies for elf generation
RUN apt-get -yqq update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -o APT::Immediate-Configure=0 -yqq \
    cmake gcc-arm-none-eabi
# Dependencies for bundler-py:
RUN apt-get -yqq update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -o APT::Immediate-Configure=0 -yqq \
    python3 python3-pip protobuf-compiler
RUN pip3 install cryptography protobuf~=3.0
WORKDIR /home

USER $USERNAME
ENTRYPOINT /home/docker-entrypoint.sh
