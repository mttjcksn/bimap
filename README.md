# serialser
A container class that allows for fetching key by value and value by key. 
Supports iterating and (de)serialisation.

## Build example
```
cmake --preset clang-debug
cd build/clang-debug
cmake --build .
```

## Runing tests
```ctest```
(From inside build folder)

## Using in a cmake project
```
include(FetchContent)

FetchContent_Declare(
  bimap 
  GIT_REPOSITORY https://www.github.com/mttjcksn/bimap
  GIT_TAG  main
)

FetchContent_MakeAvailable(bimap)
```

Link with bimap-lib or reference source files with:

```"${bimap_SOURCE_DIR}/src"```