FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
    && apt install -y --no-install-recommends \
    build-essential cmake vim openssl ca-certificates \
    unzip zip pkg-config libgl1-mesa-dev mesa-utils libgl1-mesa-glx \
    libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev

# Set the working directory to root (ie $HOME)
WORKDIR root

COPY . .

RUN cmake -B build && make -C build

RUN ./build/test/PathTracer_TEST

#RUN echo "export DISPLAY=localhost:0.0" >> ~/.bashrc

ENTRYPOINT ["./build/src/main/PathTracer_exe"]
