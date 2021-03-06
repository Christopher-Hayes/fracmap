FracMap
=======

Based on the source code found here: ["FracMAP: a user-interactive package for performing simulation and orientation-specific morphology analysis of fractal-like solid nano-agglomerates"](http://cpc.cs.qub.ac.uk/summaries/AEDD_v1_0.html)

Software for simulating carbon pseudo-fractal agglomerates and analyzing their morphological properties.

Hints For Usage
---------------

The compiled version of the program presently runs a single fractal. A subroutine analysis can be compiled and run with “File” > “Run Subroutine” that allows for the processing of many fractal aggregates.

If you have difficulty viewing the micrograph of a fractal, attempt to expand the micrograph window to fullscreen. Also, be aware that minor graphical bugs exist.


Hints for Compiling
-------------------

This version of FracMAP with a graphical user interface was developed using Microsoft Visual C++.  A subfolder called /unixfractal contains files sufficient for developing your own unix command-line application.

To compile, you must have downloaded, installed, and compiled [wxWidgets][1].

Under Project > Properties for the solutions:

*   Configuration Properties > C/C++ > General > Additional Include Directories should reflect something similar to the following (relative to your own wxWidgets installation):

    `C:\wxWidgets\lib\vc_lib\mswd;C:\wxWidgets\include;.;.\unix_fractal;C:\wxWidgets\samples;%(AdditionalIncludeDirectories)`

*   Configuration Properties > C/C++ > Preprocessor > Preprocessor Definitions

    For release: `WIN32;__WXMSW__;_WINDOWS;NOPCH;%(PreprocessorDefinitions)`
    
    For debug: `WIN32;_DEBUG;__WXMSW__;__WXDEBUG__;_WINDOWS;NOPCH;%(PreprocessorDefinitions)`

*   Configuration Properties > Linker > General > Additional Library Directories

    This should be changed to reflect your wxWidgets installation: `C:\wxWidgets\lib\vc_lib;%(AdditionalLibraryDirectories)`

*   Configuration Properties > Linker > Input > Additional Dependencies

    This should be changed to reflect the proper version for your wxWidgets installation: `wxmsw28d_gl.lib;opengl32.lib;glu32.lib;wxmsw28d_core.lib;wxbase28d.lib;wxtiffd.lib;wxjpegd.lib;
wxpngd.lib;wxzlibd.lib;wxregexd.lib;wxexpatd.lib;winmm.lib;comctl32.lib;rpcrt4.lib;
wsock32.lib;odbc32.lib;%(AdditionalDependencies)`


[1]: http://www.wxwidgets.org/    "wxWidgets"
[2]: http://www.mgarro.com/wp-content/uploads/2011/09/wxFracMap.zip "FracMap executable"

