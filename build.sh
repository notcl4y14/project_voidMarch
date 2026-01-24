# Remove build artifacts
rm -rf build lib

# Build the rust crate
cd math_core && cargo b -Z unstable-options --artifact-dir "../lib/" && cd ..

# Build the Project
cmake -B build -G Ninja
cmake --build build
