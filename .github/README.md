# Robotics Toolbox for C++

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

## Getting Started

### Prerequisites

The *Robotics Toolbox for C++* depends on the following external C++ tools:

- Boost (see [https://github.com/boostorg/boost](https://github.com/boostorg/boost))
- Eigen (see [https://eigen.tuxfamily.org/index.php?title=Main_Page](https://eigen.tuxfamily.org/index.php?title=Main_Page))
- GoogleTest (see [https://github.com/google/googletest](https://github.com/google/googletest))
- OpenCV (see [https://github.com/opencv/opencv](https://github.com/opencv/opencv))

Additionally, the following Python packages are required:

- Coverxygen (see [https://pypi.org/project/coverxygen/](https://pypi.org/project/coverxygen/))
- Flake8 (see [https://pypi.org/project/flake8/](https://pypi.org/project/flake8/))
- Gcovr (see [https://pypi.org/project/gcovr/](https://pypi.org/project/gcovr/))
- GitPython (see [https://pypi.org/project/GitPython/](https://pypi.org/project/GitPython/))
- Metrix++ (see [https://pypi.org/project/metrixpp/](https://pypi.org/project/metrixpp/))

In the following, it is assumed that the C++ tools and Python packages mentioned above have been installed already.

A Dockerfile based on Ubuntu 22.04 with all the prerequisites available is part of the repository (see [Docker](#docker) section). In case the development shall happen inside a Docker container, Docker also needs to be installed on the system (see [https://www.docker.com/](https://www.docker.com/)).

### Clone Repository

To get your own version of the Git repository, you can clone the repository to your own system. This can be done by running

```bash
git clone --recursive https://github.com/berndkitt/robotics_toolbox.git
```

in the terminal. Afterwards a subdirectory called `robotics_toolbox` will be available inside the directory the command was called.

### CMake

The *Robotics Toolbox for C++* uses CMake as build environment. In a first step, the build environment needs to be generated. This can be done by running

```bash
cmake -B ./build/ -S ./
```

in the terminal, while being in the main directory of the toolbox. This will create a directory called `build` which contains all the temporary build files.

Afterwards, the individual parts of the toolbox can be build. It is recommended to build all targets of the toolbox by running

```bash
cmake --build ./build/ -t all -j4
```

in the terminal. This will create a directory called `libs` which contains all the libraries of the toolbox as well as a directory called `bin` containing all the executables (i.e. unit tests, examples,...).

### Docker

In order to make use of the Docker container, the first step is to build the Docker image by running

```bash
docker build -t robotics_toolbox .
```

in the terminal.

After the Docker image has been built, a Docker container can by started by running

```bash
docker run -dit -v <absolute_path_on_host>:<absolute_path_in_container> --name robotics_toolbox -h ubuntu robotics_toolbox
```

in the terminal.

Using the command above, the local version of the repository is made available inside the Docker container. `absolute_path_on_host` needs to be replaced by the directory the repository was cloned into on the host machine (see [Clone Repository](#clone-repository) section), `absolute_path_in_container` needs to be replaced by the path the repository shall be available inside the container.

Example: `docker run -dit -v /development/robotics_toolbox/:/mnt/ --name robotics_toolbox -h ubuntu robotics_toolbox`

Changes made in the repository while working inside the container will also be available on the host machine.

## Versioning

The release numbers follow the **Semantic Versioning** scheme (see [https://semver.org/](https://semver.org/)). Hence, a version number has the following format:

*MAJOR*.*MINOR*.*PATCH*

The individual numbers are incremented as follows:

- *MAJOR*: Incremented when major changes were made (**not backwards compatible**). Whenever this number is incremented, *MINOR* and *PATCH* will be set to 0.
- *MINOR*: Incremented when new features were implemented (**backwards compatible**). Whenever this number is incremented, *PATCH* will be set to 0.
- *PATCH*: Incremented when small bug fixes were implemented (**backwards compatible**).

## License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <https://www.gnu.org/licenses/>.
