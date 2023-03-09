FROM ubuntu

RUN apt-get update 
RUN apt-get upgrade -y
RUN apt-get install -y nasm
RUN apt-get install -y binutils-x86-64-linux-gnu
RUN apt-get install -y gcc-x86-64-linux-gnu
RUN apt-get install -y make
RUN apt-get install -y xorriso
RUN apt-get install -y curl
RUN apt-get install -y git
RUN apt-get install -y p7zip-full

VOLUME /root/env
WORKDIR /root/env
