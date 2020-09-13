# NuGenTKI
  ## Documentation of source codes
   http://www-pnp.physics.ox.ac.uk/~luxi/transport/doxygen/NuGenTKI

  ## Quick how-to
  
style/, bin/, and include/AnaFunctions.h are from submodule TKI. Need to load/update separately with
   ```
   git submodule update --init
   ```
and
   ```
   git submodule update --remote
   ```
respectively.

In case of "Permission denied", open .git/config and change the url in [submodule “TKI”] part to url = https://github.com/luxianguo/TKI.git. See https://stackoverflow.com/questions/49191565/git-clone-works-git-submodule-fails-permission-denied
