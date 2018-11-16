Overview
--------
Prun job serialization library.


Building
--------

Build requirements:

- cmake 2.6 (or higher)
- GCC 4.6 (or higher) or Clang
- boost 1.46 (or higher)
- libcouchbase-dev 

Building DEB::

> git clone https://github.com/zhka/prun-couchbase.git
> cd prun-couchbase
> git submodule update --init
> debuild -sa

Building RPMs::

> git clone https://github.com/zhka/prun-couchbase.git
> cd prun-couchbase
> git submodule update --init
> ./build-rpm.sh

Building::

> git clone https://github.com/zhka/prun-couchbase.git
> cd prun-couchbase
> git submodule update --init
> cd build
> cmake .. && make

Couchbase setup
---------------

1. Create new bucket.
2. Create user and grant permissions.
3. Create primary index:
> CREATE PRIMARY INDEX `#primary` ON `<bucket_name>`

Configuration
-------------

See example of config file in ./config/ directory

Links
-----

https://github.com/abudnik/prun

