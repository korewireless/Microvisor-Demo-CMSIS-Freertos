FROM ubuntu:20.04 AS builder
ARG USERNAME=mvisor
ARG UID=1000
ARG GID=1000
RUN groupadd -g $GID -o $USERNAME
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $USERNAME

# Dependencies for elf generation
RUN apt -yqq update \
    && DEBIAN_FRONTEND=noninteractive apt install -o APT::Immediate-Configure=0 -yqq \
    cmake gcc-arm-none-eabi jq apt-utils

# Twilio CLI for bundle generation via npm: (a binary debian package is not yet available for Apple Silicon)
RUN apt -yqq update \
    && apt install -y curl \
    && curl -sL https://deb.nodesource.com/setup_19.x | bash - \
    && apt install -y nodejs \
    && npm install -g twilio-cli

WORKDIR /home/${USERNAME}/

USER $USERNAME

RUN twilio plugins:install "@twilio/plugin-microvisor"

ENTRYPOINT ["./project/docker-entrypoint.sh"]
