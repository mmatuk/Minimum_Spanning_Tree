The input file structure for the Minimum Spanning Tree test program needs to be as follows:

    n
    0 2 1 0 0 0 ... n (n total columns)
    2 0 0 2 1 0 ... n (n total columns)
    etc... (n+1 total lines)

    First Line: n = Number of Nodes
    The follwing n Lines: Shows the connections to the other nodes. Must have spaces between weights.
        EX: 021000

            Means:
                Node 1 has a connection to node 2 with a weight of 2.
                Node 1 has a connection to node 3 with a weight of 1.
                Any 0 means the current node does not have a connection.

        EX: 200210

            Means:
                Node 2 has a connection to node 1 with a weight of 2.
                Node 2 has a connection to node 4 with a weight of 2.
                Node 2 has a connection to node 5 with a weight of 1.
                Any 0 means the current node does not have a connection.

The output will be displayed as an adj matrix of the new tree to either the entered file name or to the command line. 


    EX: 
          1   2   4   5   6   7
          ______________________
        1| 1  14 500   7   6   8
        2| 0   0   5   3   6   0
        etc...

    The top line is the id for each node.
    The first number for the next n lines is the node id.
    _____________________________
    | INside this is the adj matrix for the minium spanning tree. 
    |
    |
    |
 