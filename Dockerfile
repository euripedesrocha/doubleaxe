# Based on
# https://hub.docker.com/r/kylemanna/ci-embedded/~/dockerfile/
FROM ubuntu:16.04
RUN \
    echo 'deb http://ppa.launchpad.net/team-gcc-arm-embedded/ppa/ubuntu xenial main' > /etc/apt/sources.list.d/gcc-arm-embedded.list && \
    apt-key adv --keyserver keyserver.ubuntu.com --recv-keys D1FAA6ECF64D33B0 && \
    apt-get update && \
    apt-get install -y \
                        build-essential \
                        gcc \
                        python3-pip \
                        gcc-arm-embedded \
                   && \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
RUN pip3 install ninja meson
WORKDIR /development


