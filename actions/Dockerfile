FROM ubuntu:latest

# setup zoneinfo
RUN ln -snf /usr/share/zoneinfo/$INPUT_ZONEINFO /etc/localtime && echo $INPUT_ZONEINFO > /etc/timezone

RUN apt update
RUN apt install -y build-essential libcurl4-gnutls-dev libxml2-dev libssl-dev
RUN apt install -y r-base

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

# Executes `entrypoint.sh` when the Docker container starts up
ENTRYPOINT ["/entrypoint.sh"]