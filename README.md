# Overview

Catfish implements an efficient heuristic to decompose a given flow into a set of minimum number of paths.  
Please refer to our paper at [here](http://biorxiv.org/content/early/2016/11/16/087759).
The datasets used in this paper can be found at [here](https://cmu.box.com/s/p687exyr279wny7fb2rb36wifvavvu3f).

# Release
Latest release is [here](https://github.com/Kingsford-Group/catfish/releases/tag/v0.1.4).
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
The `--prefix` argument for `configure` gives the directory where you would put the binary of Catfish.
It is optional and the default is `/usr/local/bin` for most linux distributions.
If Boost has been installed in your system, the `--with-boost` option for `./configure` can also be omitted.


# Usage

The usage of `catfish` is:
```
./catfish -i input.sgr/input.gtf -o output.out [-a algo]
```

`-i` parameter specifies the input file.
Catfish accepts two types of input file formats. The first one is `.sgr`,
which specifies multiple directed acyclic graph. 
Each graph starts with a header line marked with a `#`.
The next line gives n, indicating the number of vertices in the graph. The vertices 
are named from 0 to (n - 1), where vertex 0 has to be the source vertex
and vertex (n - 1) has to be the sink vertex. 
Each of the following line specifies an edge, which consists of three integers:
the in-vertex, out-vertex and the weight of this edge. 
The second input file format
is `.gtf`. If it is this file format, Catfish will merge all transcripts
for each gene into a splice graph, and then try to decompose it.
There are two such input example files at `bin`.

`-o` parameter specifies the output file, which will show the predicted paths
and their associated abundances.

`-a` parameter specifies the algorithm.
There are three options: {full, core, greedy}.
With option of `core`, the program will only run the core algorithm to partly
decompose the given splice graph, which will predict fewer paths but with
higher accuracy. With option of `full`, the program will completely
decompose the given splice graph, using greedy algorithm following the core part of the algorithm.
With option of `greedy`, the program will only use greedy algorithm to fully decompose
the given splice graph. This parameter is optional, and its default value is `full`.
