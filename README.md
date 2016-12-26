A lightweight financial maths library based on core components from [QuantLib](https://github.com/lballabio/QuantLib)

## Pre-requisities
### Build
* A recent version of [boost](http://www.boost.org)
* The easisest way to install boost is by using the repository manager (or equivalent) for your OS:
  * Ubuntu/Debian: sudo apt-get install libboost-all-dev
  * CentOs/RedHat: sudo yum install boost-devel
  * Mac OS X: sudo port install boost ([using MacPorts](https://www.macports.org/))

### Document Generation
* In order to generate documentation from doxygen, the following tools installed are required:
  * [doxygen](www.doxygen.org)
  * [graphviz](http://www.graphviz.org)
* The easisest way to get these tools installed is by using the repository manager (or equivalent) for your OS:
  * Ubuntu/Debian: sudo apt-get install doxygen graphviz
  * CentOS/RedHat: sudo yum install doxygen graphviz
  * Mac OS X: sudo port install doxygen graphviz  ([using MacPorts](https://www.macports.org/))
* If doxygen and graphviz are installed, documentation will be generated during the invocation of make and the generated files can be found under docs/html, for example.

## Installation
* Run ./autogen.sh in order to generate the configure script.
* Run ./configure --help to see available options
* Example:
 * ./autogen.sh
 * ./configure
 * make
 * make check (run tests)

## Development
* Developed primarily using g++ (requires a compiler that supports c++11).
* For unit tests, I am using the excellent [Catch](https://github.com/philsquared/Catch) library; the single header can be found under the test subdirectory. 

