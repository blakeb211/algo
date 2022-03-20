## Demonstrations of different interesting algorithms
1. Andrew's Algorithm for finding the polygon that outlines or bounds
   a set of a points.
   - R version   : complete
   - C++ version : working 
   <img src="screenshots/convexhull/1.png" width=50% height=50%>

## Build instructions
   For R examples, either open in RStudio, or open file in R by typing:
   ```
   R
   source("filename.r")
   ```
   For c++ examples, first make sure **sdl2-dev** is installed. 
   Go into an individual example, then either modify the *build.sh* 
   script or create a **build** directory and build with cmake by typing:
   ``` 
   mkdir build
   cd build
   cmake ..
   make
   ```
   You can test with
   ```
   make test
   ```
## Templates Directory
   Contains templates to easily create additional examples that include an
   SDL visualization window and a ctest testbed.
