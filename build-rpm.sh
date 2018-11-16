#!/bin/bash

VERSION="0.1"

# Create source tarball
tar czf rpm/SOURCES/prun-couchbase-${VERSION}.tar.gz --exclude=./rpm/SOURCES/prun-couchbase-${VERSION}.tar.gz --transform "s,^,prun-couchbase-${VERSION}/," .

# Build
rpmbuild --define "_topdir $(pwd)/rpm" -ba ./rpm/SPECS/prun-couchbase.spec
