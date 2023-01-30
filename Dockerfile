FROM ubuntu:20.04 AS builder
ARG USERNAME=mvisor
ARG UID=1000
ARG GID=1000
RUN groupadd -g $GID -o $USERNAME
RUN useradd -m -u $UID -g $GID -o -s /bin/bash $USERNAME

# Dependencies for elf generation
RUN apt-get -yqq update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -o APT::Immediate-Configure=0 -yqq \
    cmake gcc-arm-none-eabi jq

# Twilio CLI for bundle generation via debian package:
RUN apt-get -yqq update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -o APT::Immediate-Configure=0 -yqq \
    wget gnupg \
    && wget -qO- https://twilio-cli-prod.s3.amazonaws.com/twilio_pub.asc | apt-key add - \
    && touch /etc/apt/sources.list.d/twilio.list \
    && echo 'deb https://twilio-cli-prod.s3.amazonaws.com/apt/ /' | tee /etc/apt/sources.list.d/twilio.list \
    && apt update \
    && apt install -y twilio

WORKDIR /home/${USERNAME}/

USER $USERNAME

RUN twilio update && twilio plugins:install "@twilio/plugin-microvisor"

ENTRYPOINT ./project/docker-entrypoint.sh
