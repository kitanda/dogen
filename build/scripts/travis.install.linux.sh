#!/bin/bash
#
# Copyright (C) 2012-2016 Marco Craveiro <marco.craveiro@gmail.com>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be  useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#

#
# vcpkg dependencies
#
vcpkg_folder="vcpkg-export-20181009-143329"
vcpkg_package="${folder}.zip"
vcpkg_input_location="https://www.dropbox.com/s/0muqncafml30iey/${package}?dl=0"
vcpkg_output_location="/tmp/${package}"
vcpkg_extract_dir="/tmp/"
vcpkg_final_folder="vcpkg-export"
wget --no-check-certificate ${vcpkg_input_location} -O ${vcpkg_output_location}
unzip -q ${vcpkg_output_location} -d ${vcpkg_extract_dir}
mv ${vcpkg_extract_dir}/${vcpkg_folder} ${vcpkg_extract_dir}/vcpkg_final_folder
ls ${vcpkg_extract_dir}/vcpkg_final_folder

#
# common repos
#
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get update -qq

#
# clang
#
if [ "$CXX" == "clang++" ]; then
    server="http://apt.llvm.org/trusty/"
    sources="/etc/apt/sources.list"
    trusty="llvm-toolchain-trusty"
    sudo sh -c "echo 'deb ${server} ${trusty}-6.0 main' >> ${sources}"
    sudo sh -c "echo 'deb ${server} ${trusty}-6.0 main' >> ${sources}"
    wget -O - http://llvm.org/apt/llvm-snapshot.gpg.key | sudo apt-key add -
    sudo apt-get update -qq

    sudo apt-get install --allow-unauthenticated -qq clang-6.0
    which clang-6.0
    export CXX="clang++-6.0" CC="clang-6.0"
fi

#
# g++
#
if [ "$CXX" = "g++" ]; then
    sudo apt-get install -qq g++-8
    export CXX="g++-8" CC="gcc-8" GCOV="gcov-8"
fi

#
# ninja
#
sudo apt-get install ninja-build

#
# cmake
#
sudo rm -rf /usr/local/cmake-3.9.2

cmake_name="cmake-3.12.0-Linux-x86_64"
cmake_tar="${cmake_name}.tar.gz"
cmake_input="https://cmake.org/files/v3.12/${cmake_tar}"
cmake_output="/tmp/${cmake_tar}"
wget --no-check-certificate ${cmake_input} -O ${cmake_output}
tar xf ${cmake_output} -C /tmp
sudo cp -r /tmp/${cmake_name}/* /usr
which cmake
cmake --version
rm -rf ${cmake_output} /tmp/${cmake_name}

sudo apt-get clean
echo "Cleaned cache."
