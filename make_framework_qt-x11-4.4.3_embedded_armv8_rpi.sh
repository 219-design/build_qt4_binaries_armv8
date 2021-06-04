#!/bin/bash

#
# Copyright (c) 2021, 219 Design, LLC
# See LICENSE.txt
#
# https://www.219design.com
# Software | Electrical | Mechanical | Product Design
#

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

# Tested on Ubuntu 18.04 as of June 2021.

echo "Reading first argument. Directory into which to download the Qt framework."
WORK_DIR=$1
shift 1

echo "Reading second argument. Installation directory."
INSTALL_PREFIX_DIR=$1
shift 1

pushd ${WORK_DIR}/

if [ -d ${WORK_DIR}/tools/ ]; then
  echo "raspberrypi cross-compiler tools were already cloned. Will NOT clone again."
else
  git clone https://github.com/raspberrypi/tools
fi

pushd .
  cd tools
  git checkout fc0e73c1
  cd arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin
  ln -sf arm-linux-gnueabihf-g++ arm-linux-g++
  ln -sf arm-linux-gnueabihf-gcc arm-linux-gcc
popd

if [ -f ${WORK_DIR}/qt-embedded-linux-opensource-src-4.4.3.tar.gz ]; then
  echo "Qt sources were already downloaded. Will NOT download again."
else
  wget https://download.qt.io/archive/qt/4.4/qt-embedded-linux-opensource-src-4.4.3.tar.gz
fi

if [ -d ${WORK_DIR}/qt-embedded-linux-opensource-src-4.4.3/ ]; then
  echo "Qt sources were already extracted. Will NOT extract again."
else
  tar xvfz qt-embedded-linux-opensource-src-4.4.3.tar.gz
fi

# when we run Qt's configure, it ends up looking for 'src/' one dir up, so link it:
ln -sf qt-embedded-linux-opensource-src-4.4.3/src .

mkdir -p ${WORK_DIR}/build
pushd build/

  # put the raspberry pi cross-compiler toolchain on the path
  export PATH="${WORK_DIR}/tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin:${PATH}"

  export CFLAGS=-std=c99 CXXFLAGS=-std=gnu++98

  # echo 'yes' to accept license agreement
  echo yes | ../qt-embedded-linux-opensource-src-4.4.3/configure \
      -prefix ${INSTALL_PREFIX_DIR} \
      -embedded arm \
      -xplatform qws/linux-arm-g++ \
      -little-endian \
      -qt-zlib \
      -qt-gif \
      -qt-libtiff \
      -qt-libpng \
      -qt-libjpeg \
      -no-openssl \
      -no-cups \
      -no-sql-odbc \
      -no-sql-mysql \
      -no-sql-sqlite \
      -no-sql-ibase \
      -no-sql-psql \
      -no-sql-sqlite \
      -no-sql-sqlite2 \
      -no-qt3support \
      -no-webkit \
      -no-assistant-webkit \
      -nomake tools \
      -nomake examples \
      -nomake demos \
      -nomake docs \
      -nomake translations

  make -j6
  make install

popd # corresponds to: pushd build/

popd # corresponds to: pushd ${WORK_DIR}/
