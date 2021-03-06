# Overview

Catfish implements an efficient heuristic to decompose a given flow into a set of minimum number of paths.  
Please refer to our paper at [here](https://doi.org/10.1109/TCBB.2017.2779509).
The tools, scripts, and datasets used in this manuscript can be found at 
[catfishtest](https://github.com/Kingsford-Group/catfishtest).

# Release
Latest release of Catfish is [v0.2.1](https://github.com/Kingsford-Group/catfish/releases/tag/v0.2.1),
including both [source code](https://github.com/Kingsford-Group/catfish/releases/download/v0.2.1/catfish-0.2.1.tar.gz),
and [linux binary](https://github.com/Kingsford-Group/catfish/releases/download/v0.2.1/catfish-0.2.1_linux_x86_64.tar.gz)
and [macOS binary](https://github.com/Kingsford-Group/catfish/releases/download/v0.2.1/catfish-0.2.1_macOS_10.10.tar.gz).


# Installation
Download Catfish from
[source code](https://github.com/Kingsford-Group/catfish/releases/download/v0.2.1/catfish-0.2.1.tar.gz).
To install it, you need to first download 
Boost if it has not been installed in your system,
and then compile the source code of Catfish.

## Install Boost
If Boost has not been downloaded/installed in your system, download Boost
[(license)](http://www.boost.org/LICENSE_1_0.txt) from (http://www.boost.org).
Uncompress it somewhere (compiling and installing are not necessary).

## Compile Catfish
Use the following to compile and install Catfish:
```
./configure --prefix=/path/to/your/installation/directory --with-boost=/path/to/your/boost/directory
make
make install
```
The `--prefix` argument for `configure` specifies the directory where you would put the binary of Catfish.
It is optional and the default is `/usr/local/bin` for most linux distributions.
If Boost has been installed in your system, the `--with-boost` argument for `configure` can also be omitted.


# Usage

The usage of `catfish` is:
```
catfish -i <input.sgr> -o <output-file> [-a core|full|greedy] [-h] [-v]
```

`-i` parameter specifies the input file,
which specifies multiple directed acyclic graph. 
Each graph starts with a header line marked with `#`.
The next line gives n, indicating the number of vertices in this graph.
The vertices are named from 0 to (n - 1), where vertex 0 has to be the source vertex
and vertex (n - 1) has to be the sink vertex. 
Each of the following line specifies an edge, which consists of three integers:
the in-vertex, out-vertex and the weight of this edge. 
There is one such input example files at `examples`.

`-o` parameter specifies the output file, which will show the predicted paths
and their associated abundances.

`-a` parameter specifies the algorithm.
There are three options: {full, core, greedy}.
With option of `core`, the program will only run the core algorithm to partly
decompose the given splice graph, which will predict fewer paths but with
higher accuracy.
With option of `full`, the program will completely
decompose the given splice graph, using greedy algorithm following the core algorithm.
With option of `greedy`, the program will only use greedy algorithm to fully decompose
the given splice graph. This parameter is optional, and its default value is `full`.

`-h` parameter prints the usage of Catfish and exits.

`-v` parameter prints the version of Catfish and exits.
