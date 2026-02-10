# Build-recorder

The purpose of this project is
to fully record the interactions
between assets (files and tools)
when a software artifact is being built (compiled).

## Usage
**build-recorder** [-o outfile] command
* outfile: The output file, by default "build-recorder.out".
* command: The original build command with all its arguments.
    * e.g. cc -o hello helloworld.c 

## Description
**build-recorder** is a command line tool for linux 5.3+ that records
information about build processes. It achieves this by running transparently
in the background while the build process is running, tracing it
and extracting all relevant information, which it then stores in the output
file in RDF Turtle format.

A complete schema for the generated RDF can be found in docs/output.md.

**build-recorder** works regardless of the programming language, build system
or configuration used. In fact there is no limitation as to what the supplied
command should be. If it runs, **build-recorder** can trace it.

## Installation

### Pre-built packages (recommended)

Download the latest release from the [releases page](https://github.com/ohappykust/build-recorder/releases/latest).

#### Debian/Ubuntu (DEB)
```bash
# Download the .deb package, then install with automatic dependency resolution:
sudo apt install ./build-recorder_1.0-1_amd64.deb
```

#### Fedora/RHEL/Rocky Linux (RPM)
```bash
# Download the .rpm package, then install with automatic dependency resolution:
sudo dnf install build-recorder-1.0-1.fc43.x86_64.rpm
```

**Note:** Using `apt install` or `dnf install` (not `dpkg -i` or `rpm -i`) ensures that all required dependencies (OpenSSL, glibc) are automatically installed.

### Static binary (no dependencies)

For systems where you cannot install packages or need a standalone binary:

```bash
# Download the static binary
wget https://github.com/ohappykust/build-recorder/releases/latest/download/build-recorder-linux-x86_64-static

# Make it executable
chmod +x build-recorder-linux-x86_64-static

# Run it
./build-recorder-linux-x86_64-static --help
```

The static binary includes all dependencies and works on any Linux 5.3+ system without requiring additional libraries.

## Build
To build it you are going to need the following tools:
* A C compiler
* make

As well as the following libraries:
* libcrypto
### Build from github repository
In order to build from the github repository directly, you are also going
to need
* autoconf
* automake

On the project's top-level directory, run:
```
autoreconf -i
./configure
make
```

### Build from release tarball
Assuming you've downloaded the tarball:
```
tar -xf <build-recorder-release>.tar.gz
cd <build-recorder-release>
./configure
make
```

## License

The code is licensed under
GNU Lesser General Public License v2.1 or later
(`LGPL-2.1-or-later`).

