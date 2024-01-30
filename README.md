Quake2-WASM
===========

This is a WebAssembly port of the 3D first-person shooter Quake 2.

[Run Quake2-WASM in your browser here](https://gmh-code.github.io/quake2/).

Note that this version currently requires the PAK (asset) files from the shareware or full version of the original game.

[Quake-WASM](https://github.com/GMH-Code/Quake-WASM) is also available, playable [here](https://gmh-code.github.io/quake/), and can be built with open source PAK files.  Quake-WASM is based on id's original code, and is designed to match the original game as closely as possible.  It retains limitations, and has low memory usage and high performance in modern browsers.

Quake2-WASM is based upon *Yamagi Quake II*, and therefore inherits the changes to the original game.  These alterations may include changes to performance, memory usage, and visual effects.

Playing the Shareware Version
-----------------------------

The shareware PAK can be extracted from this file, widely available online:

    Filename: q2-314-demo-x86.exe
    File size: 39,015,499 bytes (37 MiB)
    SHA1: 5B4DEDC59CEEE306956A3E48A8BDF6DD33BC91ED
    SHA256: 7ACE5A43983F10D6BDC9D9B6E17A1032BA6223118D389BD170DF89B945A04A1E

You do *not* need to run this installer.  You can extract the PAK file directly from the executable using software like *7-Zip* or *WinRAR*.

The required file is in `Install/Data/baseq2`, and should match the following:

    Filename: pak0.pak
    File size: 49,951,322 bytes (47 MiB)
    SHA1: B86E8878A8E8706595CEEBE88B3E6B4C1BA5BCAB
    SHA256: CAE257182F34D3913F3D663E1D7CF865D668FEDA6AF393D4ECF3E9E408B48D09

Playing the Full Game
---------------------

This PAK file is the bare minimum needed to play the full version of Quake 2:

    Filename: pak0.pak
    File size: 183,997,730 bytes (175 MiB)
    SHA1: 1DD586A3230D1AC5BFD34E57CC796000D4C252C2
    SHA256: 1CE99EB11E7E251CCDF690858EFFBA79836DBE5E32A4083AD00A13ECDA491679

If you have the original CD, this file can be found in `Install/Data/baseq2`.

### Updating the Full Game

If you want to add the V3.20 update (recommended) which fixes bugs and other issues, grab this file online:

    Filename: q2-3.20-x86-full.exe
    File size: 13,842,432 bytes (13 MiB)
    SHA1: F0BECCE2618827C08CEB5C99575E1ED3D1FC003E
    SHA256: EE1B430258D5FC5A897EF47C6246F5DA11DE885F4C29FBECA005FF27924700BE

You can extract `pak1.pak` and `pak2.pak` without running the executable, using the same method as the shareware version.  These are the details of the files contained in the `baseq2` folder:

    Filename: pak1.pak
    File size: 12,992,754 bytes (12 MiB)
    SHA1: 588EF09965DEE539521B4EB6DA4337CE78A2EA21
    SHA256: 678210ECD1B27DDE1C645660333A1A7B139D849425793859657F804D379B62AD

    Filename: pak2.pak
    File size: 45,055 bytes (43 KiB)
    SHA1: 67E76A7F3234646507AE59EC1BF755637C1DAD03
    SHA256: CB88D584EF939D08E24433A6CF86274737303FAC2BBD94415927A75E6B269DD8

These two files can be placed in the same folder as `pak0.pak` to update the game.

### Licence Notes

The licence for the shareware version of Quake 2 only appears to permit duplication of the self-extracting archive (executable) that was originally obtained from an official source, so it appears as though, understandably, the archive's contents cannot be distributed nor embedded separately.

The full version carries an even more restrictive licence -- so do not be tempted to host the full version on a public server!

In-Browser Saving
-----------------

If you use the `Save` option or change the settings in-game, Quake2-WASM will attempt to commit those changes to browser storage.  These changes should persist after a browser reload.

Saving PAK files to storage isn't implemented as they are large and this can cause a substantial lag when the filesystem is synched.

Command-Line Arguments
----------------------

Like the desktop version of Quake 2, you can pass arguments to this version at runtime.  By default, the query portion of the URL is used, but the JavaScript code can be modified to use anything else, such as an input text box.

### Example

Let's say you were using the default template, serving the page locally, and you wanted to:

1. Start the software renderer, and
2. Start with the resolution set to 1920x1080.

To do this, you can start the game with `+set vid_renderer soft +set r_mode 21`.

In Quake2-WASM, you can append a single `?` to the end of the URL and place `&` between each parameter and value, where you would usually put a space.  This would look something like:

    https://127.0.0.1/quake2.html?+set&vid_renderer&soft&+set&r_mode&21

Networking Support
------------------

WebSockets support for multiplayer has not yet been added.

It should be possible to connect to a WebSockets proxy to enable online play, but Quake2-WASM will need rebuilding with the appropriate proxy configuration.

Mods and Mission Packs
----------------------

These are partly supported, but since the QuakeC interpreter was only present in Quake 1, mods and mission packs now require separate compilation into WebAssembly.

Mission pack code is *not* currently part of the Quake2-WASM build.

Due to an Emscripten limitation with load-time linking dynamic libraries in subfolders, only one `game.wasm` is supported at present, so you cannot switch between mods or mission packs at runtime.

Known Issues
------------

### OpenGL Renderer

All of these problems can be solved by configuring the game to use the software renderer, but that comes with a performance impact and change in visual quality.  You can choose this in `wasm.cfg`, `config.cfg`, at startup with `+set vid_renderer soft`.

These are the current issues:

- Starting this renderer after starting another (including the software renderer) will cause the display to revert to software mode, because otherwise the canvas becomes blank.
- This renderer cannot be restarted once it has started, meaning you cannot change display modes without reverting to the software renderer.  Forcing this in the code will result in the GL context (the 3D shapes) becoming corrupted.

Usage of the software renderer will likely be saved in the user's configuration, so to get back to OpenGL mode after reverting, the game must be restarted with `+set vid_renderer gl1`.

It appears as though the first two issues are likely within GL4ES, but it could also be due to some other improper shutdown of the GL context when the video is restarted.  Either way, reverting to the software renderer at least allows the user to save before exiting the game.

These OpenGL 1.x issues may someday be fixed by modifying the currently unusable OpenGL ES 3.x renderer to use native WebGL 2.x.

### Heap Usage

Quake 2's heap (an area of RAM for game objects) is dynamic, meaning it can allocate and de-allocate memory pages from system RAM depending on how much is required.  Memory allocated in Quake2-WASM's heap should be reused once allocated, but unlike on desktop systems, freed pages will *not* be completely returned to system RAM, because WebAssembly does not appear to support that yet.

How to Build on Linux for WebAssembly
-------------------------------------

### EMSDK

This is required to build both GL4ES and Quake2-WASM.

Clone or download EMSDK: https://emscripten.org/docs/getting_started/downloads.html

Install and fully activate the latest version, as per the instructions.

### GL4ES

This is currently required to build Quake2-WASM, and is the default renderer unless the user changes video settings.  If you start the game up in software mode, it will not be initialised or used.  At a future date, this library may be completely replaced by native WebGL.

Clone or download GL4ES: https://ptitseb.github.io/gl4es/

There is a change you must make before proceeding with the build:

1. Open `CMakeLists.txt` in a text editor.
2. Search the file for `Emscripten`.  There should be only one match.
3. In the next line (starting with `add_definitions`), add `-fPIC` before the closing bracket.

Remember to keep this customised ('PIC') copy of GL4ES separate from any other version.

Now run the GL4ES *Emscripten* build according to the instructions on: https://ptitseb.github.io/gl4es/COMPILE.html

### Quake2-WASM

1. Switch to the Quake2-WASM folder.
2. Run `emmake make GL4ES_PATH=/home/user/gl4es_pic`, substituting the GL4ES path as appropriate.  Your Emscripten installation will be automatically detected and used for the build.

The build will output the following into the `release` folder:

    quake2.html
    quake2.js
    quake2.data
    quake2.wasm
    game.wasm
    ref_soft.wasm
    ref_gl1.wasm

Note that the game will not properly boot without PAK files present in `wasm/baseq2`.  It is not legal to host nor embed any of the PAK files (or their contents) on a public server, regardless of whether you have the shareware or full version, so do not be tempted to do this.  In any case, licence compliance is your responsibility.

You can rename `quake2.html` to `index.html` or `index.htm`, if you wish.

To massively reduce bandwidth and download time, compress all the files using GZip (or better, Brotli) compression, host the files statically, and verify the web browser is doing the decompression for each file.
