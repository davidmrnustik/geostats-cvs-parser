FROM gcc:11.2.0
#FROM rikorose/gcc-cmake:latest

ENV DEBIAN_FRONTEND noninteractive
ENV APP_NAME=geostats_cvs_parser
ENV DIR_NAME_BUILD=cmake-build-release

RUN apt-get update && apt-get install -y cmake

EXPOSE 8080

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp


RUN mkdir ${DIR_NAME_BUILD} \
    && cd ${DIR_NAME_BUILD} \
    && ls /usr/local/include \
    && cmake ../ \
    && cmake --build . --target ${APP_NAME} --config Release

CMD ./$DIR_NAME_BUILD/$APP_NAME