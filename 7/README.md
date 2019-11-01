# Homework (Simulation)
This program, *scheduler.py*, allows you to see how different schedulers perform under scheduling metrics such as response time, turnaround time, and total wait time. See the README for details.
## Questions
1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers.
    - FIFO
      - response time
        - job0: 0
        - job1: 200
        - job2: 400
      - turnaroud time
        - job0: 200
        - job1: 400
        - job2: 600
    - SJF
      - response time
        - job0: 0
        - job1: 200
        - job2: 400
      - turnaround time
        - job0: 200
        - job1: 400
        - job2: 600
2. Now do the same but with jobs of different lengths: 100, 200, and 300.
    - FIFO
      - response time
        - job0: 0
        - job1: 100
        - job2: 300
      - turnaroud time
        - job0: 100
        - job1: 300
        - job2: 600
    - SJF
      - response time
        - job0: 0
        - job1: 100
        - job2: 300
      - turnaround time
        - job0: 100
        - job1: 300
        - job2: 600
3. Now do the same, but also with the RR scheduler and a time-slice
of 1.
    - RR
      - response time
        - job0: 0
        - job1: 1
        - job2: 2
      - turnaroud time
        - job0: 298
        - job1: 499
        - job2: 600
4. For what types of workloads does SJF deliver the same turnaround times as FIFO?
    - The time length of jobs are same
    - The time length of jobs are in the same order as FIFO
    - **Jobs are in ascending order by length.*
5. For what types of workloads and quantum lengths does SJF deliver the same response times as RR?
    - Time length of jobs are less than or equal to time slice of rr
6. What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?
    - The response time with SJF will increase with job lengths increasing
7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?
    - The response time with RR will increase with quantum lengths increasing
    - Suppose q is quantum length(time slice), rt(worst) = (N-1) * q