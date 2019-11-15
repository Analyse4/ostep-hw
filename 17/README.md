# Homework (Simulation)
The program, malloc.py, lets you explore the behavior of a simple free-space allocator as described in the chapter. See the README for details of its basic operation.
## Questions
1. First run with the flags -n 10 -H 0 -p BEST -s 0 to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time?
    ptr[0] = Alloc(3)  returned 1000 (searched 1 elements)
    Free List [ Size 1 ]:  [ addr:1003 sz:97 ]
    Free(ptr[0]) returned 0
    Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]
    ptr[1] = Alloc(5)  returned 1003 (searched 2 elements)
    Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]
2. How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes?
3. What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit?
4. For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings (-l ADDRSORT, -l SIZESORT+, -l SIZESORT-) to see how the policies and the list orderings interact.
    - There is no effect to BEST or WORST policy whatever the policies of keeping fress list's order is
    - The SIZESORT- is the best to the FIRST policy
5. Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case?
    - It will failed
    - The free list is longer without coalescing
    - The ADDRSORT is better
6. What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as the percent nears 0?
7. What kind of specific requests can you make to generate a highlyfragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.