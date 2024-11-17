## MVQB

This repository implements the maximum (α,β)-quasi biclique algorithm **MVQB** proposed in our paper. If you are using the code, please cite our paper.

### compile the code

```
$ g++ MVQB.cpp -o mvqb
```

It generates an executable "MVQB", which corresponds to our MVQB algorithm

### Get datasets

The datasets used in our paper can be found from the links below.

`http://konect.cc`

### Data format

To provide a clearer understanding of the data format, we present a simple illustrate example as shown below.

Note that the three integers in the first line means the number of vertices _n_, the size of _L_ and the number of edges _m_. For the next _m_ lines, the first number is the vertice _i_, and the next numbers are the vertice connect to _i_.

```
11 5 16
0 5 6 7
1 6 7 8 10
2 7 8 9
3 8 9 5
4 9 5 6
5 0 3 4
6 0 1 4
7 0 1 2
8 1 2 3
9 2 3 4
10 1
```

### Run the code

The usage procedure for our program is as follows.

You can use `-h ` to display the help menu

```
$ ./mvqb -h
```

An example of computing the xxx for our provided example graph '’Example.g‘ is as follows

```
$ ./mvqb -f "Example.g" -u 2 -v 2 -a 0.7 -b 0.7
```

### Result Analysis

If you are using our provided example abouve, then you will see the folloing outputs

```
---------------Example.g a,b,lb_L,lb_R: 0.7 0.7 2 2 --------------
4
Running Time: 0 sec
```

From the obtained empirical results, we can extract the size of maximum (α,β)-quasi biclique is 4.