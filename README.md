# Requirements

  * gcc v4.4 or newer
  * cmake or newer
  * Make

# installation guidelines
```
sudo apt install cmake g++ make
```

# Compilation

The code can be compiled with the provided build script named "build_all.sh"
```
./build_all.sh
```

If compiling the code manually, or integrating into a larger program, include
the following flags:

```
FLAGS=-fopenmp
```

# Run the program

Run the program using the following script

```
./run.sh
```

