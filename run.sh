BUILD_DIR="new_build"
if [ ! -d "$BUILD_DIR" ]; then
  mkdir $BUILD_DIR
fi
cd $BUILD_DIR

# Compile
cmake ..
make

# Run basic program
./basic ../data/input.txt

# Run efficient program
./efficient ../data/input.txt