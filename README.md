# smpl_IGES

- Minimal C++ header-only library to write some types of geometry to IGES

## Dependancies

- Standard Library

## Usage

The entire library is contained in `src/smpl_IGES.hpp`, so one only needs to `#include` this header.

## Current Features

- `bspl_to_iges()` - write a B-spline surface to iges by specifying its knots and control polygon (Type 128 IGES)

## Documentation

Unfortunately, no organized documentation document exists yet. However each object is documented thoroughly at its definition.
Have a look at `examples/example.cpp` for a simple demonstration of the so-far limited capabilities of this library.

## References

The IGES format for some basic geometries is documented [here](https://wiki.eclipse.org/IGES_file_Specification#Rational_B-Spline_Surface_.28Type_128.29)