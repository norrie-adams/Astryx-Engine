# Testing

This is a guide on how to run unit tests. Its very simple.

### Steps

1. Make sure you have followed steps 1-4 in BUILDING.MD
2. Run the following command. This runs the unit tests using CTest:

```bash 

cd build && ctest

```

**I recommend adding the --output-on-failure flag because it makes it much easier to actually figure out what went wrong to do this, make sure you are in the build directory and run the following command:**

```bash

ctest --output-on-failure

```