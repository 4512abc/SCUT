# SCUT2013COAA

### Point on the dependent instructions,Can we eliminate the data dependencies using forwarding if not ,what should we do? Draw a diagram to show the pipelined execution of the 4个命令

```assembly
Add R3 R1 #100

Or  R4 R5 R6

Load  R2 (R3)

Subtract R9 R2 #30
```

![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202412261029830.webp)





### 两种 static memory chips :128k X 8 bit (total 4 chips) and 512k X 4bit (total 2 chips) implement a 512k X 16 bit memory ,draw the figure of the memory organization.

 

 

 

 

### instruction length :10 bit,operand address :4 bit, need 3 two-address instructions, 15 one , 16 zero . How design instruction format

**答案**：

- 8位用于操作数

  ```assembly
  00 aaaa bbbb
  01 aaaa bbbb
  10 aaaa bbbb
  ```

- 4位用于操作数

  ```cpp
  11 0000 aaaa
  11 0001 aaaa
  11 0010 aaaa
  11 0011 aaaa
  11 0100 aaaa
  11 0101 aaaa
  11 0110 aaaa
  11 0111 aaaa
  11 1000 aaaa
  11 1001 aaaa
  11 1010 aaaa
  11 1011 aaaa
  11 1100 aaaa
  11 1101 aaaa
  11 1110 aaaa
  ```

- 0位用于操作数

  ```assembly
  111111 0000
  111111 0001
  111111 0010
  111111 0011
  111111 0100
  111111 0101
  111111 0110
  111111 0111
  111111 1000
  111111 1001
  111111 1010
  111111 1011
  111111 1100
  111111 1101
  111111 1110
  111111 1111
  ```

  

### Give the sequence of steps need to fetch and execute the instructions on 5-stage RISC

```assembly
SUB R1 R2 R3 (32bit operand)
```

**答案**：

```assembly
1	Memory Address <- [PC], Read Memory, IR <- Memory Data, PC <- [PC] + 4
2	Decode Instruction,	RA <- [R2], RB <- [R3]
3	RZ <- [RA] - [RB]
4	RY <- [RZ]
5	R1 <- [RT]
```

