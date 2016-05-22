# engine (no name yet)
This is currently a C++ rewrite of the (incomplete) physics simulator I wrote in D. It's not up to the point I was at in D yet. Once I get to that point I will be adding in more features and making a more flushed out engine. This is 100% for fun at the moment so there will be some weird things going on inside. As of May 6th the rendering engine has equal abilities as its D counterpart.
# Current (small) Goals
* Implement Component based design and abstract the rendering system
* Implement shadows, better lighting
* Longer Term:
 * An Editor (Now in the works and based on Qt). It's possible I can tie the engine's GUI libraries for in game GUI to Qt as well.
 * Physics (probably third party lib)
 * Possibly networking
 * Performance Improvments
 * Refactor and clean up code in general/read more C++ books and write better C++ code
 * Sound
 * All of the hundreds of other things you can add to a game engine
 
# Building
# Linux
`cd` into the build/ directory and run `cmake ..` then `make` and the executable will be located in the main folder.
# OSX
`cd` into the build/ directory and run `cmake .. -DCMAKE_PREFIX_PATH=/usr/local/Cellar/qt5/5.6.0` or set the `CMAKE_PREFIX_PATH` to the installation path. Then `make` and the executable will be located in the main folder.
