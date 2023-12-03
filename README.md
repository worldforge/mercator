# DEPRECATED

This code has been moved to [the Worldforge repository](https://github.com/worldforge/worldforge). 

Mercator: a procedural terrain library
======================================

[![Join us on Gitter!](https://badges.gitter.im/Worldforge.svg)](https://gitter.im/Worldforge/Lobby)
[![Appveyor build status](https://ci.appveyor.com/api/projects/status/github/worldforge/mercator?branch=master&svg=true)](https://ci.appveyor.com/project/erikogenvik/mercator)
[![Travis build Status](https://travis-ci.com/worldforge/mercator.svg?branch=master)](https://travis-ci.com/worldforge/mercator)
[![Github build status](https://github.com/worldforge/mercator/actions/workflows/cmake.yml/badge.svg)](https://github.com/worldforge/mercator/actions/workflows/cmake.yml)

Mercator is primarily aimed at terrain for multiplayer online games and
forms one of the [WorldForge](http://worldforge.org/ "The main Worldforge site")
core libraries.
It is intended to be used as a terrain library on both the client and the
server.

## Installation

If you intend to build this as a prerequisite for the Ember client or the Cyphesis server we strongly suggest that you 
use the [Hammer](http://wiki.worldforge.org/wiki/Hammer_Script "The Hammer script") tool to compile it.
This is script provided by the Worldforge project which will download and install all of the required libraries and 
components used by Worldforge.

Alternatively you can use [Conan](https://www.conan.io) to install all dependencies. 
```bash
conan remote add worldforge https://artifactory.ogenvik.org/artifactory/api/conan/conan
conan install tools/conan --build missing
cmake --preset conan-release
cmake --build --preset conan-release
```

Otherwise the library can most easily be built through the following commands.
```bash
mkdir build && cd build
cmake ..
make -j all install
```

### Tests

The test suite can be built and run using the ```check``` target. For example:

```bash
make check
```

or 

```bash
cmake --build --preset conan-release --target check
```

### API documentation

If Doxygen is available API documentation can be generated using the ```dox``` target. For example:

```bash
make dox
```

or 

```bash
cmake --build --preset conan-release --target dox
```

## Design 
Mercator is designed in such a way that individual tiles can be
generated on-the-fly from a very small source data set.  Each tile uses
a fast deterministic random number generation to ensure that identical
results are produced "anytime, anywhere".  This enables transmission of
terrain across low bandwidth links as part of the standard data stream,
or server side collision detection with the same terrain that the
player sees. 

The use of tiles means that there is inherently a large degree of gross
control of the shape of the terrain.  Finer control is implemented by
allowing geometric modifications - for example, a polygonal area might
be flattened, or a crater could be applied.

### Height generation
* uses deterministic random number generation and seeds to
  generate detailed terrain from sparse control points.
* each tile is seeded using the four surrounding control points
* shape of each tile is influenced by height, roughness and
  falloff parameters

### Height Modifications
* geometric modifications can be applied for small features
* new types of modifications can be added quite easily

### Shading
* generate shading information based on height and gradient
* new types of shaders can be added quite easily
* used on the client side

### Collision
basic terrain intersection/collision functions are implemented for
* bbox
* point
* ray

### Vegetation
Basic support for generation of forests in much the same way as terrain.
Forest shape (polygonal) is supported
Tree location, orientation and height are generated from a random seed.
Currently incomplete and has hardcoded parameters

### Current Limitations
* multiple resolutions in the one terrain are unsupported

## How to help

If you're interested in helping out with development you should check out these resources:

* [The main Worldforge site](http://worldforge.org/ "The main Worldforge site")
* [Bugs and feature planning on Launchpad](https://launchpad.net/mercator "Mercator Launchpad entry")
* [Gitter conversation](https://gitter.im/Worldforge/Lobby "Gitter conversation")
* [Mailing lists](http://mail.worldforge.org/lists/listinfo/ "Mailing lists")
   
