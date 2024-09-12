# Chedule
## What it is
Process scheduling algorithm simulator written in c. This is a sample project made for educational purposes. It could be useful for learning and understanding the following process scheduling algorithms.
1. First come first serve
2. Shortest job first
3. Preemptive shortest job first
4. Priority, and
5. Round robin
## What it does
This is roughly the steps the program takes during execution
- Accept what number of processes the user would like to schedule
- Create that number of jobs (jobs are a struct with attributes active:bool type, [process, burst, arrival, and priority]:int types)
- Asks and accepts from the user the attributes of each job created
- Accept the users choice of algorithm, 1 through 5 also representing the algorithms in respective order
- Pass on the jobs to the selected algorithms function
- Each function then schedules the jobs and prints the result in a readable view
## How to run it
To run this code in your machine ensure you have either ```gcc``` or ```clang``` compilers in your system (they usually come built in on macos and linux)
- Clone the repository or just download the zip and extract the ```Cheduler.c``` file in to a directory of your choosing
- ```cd``` in to the directory containing the ```Cheduler.c``` file and
- Run the command ```gcc Cheduler.c -o Cheduler``` or ```clang Cheduler.c -o Cheduler```
- Run the executable outputted by the above command ``./Cheduler``
## Sample outputs
1. Sample one
<img width="449" alt="Screen Shot 2024-09-12 at 6 14 07 PM" src="https://github.com/user-attachments/assets/6b578b5c-92ee-4555-91c6-353e772346dd">

2. Sample two
<img width="537" alt="Screen Shot 2024-09-12 at 6 15 50 PM" src="https://github.com/user-attachments/assets/b8a2995c-0a56-468a-a482-257ac61c1f34">
