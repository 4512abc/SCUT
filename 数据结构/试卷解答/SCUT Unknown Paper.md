# SCUT Unknown Paper

## A common problem for compilers and text editors is to determine if the parentheses (or other brackets) in a string are balanced and properly nested. For example, the string “((())())()” contains properly nested pairs of parentheses, but the string “)()(” does not, and the string “())” does not contain properly matching parentheses.



### (a) Give an algorithm that returns **true** if a string contains properly nested and balanced parentheses, and **false** otherwise. Use a stack to keep track of the number of left parentheses seen so far. *Hint*: At no time while scanning a legal string from left to right will you have encountered more right parentheses than left parentheses.  (8 scores)



### (b) Give an algorithm that returns the position in the string of the first offending parenthesis if the string is not properly nested and balanced. That is, if an excess right parenthesis is found, return its position; if there are too many left parentheses, return the position of the first excess left parenthesis. Return -1 if the string is properly balanced and nested. Use a stack to keep track of the number and positions of left parentheses seen so far.  (8 scores)

 

 

 

 



 

 

 

 

 

 

 

 

4. Assume that a given binary tree stores integer values in its nodes. Write a recursive function that sums the values of all nodes in the tree. (6 scores)

 

 



 

 

5. Trace by hand the execution of creation a binary search tree with the input sequence as : {46，25，78，62，12，37，70，29} which is empty tree initially. (6 scores)

 

 



 

 

 

6. Show the max-heap that results from running **buildHeap** on the following values stored in an array:                       

​        10 5 12 3 2 1 8 7 9 4

(8 scores)

 

 

 

 

 



 

8. Using closed hashing, with double hashing to resolve collisions, insert the following keys into a hash table of eleven slots (the slots are numbered 0 through 10). The hash functions to be used are H1 and H2, defined below. You should show the hash table after all eight keys have been inserted. Be sure to indicate how you are using H1 and H2 to do the hashing. ( The process of your solution is required!!!)     

H1(k) = 3k mod 11    H2(k) = 7k mod 10+1 

Keys: 22, 41, 53, 46, 30, 13, 1, 67.              (9 scores)

 

 

 

 

 

 

 

 

 

 

 

 

9. Show the result of inserting the value 55 into the B-tree.  (10 scores)



![img](file:///C:/Users/APP/AppData/Local/Temp/msohtmlclip1/01/clip_image002.gif)

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

 

​      

 

10. (10 scores)
11. Show the DFS tree for the graph, starting at Vertex 1.
12. List the order in which the edges of the graph are visited when running Kruskal’s MST algorithm.

![img](file:///C:/Users/APP/AppData/Local/Temp/msohtmlclip1/01/clip_image004.gif)

 

 



​            

1. Suppose Hash tables are built with the numbers inserted in the order of 12, 10, 26, 8, 2, 5, 40, 11. 

Draw the hash tables by respectively adopting the following two combinations of hash function and collision resolution strategies.

(1)   Bucket hashing with a 10-slot hash table using the hash function ***h(K) = (3K+1) mod 10\*.** Each bucket contains 2 slots. If a bucket is full, the record is stored in the overflow bucket.

(2)   Closed hashing with a 10-slot hash table using ***h(K) = (3K+1) mod 10\***; linear probing with the probe function *p(K, i) = 3i*

 

Answer:

(1)

Hash table     overflow

| 40   |
| ---- |
| 10   |
|      |
|      |
| 11   |
| 8    |
| 2    |
| 12   |
|      |
| 26   |

| 5    |
| ---- |
|      |
|      |
|      |

 

​    (2)

| 2    |
| ---- |
| 10   |
|      |
| 11   |
| 40   |
| 8    |
| 5    |
| 12   |
|      |
| 26   |

 

 

 

2. Given the following B+-tree of order 3, in which the leaf nodes can store up to 3 records.

Two records with key values 13 and 50 are inserted in the given order. Draw the updated B+-tree after each insertion, respectively. 

 



|      |                                                              |
| ---- | ------------------------------------------------------------ |
|      | ![img](./../../source/images/SCUT%20Unknown%20Paper/clip_image001.png) |

 



 

 

 

 

 

 

Answer: 

After inserting 13 

 



|      |                                                              |
| ---- | ------------------------------------------------------------ |
|      | ![img](./../../source/images/SCUT%20Unknown%20Paper/clip_image002.png) |

 



 

 

 

 

 

 

 

After inserting 50



|      |                                                              |
| ---- | ------------------------------------------------------------ |
|      | ![img](./../../source/images/SCUT%20Unknown%20Paper/clip_image003.png) |

 



 

 

 

 

 

 

 

 

 

 

3. Suppose Prim’s algorithm is revised to find the maximum spanning tree (MaxST). The revision is simply that the MaxST is repeatedly expanded by selecting the largest-cost edge from a vertex currently in the MaxST to a vertex not currently in the MaxST.

Run the revised Prim’s algorithm described above on the following graph staring at vertex 2. Draw the final MaxST.



|      |                                                              |
| ---- | ------------------------------------------------------------ |
|      | ![img](./../../source/images/SCUT%20Unknown%20Paper/clip_image005.png) |

 



 

 

 

 

 

 

 

 

 

Answer：

 

 



|      |                                                              |
| ---- | ------------------------------------------------------------ |
|      | ![img](./../../source/images/SCUT%20Unknown%20Paper/clip_image006.png) |

 



 

 

 

 

 

 

 

 

 

4. Assume that a computer system has disk blocks of 4096 bytes, and a record have 4-byte keys and 12-byte data fields. There are 230 records which are sorted and packed sequentially into the disk file. 

(1)  Suppose a linear index is constructed to index the records, which uses 4 bytes to store the key and 4 bytes to store the block ID for the associated records. What is the size of the linear index?

(2)  Suppose a B+-tree of order 128 is built with each leaf node corresponding to each data block. An internal node has up to 128 key/pointer pairs where the key size and the pointer size are both 4 bytes. Estimate the size of the smallest possible B+-tree with the size of the data blocks excluded.

 

Answer:

(1)  1block stores 28=256 records; 230 records needs 230/28 = 222 blocks

For linear index, the size is 222*(4+4) =225 bytes = 32MB

(2)  For the B+-tree index, 

the number of internal nodes at the level above leaf nodes is 222/27=215

the number of internal nodes one level above is 215/27=28

the number of internal nodes one level above is 2

one root node

the size of an internal node is 128*8=210 bytes = 1KB. In total, the size of B+-tree is （215+28+2+1）*1KB=32.25MB

 