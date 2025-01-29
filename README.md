## C++ 20 Thread-Safe HashTable

## Project Structure

```shell
cxx-thread-safe-ht
├── CMakeLists.txt
├── README.md
└── src
    ├── hash_function.cpp
    ├── hash_function.hpp
    ├── hash_table.hpp
    ├── hash_table_impl.hpp
    └── main.cpp         
```

## Compiling using CMake

Using CMake `FetchContent` to automatically pull the project dependencies.


- Git Clone the Project.
```shell
git clone https://github.com/isgo-golgo13/cxx-thread-safe-ht
```

- Create the Dist Directory
```shell
mkdir dist && cd dist
```

- Run CMake
```shell
cmake ..
```

The previous step will pull down the `blake3` library dependency and compile it as part of the project.  This will download `blake3` source code into `dist/_deps/blake3-src/` configure the project and auto-configure the depenencies.


- Compile to the EXE
```shell
cmake --build .
```

- Run the EXE
```shell
./ThreadSafeHashTable
```








