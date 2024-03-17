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
                   plantuml \
                   python3-dev \
                   python3-pip \
                   python3-setuptools

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
                           gitpython

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
