# Homework (Code)
In this section, we’ll write some simple multi-threaded programs and use a specific tool, called helgrind, to find problems in these programs. Read the README in the homework download for details on how to build the programs and run helgrind.
## Questions
1. First build main-race.c. Examine the code so you can see the (hopefully obvious) data race in the code. Now run helgrind (by typing valgrind --tool=helgrind main-race) to see how it reports the race. Does it point to the right lines of code? What other information does it give to you?
> ==3634== Helgrind, a thread error detector
> ==3634== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
> ==3634== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
> ==3634== Command: ./main-race
> ==3634== 
> ==3634== ---Thread-Announcement------------------------------------------
> ==3634== 
> ==3634== Thread #1 is the program's root thread
> ==3634== 
> ==3634== ---Thread-Announcement------------------------------------------
> ==3634== 
> ==3634== Thread #2 was created
> ==3634==    at 0x518287E: clone (clone.S:71)
> ==3634==    by 0x4E49EC4: create_thread (createthread.c:100)
> ==3634==    by 0x4E49EC4: pthread_create@@GLIBC_2.2.5 (pthread_create.c:797)
> ==3634==    by 0x4C36E33: pthread_create_WRK (hg_intercepts.c:427)
> ==3634==    by 0x4C37F25: pthread_create@* (hg_intercepts.c:460)
> ==3634==    by 0x108C54: Pthread_create (mythreads.h:51)
> ==3634==    by 0x108D26: main (main-race.c:14)
> ==3634== 
> ==3634== ----------------------------------------------------------------
> ==3634== 
> ==3634== Possible data race during read of size 4 at 0x30A014 by thread #1
> ==3634== Locks held: none
> ==3634==    at 0x108D27: main (main-race.c:15)
> ==3634== 
> ==3634== This conflicts with a previous write of size 4 by thread #2
> ==3634== Locks held: none
> ==3634==    at 0x108CDF: worker (main-race.c:8)
> ==3634==    by 0x4C37027: mythread_wrapper (hg_intercepts.c:389)
> ==3634==    by 0x4E496DA: start_thread (pthread_create.c:463)
> ==3634==    by 0x518288E: clone (clone.S:95)
> ==3634==  Address 0x30a014 is 0 bytes inside data symbol "balance"
> ==3634== 
> ==3634== ----------------------------------------------------------------
> ==3634== 
> ==3634== Possible data race during write of size 4 at 0x30A014 by thread #1
> ==3634== Locks held: none
> ==3634==    at 0x108D30: main (main-race.c:15)
> ==3634== 
> ==3634== This conflicts with a previous write of size 4 by thread #2
> ==3634== Locks held: none
> ==3634==    at 0x108CDF: worker (main-race.c:8)
> ==3634==    by 0x4C37027: mythread_wrapper (hg_intercepts.c:389)
> ==3634==    by 0x4E496DA: start_thread (pthread_create.c:463)
> ==3634==    by 0x518288E: clone (clone.S:95)
> ==3634==  Address 0x30a014 is 0 bytes inside data symbol "balance"
> ==3634== 
> ==3634== 
> ==3634== Use --history-level=approx or =none to gain increased speed, at
> ==3634== the cost of reduced accuracy of conflicting-access information
> ==3634== For lists of detected and suppressed errors, rerun with: -s
> ==3634== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

   - Yes
   - Share source address and size
2. What happens when you remove one of the offending lines of code? Now add a lock around one of the updates to the shared variable, and then around both. What does helgrind report in each of these cases?
    - Avoid data race
    - main-race still exist data race after adding a lock around one, both are fine
3. Now let’s look at main-deadlock.c. Examine the code. This code has a problem known as deadlock (which we discuss in much more depth in a forthcoming chapter). Can you see what problem it might have?
4. Now run helgrind on this code. What does helgrind report?
    - Thread #3: lock order "0x30A040 before 0x30A080" violated
5. Now run helgrind on main-deadlock-global.c. Examine the code; does it have the same problem that main-deadlock.c has? Should helgrind be reporting the same error? What does this tell you about tools like helgrind?
    - Yes
    - No
    - The tools like helgrind are not perfect
6. Let’s next look at main-signal.c. This code uses a variable (done) to signal that the child is done and that the parent can now continue. Why is this code inefficient? (what does the parent end up spending its time doing, particularly if the child thread takes a long time to complete?)
    - Because the main thread use cpu time slice to execute invalid check operation (invalid chek operation in this context mean that the check will get unexpect result)
7. Now run helgrind on this program. What does it report? Is the code correct?
    - Possible data race of write/read done and printf()
    - No
8. Now look at a slightly modified version of the code, which is found in main-signal-cv.c. This version uses a condition variable to do the signaling (and associated lock). Why is this code preferred to the previous version? Is it correctness, or performance, or both?
    - Because this code avoid invalid check by sleep the routine, it will quit schduled queue, save cpu time slice and improve performance
9.  Once again run helgrind on main-signal-cv. Does it report any errors?
    - No