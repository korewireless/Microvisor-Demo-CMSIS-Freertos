FROM ubuntu:20.04 AS builder
ARG USERNAME=mvisor
ARG UID=1000
ARG GID=1000
RUN groupadd -g $GID -o $USERNAME
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $USERNAME

# Dependencies for elf generation
RUN apt-get update -yqq && apt-get install -yqq apt-utils
RUN DEBIAN_FRONTEND=noninteractive apt-get install -o APT::Immediate-Configure=0 -yqq \
    cmake gcc-arm-none-eabi jq curl ca-certificates gnupg

# Twilio CLI for bundle generation via npm
# as a binary debian package is not yet available for Apple Silicon
RUN mkdir -p /etc/apt/keyrings
RUN curl -fsSL https://deb.nodesource.com/gpgkey/nodesource-repo.gpg.key | gpg --dearmor -o /etc/apt/keyrings/nodesource.gpg
RUN echo "deb [signed-by=/etc/apt/keyrings/nodesource.gpg] https://deb.nodesource.com/node_20.x nodistro main" | tee /etc/apt/sources.list.d/nodesource.list
RUN apt-get update -yqq && DEBIAN_FRONTEND=noninteractive apt-get install -yqq nodejs
RUN npm install -g twilio-cli

WORKDIR /home/${USERNAME}/

USER $USERNAME

RUN twilio plugins:install "@twilio/plugin-microvisor"

ENTRYPOINT ["./project/docker-entrypoint.sh"]
