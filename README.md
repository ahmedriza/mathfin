A lightweight financial maths library based on core components from [QuantLib](https://github.com/lballabio/QuantLib)

Pre-requisities
---------------
* A recent version of [boost](http://www.boost.org)
* The easisest way to install boost is by using the repository manager (or equivalent) for your OS:
  * Ubuntu/Debian: sudo apt-get install libboost-all-dev
  * CentOs/RedHat: sudo yum install boost-devel
  * Mac OS X: sudo port install boost ([using MacPorts](https://www.macports.org/))

Installation
------------
* Run ./autogen.sh in order to generate the configure script.
* Run ./configure --help to see available options
* Example:
 * ./autogen.sh
 * ./configure
 * make
 * make check (run tests)

Development
-----------
* Developed primarily using g++ (requires a compiler that supports c++11).
* For unit tests, I am using the excellent [Catch](https://github.com/philsquared/Catch) library; the single header can be found under the test subdirectory. 
