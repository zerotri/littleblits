# RocKit

## Download/Build
The build process requires git. On Linux, a suitable SDL2 package should also be installed. Then run:

```bash
# download source
git clone https://github.com/zerotri/rockit
cd rockit

# create cmake build files in directory build/
cmake -B build/

# run build process on directory build/
cmake --build build/

# run demo
./build/bin/demo
```

## Coding Conventions
### Common
#### **Namespacing**
All code belonging to the `rockit` toolkit should be kept inside of the `rockit` namespace except where it is necessary to keep outside of a namespace, for example where using C compatible linkage.

#### **Classes vs. Structs**
Except where necessary, structs should be preferred to classes to promote public accessibility of data. This is done in favor of reducing complexity. Usage of `private` and `protected` keywords should also be kept to a minimum.

### Source Files (.cpp)
### Header Files (.h)
#### **Include Guard**
All header files should begin with `#pragma once` to prevent multiple inclusion of code.
