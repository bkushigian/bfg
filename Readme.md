# BFG README
## What is BFG?
BFG is a fractal generation program, designed in C++ with an eye towards being
very flexible on the back end. Currently I am working on creating an interpreter
for a very basic language `BFGLang` through which `BFG` will be interacted with.

## Installing
### Installation Dependencies
Currently the only external library is SFML. This has been built on Ubuntu
14.04 but will be ported to OSx/Windows at earliest convenience. Compiles with
the 
<pre>make</pre>
command run from the project home directory.. Requires <code>g++ 5.0</code> or greater
for `C++14` support. 

## Overview of Files
Currently <code>main.cpp</code> creates a Mandelbrot set and adds it to our
window manager <code>WM</code>. This will eventually be handled from command
line -- it is strictly for testing purposes at the moment. Our object hierarchy
is as follows

### Object Hierarchy
Everything displayable will be a derived from the `object` class. The 
`fractal` class is declared:

<pre>class fractal : public object {
...
};</pre>
and defines an abstract fractal class. Each implementation of a fractal is derived
from `fractal`. Fractals (and objects in general) are stored dynamically in a
`fManager` instance - more precisely, pointers to dynamically allocated fractal
instances are stored in an `fManager` instance. These must be cast explicitly
when invoking functions on them that are not general to `object` -- this includes
`draw()`, `setC( complex z)` (for the `julia` class), etc.

The `winManager` class contains an `fManager` class and an instance of SFML's 
`RenderWindow` to display the various fractals. `winManager` has a very unwieldy
`handleEvent()` function that needs to be broken up (currently over 220 lines).


