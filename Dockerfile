FROM debian:11

RUN apt-get update \
 && apt-get install --assume-yes --no-install-recommends --quiet \
    ca-certificates \
    cmake \
    git \
    g++ \
    make \
    libzip-dev \
 && apt-get clean all

# RUN ln -sf /usr/bin/clang /usr/bin/cc \
#   && ln -sf /usr/bin/clang++ /usr/bin/c++ \
#   && update-alternatives --install /usr/bin/cc cc /usr/bin/clang 10\
#   && update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 10\
#   && update-alternatives --auto cc \
#   && update-alternatives --auto c++ \
#   && update-alternatives --display cc \
#   && update-alternatives --display c++ \
#   && ls -l /usr/bin/cc /usr/bin/c++ \
#   && cc --version \
#   && c++ --version

WORKDIR /usr/local/src