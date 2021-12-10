BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir $BUILD_DIR
fi
cd $BUILD_DIR

# Compile
cmake ..
cmake --build . --target basic

# Run
# output: ../data/output_basic.txt
./basic ../data/input.txt