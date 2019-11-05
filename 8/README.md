# Homework (Simulation)
This program, mlfq.py, allows you to see how the MLFQ scheduler presented in this chapter behaves. See the README for details.
## Questions
1. Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.
2. How would you run the scheduler to reproduce each of the examples in the chapter?
    - 8.2: ./mlfq.py -s -a 1 -S
    - 8.3: ./mlfq.py -s -a 1 -S -N
    - 8.4: ./mlfq.py -s -a -N
3. How would you configure the scheduler parameters to behave just like a round-robin scheduler?
    ./mlfq.py -l 0,20,4:0,20,4 -q 5 -a 1 -S
4. Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.
    ./mlfq.py -l 0,99,98:0,1,0 -q 100 -a 1 -S -i 0
5. Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single longrunning (and potentially-starving) job gets at least 5% of the CPU?
    
6. One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.
    - back in the queue without -I flag
    - front in the queue with -I flag