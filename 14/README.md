# Homework (Code)
In this homework, you will gain some familiarity with memory allocation. First, you’ll write some buggy programs (fun!). Then, you’ll use some tools to help you find the bugs you inserted. Then, you will realize how awesome these tools are and use them in the future, thus making yourself more happy and productive. The tools are the debugger (e.g., gdb) and a memory-bug detector called valgrind [SN05].
# Questions
1. First, write a simple program called null.c that creates a pointer to an integer, sets it to NULL, and then tries to dereference it. Compile this into an executable called null. What happens when you run this program?
    - Segmentation fault
2. Next, compile this program with symbol information included (with the -g flag). Doing so let’s put more information into the executable, enabling the debugger to access more useful information about variable names and the like. Run the program under the debugger by typing gdb null and then, once gdb is running, typing run. What does gdb show you?
    - Program received signal SIGSEGV, Segmentation fault
3. Finally, use the valgrind tool on this program. We’ll use the memcheck tool that is a part of valgrind to analyze what happens. Run this by typing in the following: valgrind --leak-check=yes null. What happens when you run this? Can you interpret the output from the tool?
```
==28014== Memcheck, a memory error detector
==28014== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28014== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==28014== Command: ./1
==28014==
==28014== Invalid read of size 4
==28014==    at 0x108611: main (1.c:7)
==28014==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==28014==
==28014==
==28014== Process terminating with default action of signal 11 (SIGSEGV)
==28014==  Access not within mapped region at address 0x0
==28014==    at 0x108611: main (1.c:7)
==28014==  If you believe this happened as a result of a stack
==28014==  overflow in your program's main thread (unlikely but
==28014==  possible), you can try to increase the size of the
==28014==  main thread stack using the --main-stacksize= flag.
==28014==  The main thread stack size used in this run was 8388608.
==28014==
==28014== HEAP SUMMARY:
==28014==     in use at exit: 0 bytes in 0 blocks
==28014==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==28014==
==28014== All heap blocks were freed -- no leaks are possible
==28014==
==28014== For lists of detected and suppressed errors, rerun with: -s
==28014== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
Segmentation fault
```
4. Write a simple program that allocates memory using malloc() but forgets to free it before exiting. What happens when this program runs? Can you use gdb to find any problems with it? How about valgrind (again with the --leak-check=yes flag)?
*gdb*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# gdb 4
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from 4...done.
(gdb) run
Starting program: /root/ostep-hw/14/4
[Inferior 1 (process 28319) exited normally]
```
*valgrind*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# valgrind --leak-check=yes ./4
==28326== Memcheck, a memory error detector
==28326== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28326== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==28326== Command: ./4
==28326==
==28326==
==28326== HEAP SUMMARY:
==28326==     in use at exit: 4 bytes in 1 blocks
==28326==   total heap usage: 1 allocs, 0 frees, 4 bytes allocated
==28326==
==28326== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==28326==    at 0x4C2FDFB: malloc (vg_replace_malloc.c:309)
==28326==    by 0x108662: main (4.c:6)
==28326==
==28326== LEAK SUMMARY:
==28326==    definitely lost: 4 bytes in 1 blocks
==28326==    indirectly lost: 0 bytes in 0 blocks
==28326==      possibly lost: 0 bytes in 0 blocks
==28326==    still reachable: 0 bytes in 0 blocks
==28326==         suppressed: 0 bytes in 0 blocks
==28326==
==28326== For lists of detected and suppressed errors, rerun with: -s
==28326== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
5. Write a program that creates an array of integers called data of size 100 using malloc; then, set data[100] to zero. What happens when you run this program? What happens when you run this program using valgrind? Is the program correct?
*run*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# ./5
arr[100]: 0
```
*gdb*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# gdb 5
GNU gdb (Ubuntu 8.1-0ubuntu3) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from 5...done.
(gdb) run
Starting program: /root/ostep-hw/14/5
arr[100]: 0
[Inferior 1 (process 28367) exited normally]
```
*valgrind*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# valgrind --leak-check=yes ./5
==28373== Memcheck, a memory error detector
==28373== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28373== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==28373== Command: ./5
==28373==
==28373== Invalid read of size 4
==28373==    at 0x108701: main (5.c:8)
==28373==  Address 0x522e1d0 is 224 bytes inside an unallocated block of size 4,194,032 in arena "client"
==28373==
arr[100]: 0
==28373==
==28373== HEAP SUMMARY:
==28373==     in use at exit: 0 bytes in 0 blocks
==28373==   total heap usage: 2 allocs, 2 frees, 1,124 bytes allocated
==28373==
==28373== All heap blocks were freed -- no leaks are possible
==28373==
==28373== For lists of detected and suppressed errors, rerun with: -s
==28373== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
6. Create a program that allocates an array of integers (as above), frees them, and then tries to print the value of one of the elements of the array. Does the program run? What happens when you use
valgrind on it?
    - Yes
*valgrind*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# valgrind --leak-check=yes ./6
==28426== Memcheck, a memory error detector
==28426== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==28426== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==28426== Command: ./6
==28426==
==28426== Invalid read of size 4
==28426==    at 0x108719: main (6.c:10)
==28426==  Address 0x522e054 is 20 bytes inside a block of size 100 free'd
==28426==    at 0x4C30FA8: free (vg_replace_malloc.c:540)
==28426==    by 0x108710: main (6.c:9)
==28426==  Block was alloc'd at
==28426==    at 0x4C2FDFB: malloc (vg_replace_malloc.c:309)
==28426==    by 0x1086F2: main (6.c:7)
==28426==
arr[5]: 44
==28426==
==28426== HEAP SUMMARY:
==28426==     in use at exit: 0 bytes in 0 blocks
==28426==   total heap usage: 2 allocs, 2 frees, 1,124 bytes allocated
==28426==
==28426== All heap blocks were freed -- no leaks are possible
==28426==
==28426== For lists of detected and suppressed errors, rerun with: -s
==28426== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```
7. Now pass a funny value to free (e.g., a pointer in the middle of the array you allocated above). What happens? Do you need tools to find this type of problem?
*run*
```
root@iZwz9a0z1wy5zy1geob36gZ:~/ostep-hw/14# ./7
arr[11]: 44
free(): invalid pointer
Aborted
```
8. Try out some of the other interfaces to memory allocation. For example, create a simple vector-like data structure and related routines that use realloc() to manage the vector. Use an array to store the vectors elements; when a user adds an entry to the vector, use realloc() to allocate more space for it. How well does such a vector perform? How does it compare to a linked list? Use valgrind to help you find bugs.
    - The complexity of adding elements in such vector is O(1) or O(n)(when invoking realloc), but the complexity in linked list is O(1)
9.  Spend more time and read about using gdb and valgrind. Knowing your tools is critical; spend the time and learn how to become an expert debugger in the UNIX and C environment.