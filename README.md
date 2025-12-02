## Lib Build & Install to generated_libs

```bash
cd complexNumberLib-static-shared

cmake -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_SHARED=ON
 && cmake --build build --config Release
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Release
```

Debug type
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SHARED=ON
 && cmake --build build --config Debug
 && cmake --install build --prefix "..\generated_libs\complexNumber" --config Debug
```

## Consumer Build

```bash
cd complexNumberLib-consumer

cmake -B build -DCMAKE_PREFIX_PATH="../generated_libs/complexNumber" -DCMAKE_BUILD_TYPE=Release
 && cmake --build build --config Release
```

source: https://cfd.university/learn/automating-cfd-solver-and-library-compilation-using-cmake/how-to-compile-install-and-use-custom-libraries-with-cmake/