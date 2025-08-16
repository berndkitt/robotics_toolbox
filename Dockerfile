# define base image
FROM ubuntu:24.04

# define additional build arguments
ARG USER_ID

# define variables
ARG UBUNTU_VERSION_CODENAME=noble
ARG CLANG_VERSION=21
ARG DIR_DEV_TOOLS="/development_tools"
ARG GCC_VERSION=14
ARG PYTHON_VERSION=3.10
ARG PYTHON_VIRTUAL_ENV=/opt/venv

# update installed Linux packages
RUN apt update && apt upgrade -y

# install basic Linux packages
RUN apt install -y build-essential \
                   cmake \
                   cppcheck \
                   doxygen \
                   gdb \
                   git \
                   graphviz \
                   plantuml \
                   software-properties-common \
                   wget

# add repositories (Python, GCC, LLVM)
RUN add-apt-repository ppa:deadsnakes/ppa -y
RUN add-apt-repository ppa:ubuntu-toolchain-r/test
RUN add-apt-repository deb http://apt.llvm.org/${UBUNTU_VERSION_CODENAME}/ llvm-toolchain-${UBUNTU_VERSION_CODENAME}-${CLANG_VERSION} main

# add signing keys (LLVM)
RUN wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc

# install additional Linux packages
RUN apt update && apt install -y clang-${CLANG_VERSION} \
                                 clang-format-${CLANG_VERSION} \
                                 clang-tidy-${CLANG_VERSION} \
                                 g++-${GCC_VERSION} \
                                 gcc-${GCC_VERSION} \
                                 python${PYTHON_VERSION}-full

# set default versions
RUN ln -sf /usr/bin/clang++-${CLANG_VERSION} /usr/bin/clang++
RUN ln -sf /usr/bin/clang-${CLANG_VERSION} /usr/bin/clang
RUN ln -sf /usr/bin/clang-cl-${CLANG_VERSION} /usr/bin/clang-cl
RUN ln -sf /usr/bin/clang-cpp-${CLANG_VERSION} /usr/bin/clang-cpp
RUN ln -sf /usr/bin/clang-format-${CLANG_VERSION} /usr/bin/clang-format
RUN ln -sf /usr/bin/clang-tidy-${CLANG_VERSION} /usr/bin/clang-tidy
RUN ln -sf /usr/bin/g++-${GCC_VERSION} /usr/bin/g++
RUN ln -sf /usr/bin/gcc-${GCC_VERSION} /usr/bin/gcc
RUN ln -sf /usr/bin/python${PYTHON_VERSION} /usr/bin/python3

# create Python virtual environment
RUN python${PYTHON_VERSION} -m venv ${PYTHON_VIRTUAL_ENV}
ENV PATH="${PYTHON_VIRTUAL_ENV}/bin:$PATH"

# update Python pip
RUN python${PYTHON_VERSION} -m pip install --upgrade pip

# install additional Python packages
RUN python${PYTHON_VERSION} -m pip install coverxygen \
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

# cleanup
RUN rm -rf ${DIR_DEV_TOOLS}

# create user
RUN useradd -u "${USER_ID}" -s /bin/bash jenkins
