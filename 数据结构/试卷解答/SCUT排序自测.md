# SCUT排序自测

第7章   排序自测 
一、填空题
1. 评价排序算法好坏的标准主要是( 执行时间 )和( 所需的辅助空间　)。

2. 若待排序的文件中存在多个关键字相同的记录，经过某种排序方法排序后，具有相同关键字的记录间的相对位置保持不变。则这种排序方法是(　稳定　)的排序方法。

3. 大多数排序算法都有两个基本的操作：（比较（两个关键字的大小））和（交
换（记录或改变指向记录的指针））。

4. 在对一组记录（54，38，96，23，15，72，60，45，83）进行直接插入排序
时，当把第7个记录60插入到有序表时，为寻找插入位置至少需比较(  3  )
次。(可约定为，从后向前比较) 

5. 在插入和选择排序中，若初始数据基本正序，则选用（ 插入排序 ）；若初
始数据基本反序，则选用（  选择排序  ）。

6. 直接选择排序的总的关键字比较次数与(　文件的初始状态 　)无关。

7. 在堆排序和快速排序中，若初始记录接近正序或反序，则选用（  堆排序  ）；
若初始记录基本无序，则最好选用(   快速排序  )。


8. 在堆排序、快速排序和归并排序中，若只从排序结果的稳定性考虑，则应选取(  归并排序  )方法；
    若只从平均情况下最快考虑，则应选取(  快速排序  ) 方法；
    若只从最坏情况下最快并且要节省内存考虑，则应选取(  堆排序  )方法。

9. 分配排序的两个基本过程是(　分配  ) 和 (  收集　 )。

二、单项选择题
(　C　 )  1. 内部排序和外部排序的区别不在于         。  
A、待排序文件的大小  B、有无内外存的交换  C、是否在内存中排序  D、可采用的排序策略

（  C  ）2．排序方法中，从未排序序列中依次取出元素与已排序序列（初
始时为空）中的元素进行比较，将其放入已排序序列的正确位置上
的方法，称为      。
Ａ. 希尔排序  Ｂ. 冒泡排序   Ｃ. 插入排序   Ｄ. 选择排序

（  D  ）3． 排序方法中，从未排序序列中挑选元素，并将其依次插入已排序序列（初始时为空）的一端的方法，称为     。
Ａ. 希尔排序  Ｂ. 归并排序   Ｃ. 插入排序   Ｄ. 选择排序

（  C  ）4．快速排序在下列哪种情况下最易发挥其长处。
Ａ.  被排序的数据中含有多个相同排序码   Ｂ. 被排序的数据已基本有序  Ｃ.  被排序的数据完全无序    Ｄ. 被排序的数据中的最大值和最小值相差悬殊

（  B  ）5．对有n个记录的表作快速排序，在最坏情况下，算法的时间复杂度是        。
A．O(n)    B．O(n2)    C．O(nlog2n)     D．O(n3)

（  D ）6．在最好情况下，下列排序算法中      排序算法所需比较关键字次数最少。
A．冒泡    B．归并     C．快速     D．直接插入                          

（  D  ）7．下列关键字序列中，       是堆。
Ａ. 16,72,31,23,94,53      Ｂ. 94, 23, 31, 72, 16, 53     
Ｃ. 16, 53, 23,94,31, 72     Ｄ. 16, 23, 53, 31, 94, 72

（  B  ）8．堆是一种       排序。
Ａ. 插入       Ｂ. 选择       Ｃ. 交换       Ｄ. 归并

（  C  ）9．堆的形状是一棵       。
Ａ. 二叉排序树  Ｂ.满二叉树   Ｃ. 完全二叉树  Ｄ. 平衡二叉树

（  B  ）10．若一组记录的排序码为（46, 79, 56, 38, 40, 84），则利用堆排序的方法建立的初始最大值堆为       。
Ａ. 79, 46, 56, 38, 40, 84       Ｂ. 84, 79, 56, 38, 40, 46       
Ｃ. 84, 79, 56, 46, 40, 38       Ｄ. 84, 56, 79, 40, 46, 38 
(　D   )  11. 下列四种排序方法中，不稳定的方法是       .
A、直接插入排序　B、冒泡排序　C、归并排序　D、直接选择排序
(　D   ) 12. 下面排序方法中，关键字比较次数与记录的初始排序无关的______。
A、希尔排序　B、冒泡排序　C、直接插入排序　D、直接选择排序
(　A   ) 13. 在文件“局部有序”或文件长度较小的情况下，最佳内部排序方法是______。
A、直接插入排序　B、冒泡排序　C、直接选择排序　D、归并排序
(　C   ) 14. 在下列算法中，______算法可能出现下列情况：在最后一趟开始之前，所有元素都不在其最终位置上。
A、堆排序　B、冒泡排序　C、直接插入排序　D、快速排序
(　A   ) 15. 快速排序在最坏情况下时间复杂度是O(n2)，比______的性能差。
A、堆排序　B、冒泡排序　C、选择排序　
(　A   ) 16. 就排序算法所用的辅助空间而言，堆排序、快速排序、归并排序的关系是_______。
A、堆排序<快速排序<归并排序　B、堆排序<归并排序<快速排序　
C、堆排序>归并排序>快速排序  D、堆排序>快速排序>归并排序
E、以上答案都不对
(　D   ) 17. 在下列排序算法中，关键字比较次数与记录的初始排列无关的是______。
A、希尔排序　B、冒泡排序　C、直接插入排序　D、直接选择排序
 (　C   ) 18. 对记录的关键字集合key={50, 26, 38, 80, 70, 90, 8, 30, 40, 20}进行排序，各趟排序结束时的结果为：
      50  26  38  80  70  90  8   30  40  20
      50  8   30  40  20  90  26  38  80  70
      26  8   30  40  20  80  50  38  90  70
       8   20  26  30  38  40  50  70  80  90
其使用的排序方法是______。
A、快速排序　B、基数排序　C、希尔排序　D、归并排序
(　C   ) 19. 用某种排序方法对序列（25，84，21，47，15，27，68，35，20）进行排序，记录序列的变化情况如下：
25   84   21   47   15   27   68   35   20
15   20   21   25   47   27   68   35   84
15   20   21   25   35   27   47   68   84
15   20   21   25   27   35   47   68   84
则采取的排序方法是 _________。
   A. 直接选择排序       B. 冒泡排序         C. 快速排序         D. 归并排序

三、简答题
1. 设有1000个无序的元素，希望用最快的速度挑选出其中前10个最大的元素，最好采用哪种排序方法？
答：用堆排序最合适，因为不必等全部元素排完就能得到所需结果，时间效率为O(nlog2n)。

四、以关键字序列（256，301，751，129，937，863，742，694，076，438）为例，分别写出执行以下算法的各趟排序结束时，关键字序列的状态？
① 直接插入排序   ② 希尔排序   ③冒泡排序  ④快速排序
⑤直接选择排序 ⑥ 堆排序      ⑦ 归并排序   ⑧ 基数排序       
解：
(1)直接插入排序:(方括号表示无序区)
　　初始态: 265[301 751 129 937 863 742 694 076 438]
　　第一趟：265 301[751 129 937 863 742 694 076 438]
　　第二趟：265 301 751[129 937 863 742 694 076 438]
　　第三趟：129 265 301 751[937 863 742 694 076 438]
　　第四趟：129 265 301 751 937[863 742 694 076 438]
　　第五趟：129 265 301 751 863 937[742 694 076 438]
　　第六趟：129 265 301 742 751 863 937[694 076 438]
　　第七趟：129 265 301 694 742 751 863 937[076 438]
　　第八趟：076 129 265 301 694 742 751 863 937[438]
第九趟：076 129 265 301 438 694 742 751 863 937 

　(2)希尔排序(增量为5，3，1)
　　初始态: 265 301 751 129 937 863 742 694 076 438
　　第一趟：265 301 694 076 438 863 742 751 129 937 
　　第二趟：076 301 129 265 438 694 742 751 863 937 
第三趟：076 129 265 301 438 694 742 751 863 937 

　(3)冒泡排序(方括号为无序区)
　　初始态 [265 301 751 129 937 863 742 694 076 438]
　　第一趟： 076 [265 301 751 129 937 863 742 694 438]
　　第二趟： 076 129 [265 301 751 438 937 863 742 694]
　　第三趟： 076 129 265 [301 438 694 751 937 863 742]
　　第四趟： 076 129 265 301 [438 694 742 751 937 863]
　　第五趟： 076 129 265 301 438 [694 742 751 863 937]
第六趟： 076 129 265 301 438 694 742 751 863 937

　(4)快速排序：（方括号表示无序区，层表示对应的递归树的层数）
    初始态： [265 301 751 129 937 863 742 694 076 438]
　　第二层： [076 129] 265 [751 937 863 742 694 301 438]
　　第三层： 076 [129] 265 [438 301 694 742] 751 [863 937]
　　第四层： 076 129 265 [301] 438 [694 742] 751 863 [937]
　　第五层： 076 129 265 301 438 694 [742] 751 863 937
第六层： 076 129 265 301 438 694 742 751 863 937

　(5)直接选择排序：(方括号为无序区)
　　初始态 　[265 301 751 129 937 863 742 694 076 438]
　　第一趟： 076 [301 751 129 937 863 742 694 265 438]
　　第二趟： 076 129 [751 301 937 863 742 694 265 438]
　　第三趟： 076 129 265[ 301 937 863 742 694 751 438]
　　第四趟： 076 129 265 301 [937 863 742 694 751 438]
　　第五趟： 076 129 265 301 438 [863 742 694 751 937]
　　第六趟： 076 129 265 301 438 694 [742 751 863 937]
　　第七趟： 076 129 265 301 438 694 742 [751 863 937]
　　第八趟： 076 129 265 301 438 694 742 751 [937 863]
第九趟： 076 129 265 301 438 694 742 751 863 937

　(6)堆排序：（通过画二叉树可以一步步得出排序结果）
　　    初始态 　　　[265 301 751 129 937 863 742 694 076 438]
　　　　建立初始堆： [937 694 863 265 438 751 742 129 075 301]
　第一次排序重建堆：[863 694 751 765 438 301 742 129 075] 937
　第二次排序重建堆：[751 694 742 265 438 301 075 129] 863 937
　第三次排序重建堆：[742 694 301 265 438 129 075] 751 863 937
　第四次排序重建堆：[694 438 301 265 075 129] 742 751 863 937
　第五次排序重建堆：[438 265 301 129 075] 694 742 751 863 937
　第六次排序重建堆：[301 265 075 129] 438 694 742 751 863 937
　第七次排序重建堆：[265 129 075] 301 438 694 742 751 863 937
　第八次排序重建堆：[129 075]265 301 438 694 742 751 863 937
　第九次排序重建堆：075 129 265 301 438 694 742 751 863 937

　(7)归并排序（为了表示方便，采用自底向上的归并，方括号为有序区，当n为奇数时，mid=n/2取上限）
  　　初始态：[265] [301] [751] [129] [937] [863] [742] [694] [076] [438]
　　第一趟：[265 301] [751] [129 937] [742 863] [694] [076 438]
　　第二趟：[265 301 751] [129 937] [694 742 863] [076 438]
　　第三趟：[129 265 301 751 937] [076 438 694 742 863]
第四趟：[076 129 265 301 438 694 742 751 863 937]

　(8)基数排序（方括号内表示一个箱子共有10个箱子，箱号从0到9）
    　初始态：265 301 751 129 937 863 742 694 076 438
   　 第一趟：[] [301 751] [742] [863] [694] [265] [076] [937] [438] [129]
　　第二趟：[301] [] [129] [937 438] [742] [751] [863 265] [076] [] [694]
　　第三趟：[075] [129] [265] [301] [438] [] [694] [742 751] [863] [937] 
　　在上面的排序方法中，直接插入排序、冒泡排序、归并排序和基数排序是稳定的，其他排序算法均是不稳定的
