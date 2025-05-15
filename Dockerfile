FROM alt:p11

WORKDIR /app

RUN apt-get update && \
    apt-get install -y \
        git-core \
        gcc-c++ \
        gcc-c++-common \
        cmake \
        make \
        boost-asio-devel \
        boost-beast-devel \
        boost-devel-headers \
        libboost_url1.85.0 \
        libboost_json1.85.0 \
        libpq5-17 \
        libpq5-17-devel \
        postgresql17 \ 
        postgresql17-server

#RUN git clone -b devel https://github.com/DStener/loGMa-Finance-Server.git build

ADD . /app

RUN cmake -DCMAKE_BUILD_TYPE=Release . &&\
    cmake --build . -j $(nproc)

RUN groupadd -r logma && useradd -r -g logma logma
USER logma

WORKDIR /app/server