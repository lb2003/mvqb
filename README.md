# MVQB

This repository implements the maximum (α,β)-quasi biclique algorithm **MVQB** proposed in our paper. If you are using the code, please cite our paper.

## Compile the code

```
$ g++ MVQB.cpp -o mvqb
```

It generates an executable "MVQB", which corresponds to our MVQB algorithm

## Get datasets

The datasets used in our paper can be found from the links below.

`http://konect.cc`

## Data format

To provide a clearer understanding of the data format, we present a simple illustrate example as shown below.

Note that the three integers in the first line means the number of vertices _n_, the size of _L_ and the number of edges _m_. For the next _m_ lines, the first number is the vertice _i_, and the next numbers are the vertices connect to _i_.

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

## Run the code

The usage procedure for our program is as follows

You can use `-h ` to display the help menu.

```
$ ./mvqb -h
```

An example of computing the maximum (α,β)-quasi biclique for our provided example graph '’Example.g‘ is as follows

```
$ ./mvqb -f "Example.g" -u 2 -v 2 -a 0.7 -b 0.7
```

## Result Analysis

If you are using our provided example above, then you will see the following outputs in mvqb.txt. (other files might be a little different)

```
---------------Example.g a,b,lb_L,lb_R: 0.7 0.7 2 2 --------------
4
Running Time: 0 sec
```

From the obtained empirical results, we can extract the size of maximum (α,β)-quasi biclique is 4.

## Algorithm files

MVQB.cpp: our maximum (α,β)-quasi biclique algorithm in the paper.

ENUM.cpp: The baseline-ENUM algorithm in the paper.  

MVQB_c.cpp: MVQB without the graph coloring-based preprocessing technique (i.e. MVQB\\C).

MVQB_ubd.cpp: MVQB without using the degree-based upper bound (i.e. MVQB\\UBd).

MVQB_ubm.cpp: MVQB without missing degree-based upper bound (i.e. MVQB\\UBm).

MVQB_ubdm.cpp: MVQB without using either of the upper bounding rules (i.e. MVQB\\UBdm).

MVQB_rrd.cpp: MVQB without the degree-based reduction rule (i.e MVQB\RRd).

MVQB_rrc.cpp: MVQB without the common neighbor-based reduction rule (i.e MVQB\RRc).

MVQB_rrdc.cpp: MVQB without using either of the reduction rules (i.e MVQB\RRdc).

MVQB-br.cpp:  MVQB uses the same random branching vertex selection approach as the baseline ENUM.

MVQB-bm.cpp:  MVQB selects the vertex with the minimum degree in the candidate set.

