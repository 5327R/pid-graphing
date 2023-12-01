build: 
  cmake --build build

run: build
  ./build/app

clean:
  cmake --build build --target clean
