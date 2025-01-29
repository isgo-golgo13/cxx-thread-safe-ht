## C++ 20 Thread-Safe HashTable

## Project Structure

```shell
HashTableProject/
├── CMakeLists.txt          # Root CMake file
├── src/                    # Source files
│   ├── hash_function.cpp   
│   ├── hash_table.hpp      
│   ├── hash_table_impl.hpp 
│   ├── hash_function.hpp   
│   └── main.cpp            
├── blake3/                 
│   ├── blake3.h
│   ├── blake3.c
│   ├── blake3_dispatch.c
│   ├── blake3_portable.c
│   └── (other Blake3 files)
├── dist/                  
└── README.md               
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

The previous step will pull down the `blake3` library dependency and compile it as part of the project.


- Compile to the exe
```shell
cmake --build .
```

- Run the EXE
```shell
./ThreadSafeHashTable
```








