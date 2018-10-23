![Dogen Logo](https://raw.githubusercontent.com/MASD-Project/dogen/master/doc/images/new_logo_with_message.png)

[![Licence](https://img.shields.io/badge/license-GPL_3-green.svg?dummy)](https://raw.githubusercontent.com/MASD-Project/dogen/master/LICENCE)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FMASD-Project%2Fdogen?ref=badge_shield)
[![Status](https://img.shields.io/badge/status-active-brightgreen.svg?style=flat)](https://github.com/MASD-Project/dogen/pulse/monthly)
[![Gitter](https://img.shields.io/gitter/room/nwjs/nw.js.svg)](https://gitter.im/MASD-Project/Lobby)
[![Issues](https://img.shields.io/github/issues/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/issues)
[![Github All Releases](https://img.shields.io/github/downloads/MASD-Project/dogen/total.svg)](https://github.com/MASD-Project/dogen/releases)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5d7fca8ac9a64ea8b8d35bc8b0d534b5)](https://www.codacy.com/app/marco-craveiro/dogen?utm_source=github.com&utm_medium=referral&utm_content=MASD-Project/dogen&utm_campaign=badger)
[![Build Dashboard](https://img.shields.io/badge/cdash-dashboard-00cc00.svg)](https://my.cdash.org/index.php?project=MASD+Project+-+Dogen)
[![Build Status](https://img.shields.io/travis/MASD-Project/dogen.svg?label=linux/osx)](https://travis-ci.org/MASD-Project/dogen)
[![Build Status](https://img.shields.io/appveyor/ci/mcraveiro/dogen.svg?label=windows)](https://ci.appveyor.com/project/mcraveiro/dogen)
[![Coverage Status](https://coveralls.io/repos/github/MASD-Project/dogen/badge.svg?branch=master)](https://coveralls.io/github/MASD-Project/dogen?branch=master)
[![codecov](https://codecov.io/gh/MASD-Project/dogen/branch/master/graph/badge.svg)](https://codecov.io/gh/MASD-Project/dogen)
[![Releases](https://img.shields.io/github/release/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/releases)
[![Binaries (Stable)](https://api.bintray.com/packages/masd-project/main/dogen/images/download.svg?version=1.0.09) ](https://bintray.com/masd-project/main/dogen/1.0.09/link)
[![Binaries (Unstable)](https://api.bintray.com/packages/masd-project/main/dogen/images/download.svg) ](https://bintray.com/masd-project/main/dogen/_latestVersion)
[![GitHub commits](https://img.shields.io/github/commits-since/MASD-Project/dogen/v1.0.09.svg)](https://github.com/MASD-Project/dogen/commits/master)
[![Contributors](https://img.shields.io/github/contributors/MASD-Project/dogen.svg)](https://github.com/MASD-Project/dogen/graphs/contributors)
[![Language](https://img.shields.io/badge/Language-C++-blue.svg)](https://www.openhub.net/p/dogen/analyses/latest/languages_summary)
[![C++](https://img.shields.io/badge/std-C++17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![gcc-8](https://img.shields.io/badge/GCC-8-blue.svg)](https://www.gnu.org/software/gcc/gcc-8)
[![clang-7](https://img.shields.io/badge/CLANG-7-blue.svg)](http://releases.llvm.org/7.0.0/tools/clang/docs/ReleaseNotes.html)
[![msvc2017](https://img.shields.io/badge/MSVC-2017-blue.svg)](https://visualstudio.microsoft.com/vs/whatsnew/)
[![Coverity](https://img.shields.io/coverity/scan/16865.svg)](https://scan.coverity.com/projects/masd-project-dogen)
[![Project Stats](https://www.openhub.net/p/dogen/widgets/project_thin_badge.gif)](https://www.openhub.net/p/dogen)

# Overview

**Dogen** is the reference implementation of the MASD Project code
generator. MASD - Model Assisted Software Development - is a new
methodology for the development of software systems based on [MDE
(Model Driven
Engineering)](https://en.wikipedia.org/wiki/Model-driven_engineering). The
theoretical framework for MASD is under development as part of my PhD
thesis, and is not yet ready for public review. However, the
development of Dogen remains as it always was, an open source project
available to all.

In lay terms, Dogen's objective is to automate the development process
as much as possible: the user creates models in one of the supported
frontend formats and respecting a set of predefined restrictions;
Dogen then uses this input to generate a source code representation of
the model. At present the main frontend is
[Dia](https://en.wikipedia.org/wiki/Dia_(software)), but we also
support [JSON](http://json.org/). Depending on use cases and user
demand, other frontends may follow.

The generated code contains most of the functionality required from a
typical C++ domain object such as serialisation, hashing, streaming
and so on. Whilst we intend for the application to be useful out of
the box for most use cases, our end goal is to enable users to extend
Dogen, adapting it to the vagaries of their specific needs. Note that
Dogen has experimental C# support, but it is not in feature parity
with C++ support.

Dogen provides a reference implementation for each supported language,
available as a separate git repo:

- [C++ Reference
  Implementation](https://github.com/MASD-Project/cpp_ref_impl). Models
  available [here](https://github.com/MASD-Project/cpp_ref_impl/tree/master/projects/models).
- [C# Reference
  Implementation](https://github.com/MASD-Project/csharp_ref_impl). Models
  available [here](https://github.com/MASD-Project/csharp_ref_impl/tree/master/Src/Models).

These are designed to give you a feel for how the generated code will
look like, and they attempt to exercise all of Dogen's functionality.

# Binary Packages

Binary packages are available for each release on
[BinTray](https://bintray.com/masd-project/main/dogen), covering
Debian Linux, OSX and Windows - 64-bit only. Packages are generated
for each commit. Development is done from git master, so latest should
always be greatest, but you may want to use packages from the previous
sprint rather than what is currently under development (see badges
above).

---
**Notes**

The OSX installer provides you with a DMG. Once you open it in Finder,
it mounts under ```/Volumes/```, e.g.:

```
/Volumes/dogen-${VERSION}-Darwin-x86_64/dogen.app/Contents/Resources/bin
```

Where ```${VERSION}``` is your Dogen version such as ```1.0.10```.

----

# Building From Source

In order to build Dogen you will need a C++ toolchain. On Linux and
OSX, you'll need a recent compiler with C++ 17 support, such as [GCC
8](https://www.gnu.org/software/gcc/gcc-8) or [Clang
7](https://img.shields.io/badge/CLANG-7-cyan.svg) - and
[Ninja](https://ninja-build.org/manual.html) or [GNU
Make](https://www.gnu.org/software/make/). On Windows you'll need
[Visual Studio
2017](https://visualstudio.microsoft.com/vs/whatsnew/). Older
compilers may work, but we try to always use the most recent releases
in MASD. So, if you can, please try using to those.

Dogen has the following additional dependencies, across all operative systems:

| Name   | Type      | Version                | Description                             |
|--------|-----------|------------------------|-----------------------------------------|
| [CMake](https://cmake.org/)  | Mandatory | 3.12 or later.  | Required to generate the build files.Earlier versions may also work.  |
| [Boost](https://boost.org)  | Mandatory | 1.68 or later. | Earlier versions may also work, but patches may be needed. **Very Important**: We link statically against Boost at present, so be sure to build and install the static libraries.|
| [LibXml2](http://xmlsoft.org/) | Mandatory | 2.9.4 | Earlier versions may work but haven't been tested.|
| [Doxygen](http://www.doxygen.nl/) | Optional | Any recent | Required to build the source code documentation. |

Though Dogen should build fine with package manager supplied
libraries - or even with hand-built dependencies - the easiest way to
setup a development environment on all supported platforms is by using
[vcpkg](https://github.com/Microsoft/vcpkg). Compile it as per [vcpkg
documentation](https://github.com/Microsoft/vcpkg/blob/master/README.md),
then run:

```
./vcpkg install libxml2 boost-system boost-serialization boost-date-time boost-log boost-filesystem boost-program-options boost-test boost-scope-exit boost-graph boost-uuid boost-di boost-spirit
```

---
**Notes**


- The default vcpkg triplet on Windows [is 32-bit
dynamic](https://github.com/Microsoft/vcpkg/issues/1254) whereas we
build with ```--triplet x64-windows-static```. If you are experiencing
[weird and wonderful build
errors](https://github.com/Microsoft/vcpkg/issues/4447), check your
triplet.
- If you are on OSX, you probably should rely on the system's LibXML2
(e.g. remove it from the vpkg list above) or else you may see [some
interesting linking
errors](https://github.com/Microsoft/vcpkg/issues/4476) related to ```iconv```.
- Remember that the recommended compiler for OSX is Homebrew's GCC. If
  you do decide to use Clang, beware that for some reason [boost does
  not
  default](https://github.com/Microsoft/vcpkg/issues/4476#issuecomment-430175834)
  to C++ 14. You'll need to add ```cxxstd=14```.

---

Once you have all dependencies set up, you can then clone the
repository and create the build directory:

```
git clone https://github.com/MASD-Project/dogen.git
cd dogen/build
mkdir output
cd output
```

On Linux and OSX, you can build using GNU Make as follows:

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_VCPKG_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake ../..
make -j${CORES}
```

Where ```PATH_TO_VCPKG_DIR``` is the directory in which you've
downloaded and built vcpkg and ```CORES``` is the number of cores
available on your machine. Alternatively, you can use Ninja:

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_VCPKG_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake ../.. -G Ninja
ninja -j${CORES}
```

On Windows, the incantation is slightly different:

```
cmake -DCMAKE_TOOLCHAIN_FILE=${PATH_TO_VCPKG_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake ../.. -DCMAKE_BUILD_TYPE=Release -G 'Visual Studio 15 2017 Win64'
cmake --build . --config Release --target ALL_BUILD
```

---
**Notes**

If you are **not** using vcpkg, you can omit ```-DCMAKE_TOOLCHAIN_FILE```.
However if the dependencies are not on the standard paths, you must then set
```CMAKE_INCLUDE_PATH``` and ```CMAKE_LIBRARY_PATH``` accordingly, e.g.:

```
CMAKE_INCLUDE_PATH=/my/boost/include/path CMAKE_LIBRARY_PATH=/my/boost/lib/path cmake ../..
```

---

## Running Tests

If you'd like to run the project tests, execute the target
```run_all_tests``` or its abbreviation ```rat```.

## Regenerating Models

If you'd like to run Dogen to regenerate all of its models, you can do
so by using the target ```knit_all``` or its abbreviation
```ka```. This is useful, for example, to update the models to the
latest version of Dogen, or just to see how Dogen works. By default
Dogen uses the current built version, but you can also use
another. For this you may need to tell CMake of its location by
setting ```CMAKE_PROGRAM_PATH```:

```
CMAKE_PROGRAM_PATH=/path/to/dogen/binary cmake ../..
```

After regeneration, you can then use ```git diff``` to inspect the
differences produced by regeneration, if any. The build directory
contains all of the logs, under the directory ```log```.

# Videos

We don't really have any recent videos for Dogen, but this very old
one should at least give you an idea of its workflow:

[![Alt text](https://img.youtube.com/vi/Z7k8qbImXkU/0.jpg)](https://youtu.be/Z7k8qbImXkU)

# Blog Posts

Over time, a number of assorted blog posts have been published on
Dogen, mainly covering its development process:

- **[Nerd Food: The Refactoring Quagmire](https://mcraveiro.blogspot.co.uk/2018/01/nerd-food-refactoring-quagmire.html)**: How we solved the "refactoring ad infinitum" problem in Dogen development.
- **Nerd Food: Northwind, or Using Dogen with ODB**: Four part series on using Dogen with [ODB](https://www.codesynthesis.com/products/odb/). [Part I](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with.html), [Part II](http://mcraveiro.blogspot.co.uk/2017/02/nerd-food-northwind-or-using-dogen-with_24.html), [Part III](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with.html), [Part IV](http://mcraveiro.blogspot.co.uk/2017/03/nerd-food-northwind-or-using-dogen-with_25.html).
- **[Nerd Food: The Strange Case of the Undefined References](http://mcraveiro.blogspot.co.uk/2016/06/nerd-food-strange-case-of-undefined.html)**: Problems faced using Conan with Dogen.
- **[Nerd Food: On Product Backlog](http://mcraveiro.blogspot.co.uk/2016/01/nerd-food-on-product-backlogs.html)**: The importance of the Product Backlog in Dogen development.
- **[Nerd Food: Dogen: The Package Management Saga](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-dogen-package-management-saga.html)**: Dogen's attempt at finding a package management for C++.
- **[Nerd Food: Pull Request Driven Development](http://mcraveiro.blogspot.co.uk/2015/12/nerd-food-pull-request-driven.html)**: Not directly related to Dogen as we don't get many PRs, but may be of interest; reflections on the importance of a Pull-Request Driven Development approach.
- **[Nerd Food: Dogen: Lessons in Incremental Coding](http://mcraveiro.blogspot.co.uk/2014/09/nerd-food-dogen-lessons-in-incremental.html)**: How the Dogen development process works, via very small, incremental changes.

# Reporting Problems

If you have encountered a failure building Dogen or running its unit
tests, please submit a bug report. It must include:

- the error messages;
- the versions of all dependencies (compiler, Boost etc);
- the operative system name and version;

If you find a bug whilst using Dogen with one of your models, please
also include:

- a small model reproducing the problem;
- the compressed log; it is located under the directory where you
  executed Dogen and named ```dogen.knitter.MODEL.log``` where
  ```MODEL``` is the name of the model you ran against.

Bugs can be submitted
using [github Issues](https://github.com/MASD-Project/dogen/issues).
