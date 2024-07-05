# define base image
FROM ubuntu:22.04

# define environment variables
ENV DIR_DEV_TOOLS "/development_tools"

# upgrade installed Linux packages
RUN apt update && apt upgrade -y

# install useful Linux packages
RUN apt install -y build-essential \
                   clang-format \
                   clang-tidy \
                   cmake \
                   cppcheck \
                   doxygen \
                   gdb \
                   git \
                   graphviz \
                   python3-pip \
                   software-properties-common

# add repository
RUN add-apt-repository ppa:ubuntu-toolchain-r/test -y

# update Linux package repositories
RUN apt update && apt upgrade -y

# install Clang
RUN apt install -y clang-11 \
                   clang-12 \
                   clang-13 \
                   clang-14 \
                   clang-15

# install GCC
RUN apt install -y g++-9 \
                   gcc-9 \
                   g++-10 \
                   gcc-10 \
                   g++-11 \
                   gcc-11 \
                   g++-12 \
                   gcc-12 \
                   g++-13 \
                   gcc-13

# install useful Python packages
RUN python3 -m pip install coverxygen \
                           flake8 \
                           flake8-bugbear \
                           flake8-builtins \
                           flake8-comprehensions \
                           flake8-docstrings \
                           flake8-import-order \
                           flake8-quotes \
                           flake8-variables-names \
                           gcovr \
                           gitpython \
                           metrixpp

# install development tools
RUN mkdir ${DIR_DEV_TOOLS}

RUN cd ${DIR_DEV_TOOLS} && \
    git clone --recursive https://github.com/opencv/opencv.git && \
    git clone --recursive https://github.com/opencv/opencv_contrib.git && \
    cd ${DIR_DEV_TOOLS}/opencv/ && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local/ -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules/ -D OPENCV_ENABLE_NONFREE=ON -D BUILD_opencv_python2=OFF -D BUILD_opencv_python3=OFF -D BUILD_EXAMPLES=OFF -D BUILD_TESTS=OFF -D BUILD_PERF_TESTS=OFF -B ./build/ -S ./ && \
    cmake --build ./build/ -t install -j8

RUN cd ${DIR_DEV_TOOLS} && \
    git clone --recursive https://github.com/google/googletest.git && \
    cd ${DIR_DEV_TOOLS}/googletest/ && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local/ -B ./build/ -S ./ && \
    cmake --build ./build/ -t install -j8

RUN cd ${DIR_DEV_TOOLS} && \
    git clone --recursive https://gitlab.com/libeigen/eigen.git && \
    cd ${DIR_DEV_TOOLS}/eigen/ && \
    cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local/ -B ./build/ -S ./ && \
    cmake --build ./build/ -t install -j8

RUN cd ${DIR_DEV_TOOLS} && \
    git clone --recursive https://github.com/boostorg/boost.git && \
    cd ${DIR_DEV_TOOLS}/boost/ && \
    ./bootstrap.sh --prefix=/usr/local/ && \
    ./b2 -j8 link=static install

RUN rm -rf ${DIR_DEV_TOOLS}

# create user
RUN useradd -u 130 -s /bin/bash docker
USER docker
