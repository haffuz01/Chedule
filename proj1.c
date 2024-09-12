#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct job
{
	bool arrived;
	int process;
	int burst;
	int arrival;
	int priority;
};

struct job *get_jobs(int size, struct job *);

void schedule_fcfs(int SIZE, struct job *);
void schedule_sjf(int SIZE, struct job *);
void schedule_pre_sjf(int SIZE, struct job *);
void schedule_priority(int SIZE, struct job *);
void schedule_rr(int SIZE, struct job *);

int main(void)
{
	// Get number of jobs
	printf("How many processes would you like to schedule? ");
	int job_size;
	scanf("%d", &job_size);

	const int SIZE = job_size;
	struct job jobs_empty[SIZE];

	struct job *jobs;
	jobs = get_jobs(SIZE, jobs_empty);

	// Get algorithm choice
	char algo[20];
	printf("\nPlease input the algorithm you want to use.\n");
	scanf("%s", &algo);

	// Print all jobs
	printf("\n------------------");
	printf("\nJob\tBurst\tArrival\tPriority\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("P%d\t  %d\t   %d\t   %d\n", jobs[i].process, jobs[i].burst, jobs[i].arrival, jobs[i].priority);
	}

	while (true)
	{
		if (!strcasecmp(algo, "FCFS") || !strcmp(algo, "1"))
		{
			// printf("FCFS selected");
			schedule_fcfs(SIZE, jobs);
			break;
		}
		else if (!strcasecmp(algo, "SJF") || !strcmp(algo, "2"))
		{
			// printf("SJF selected");
			schedule_sjf(SIZE, jobs);
			break;
		}
		else if (!strcasecmp(algo, "Pre SJF") || !strcmp(algo, "3"))
		{
			// printf("Pre SJF selected");
			schedule_pre_sjf(SIZE, jobs);
			break;
		}
		else if (!strcasecmp(algo, "Priority") || !strcmp(algo, "4"))
		{
			// printf("Priority selected");
			schedule_priority(SIZE, jobs);
			break;
		}
		else if (!strcasecmp(algo, "RR") || !strcmp(algo, "5"))
		{
			// printf("RR selected");
			schedule_rr(SIZE, jobs);
			break;
		}
		else
		{
			printf("Please input a valid algorithm:\n");
			scanf("%s", &algo);
		}
	}

	return 0;
}

struct job *get_jobs(int size, struct job *jobs)
{
	for (int i = 0; i < size; i++)
	{
		jobs[i].process = i;
		printf("\nP%d values:\n", i);

		printf("Burst: ");
		scanf("%d", &jobs[i].burst);
		printf("Arrival: ");
		scanf("%d", &jobs[i].arrival);
		printf("Priority: ");
		scanf("%d", &jobs[i].priority);
	}
	return jobs;
}

void schedule_fcfs(int size, struct job *jobs)
{

	struct job jobs_temp[size];
	int smallest_index = 0;

	for (int i = 0; i < size; i++)
	{
		jobs_temp[i] = jobs[i];
	}

	printf("\n>> Accepted Jobs [%d]", size);
	printf("\n>> Algorithm: First Come First Serve\n");
	printf("\nSchedule:\n");

	for (int i = 0; i < size; i++)
	{
		for (int i = 0; i < size; i++)
		{
			if (jobs_temp[i].arrival < jobs_temp[smallest_index].arrival)
			{
				smallest_index = i;
			}
		}

		printf("P%d", jobs_temp[smallest_index].process);
		for (int i = 0; i < jobs_temp[smallest_index].burst; i++)
		{
			printf(" .");
		}
		printf(" | ");

		jobs_temp[smallest_index].arrival = 9999;
	}

	printf("\n-----------------\n");
}

void schedule_sjf(int size, struct job *jobs)
{

	int shortest_burst = 0;

	struct job jobs_temp[size];
	for (int i = 0; i < size; i++)
	{
		jobs_temp[i] = jobs[i];
	}

	printf("\n>> Accepted Jobs [%d]", size);
	printf("\n>> Algorithm: Shortest job first");
	printf("\nSchedule:\n");

	int total_burst = 0;
	for (int i = 0; i < size; i++)
	{
		total_burst += jobs_temp[i].burst;
	}

	int time_running = 0;
	while (time_running < total_burst)
	{

		int arrived_counter = 0;
		int arrived_jobs_indice[size];
		for (int i = 0; i < size; i++)
		{
			arrived_jobs_indice[i] = 93;
		}

		for (int i = 0; i < size; i++)
		{
			if (jobs_temp[i].arrival <= time_running)
			{
				arrived_jobs_indice[arrived_counter] = i;
			}
			arrived_counter++;
		}

		shortest_burst = arrived_jobs_indice[0];
		for (int i = 0; i < (sizeof(arrived_jobs_indice) / sizeof(int)); i++)
		{
			if (arrived_jobs_indice[i] == 93)
				continue;
			else if (jobs_temp[arrived_jobs_indice[i]].burst < jobs_temp[shortest_burst].burst)
				shortest_burst = arrived_jobs_indice[i];
		}

		if (jobs_temp[shortest_burst].arrival > time_running || jobs_temp[shortest_burst].burst == 9999 || shortest_burst == 93)
		{
			time_running += 1;
			continue;
		}

		printf("P%d ", jobs_temp[shortest_burst].process);
		for (int i = 0; i < jobs_temp[shortest_burst].burst; i++)
		{
			printf(". ");
		}
		printf("| ");
		time_running += jobs_temp[shortest_burst].burst;
		jobs_temp[shortest_burst].burst = 9999;
	}

	printf("\n-----------------\n");
}

void schedule_pre_sjf(int size, struct job *jobs)
{

	int shortest_remaining = 0;
	int last_shortest = 9999;

	struct job jobs_temp[size];
	for (int i = 0; i < size; i++)
	{
		jobs_temp[i] = jobs[i];
	}

	printf("\n>> Accepted Jobs [%d]", size);
	printf("\n>> Algorithm: Preemptive Shortest job first");
	printf("\nSchedule:\n");

	int total_burst = 0;
	for (int i = 0; i < size; i++)
	{
		total_burst += jobs_temp[i].burst;
	}

	int time_running = 0;
	while (time_running <= total_burst)
	{

		int arrived_counter = 0;
		for (int i = 0; i < size; i++)
		{
			if (jobs_temp[i].arrival <= time_running)
			{
				jobs_temp[i].arrived = true;
				arrived_counter++;
			}
			else
				jobs_temp[i].arrived = false;
		}

		for (int i = 0; i < size; i++)
		{
			if (jobs_temp[i].arrived)
			{
				shortest_remaining = i;
				break;
			}
		}
		for (int i = 0; i < size; i++)
		{
			if ((jobs_temp[i].burst < jobs_temp[shortest_remaining].burst) && (jobs_temp[i].burst != 0) && jobs_temp[i].arrived)
			{
				shortest_remaining = i;
			}
		}

		if (shortest_remaining != last_shortest && jobs_temp[shortest_remaining].arrived)
		{
			printf("P%d ", jobs_temp[shortest_remaining].process);
		}
		if (jobs_temp[shortest_remaining].arrived)
		{
			printf(". ");
			jobs_temp[shortest_remaining].burst -= 1;
		}
		if (jobs_temp[shortest_remaining].burst <= 1 && jobs_temp[shortest_remaining].arrived)
		{
			printf("| ");
			jobs_temp[shortest_remaining].burst = 9999;
		}
		last_shortest = shortest_remaining;
		time_running += 1;
	}

	printf("\n-----------------\n");
}

void schedule_priority(int size, struct job *jobs)
{

	struct job jobs_temp[size];
	int smallest_index = 0;

	for (int i = 0; i < size; i++)
	{
		jobs_temp[i] = jobs[i];
	}

	printf("\n>> Accepted Jobs [%d]", size);
	printf("\n>> Algorithm: Priority\n");
	printf("\nSchedule:\n");

	for (int i = 0; i < size; i++)
	{
		for (int i = 0; i < size; i++)
		{
			if (jobs_temp[i].priority < jobs_temp[smallest_index].priority)
			{
				smallest_index = i;
			}
		}

		printf("P%d", jobs_temp[smallest_index].process);
		for (int i = 0; i < jobs_temp[smallest_index].burst; i++)
		{
			printf(" .");
		}
		printf(" | ");

		jobs_temp[smallest_index].priority = 9999;
	}

	printf("\n-----------------\n");
}

void schedule_rr(int size, struct job *jobs)
{
	int round_ammount = 3;

	struct job jobs_temp[size];
	for (int i = 0; i < size; i++)
	{
		jobs_temp[i] = jobs[i];
	}

	printf("\n>> Accepted Jobs [%d]", size);
	printf("\n>> Algorithm: Round robin");
	printf("\nSchedule:\n");

	int total_burst = 0;
	for (int i = 0; i < size; i++)
	{
		total_burst += jobs_temp[i].burst;
	}

	int time_running = 0;

	while (time_running <= total_burst)
	{
		time_running++;

		for (int i = 0; i < size; i++)
		{
			if (jobs_temp[i].arrival < time_running && jobs_temp[i].burst > 0)
			{
				jobs_temp[i].arrived = true;
				printf("P%d ", jobs_temp[i].process);
				for (int j = 0; j < round_ammount; j++)
				{
					if (jobs_temp[i].burst > 0)
					{
						printf(". ");
						jobs_temp[i].burst--;
					}
				}
				printf("| ");
			}
			else
				jobs_temp[i].arrived = false;
		}
	}
}
