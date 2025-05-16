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
        postgresql17-server \
        node \
        npm

ADD . /app

RUN cmake -DCMAKE_BUILD_TYPE=Release . &&\
    cmake --build . -j $(nproc)

RUN git clone https://github.com/DStener/loGMa-Finance-Client.git &&\
    cd loGMa-Finance-Client &&\
    npm install &&\
    npm run build &&\
    yes | cp -rf dist/* ../root/

RUN groupadd -r logma && useradd -r -g logma logma
USER logma

WORKDIR /app/server