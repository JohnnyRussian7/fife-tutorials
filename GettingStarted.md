# Introduction #
The instructions below will guide you through downloading and setting up the fife
engine as well as the fife-tutorials.


---

# Windows Install #
  1. Download the FIFE 0.3.2 [win32 installer](http://sourceforge.net/projects/fife/files/active/packages/FIFE-0.3.2r2_installer_win32.exe/download) from sourceforge and run the installer
  1. Checkout the [fife-tutorials](https://fife-tutorials.googlecode.com/svn/trunk) trunk to the location `<path-to-fife>`/tutorials
### Using Visual Studio ###
  1. Execute the script `<path-to-fife>`/build/win32/update\_project\_files.bat
  1. Navigate to `<path-to-fife>`/build/win32/build\_environments/visual\_studio`_`# where # is the version of visual studio you are using
  1. Open the solution fife\_engine.sln
  1. Go to the build configurations menu within visual studio and select either the "Debug\_static" or "Release\_static" configuration
  1. Build the solution and make sure no errors occurred
  1. Navigate to `<path-to-fife>`/tutorials/build/ and choose the directory based on which version of visual studio you are using
  1. Open the solution (.sln) file within the directory
  1. Set the build configuration within visual studio to either "Debug" or "Release" to correspond to how FIFE was built
  1. Build solution and make sure no errors occurred
### Using Mingw ###
TBD


---

# Linux Install #
> TBD
