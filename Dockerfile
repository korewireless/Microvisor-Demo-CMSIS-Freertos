FROM ubuntu:22.04 AS builder
ARG USERNAME=mvisor
ARG UID=1000
ARG GID=1000
RUN groupadd -g ${GID} -o ${USERNAME}
RUN useradd -m -u ${UID} -g ${GID} -o -s /bin/bash ${USERNAME}

# Dependencies for elf generation
RUN apt-get update -yqq \
  && DEBIAN_FRONTEND=noninteractive apt-get install -o APT::Immediate-Configure=0 -yqq \
  cmake gcc-arm-none-eabi jq curl ca-certificates gnupg && apt-get clean

# Twilio CLI for bundle generation via npm
# as a binary debian package is not yet available for Apple Silicon
RUN curl -sL https://deb.nodesource.com/setup_20.x | bash
RUN apt-get update -yqq && DEBIAN_FRONTEND=noninteractive apt-get install -yqq nodejs
RUN npm install -g twilio-cli

WORKDIR /home/${USERNAME}/
USER $USERNAME

RUN twilio plugins:install "@twilio/plugin-microvisor"

ENTRYPOINT ["./project/docker-entrypoint.sh"]
