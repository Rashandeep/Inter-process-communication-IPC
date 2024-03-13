#include <bits/stdc++.h>
#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

// Function to generate a random number within a given range [min, max]
int generateRandomNumber(int min, int max)
{
	// Declare variables for storing random numbers and calculations
	unsigned int r;	   // Range of numbers (max - min + 1)
	unsigned int maxR; // Maximum acceptable random value to ensure uniform distribution
	unsigned int rand; // Placeholder for random number read from /dev/urandom

	// Open /dev/urandom to read random bytes
	ifstream urandom("/dev/urandom");

	// Calculate range and maximum acceptable random value
	r = max - min + 1;
	maxR = (RAND_MAX / r) * r; // Ensuring even distribution within the range

	// Calculate size of rand variable in bytes
	int size = sizeof(rand);

	// Loop until a suitable random number is generated
	do
	{
		// Read random bytes from /dev/urandom into rand variable
		urandom.read(reinterpret_cast<char *>(&rand), size);
	} while (rand >= maxR); // Continue until rand falls within acceptable range

	// Close /dev/urandom after random number generation
	urandom.close();

	// Return generated random number within specified range [min, max]
	return min + (rand % r);
}

// funtion to catch a signal to check which process got finished first and return the pid
pid_t catchTheSignal(int &status, int p1, int p2)
{
	pid_t pid = 0;
	do
	{
		while ((pid = waitpid(WAIT_ANY, &status, 0)) == -1)
		{
			if (errno == EINTR)
			{
				continue;
			}
			else
			{

				abort();
			}
		}
	} while (pid != p1 && pid != p2);
	return pid;
}

void sig_usr(int signo)
{
	if (signo == SIGALRM)
		cout << "Error: failed to generate valid input for 25 simultaneous attempts" << endl;
	exit(0);
}

int main(int argc, char *argv[])
{

	if (signal(SIGALRM, sig_usr) == SIG_ERR)
		printf("Signal processed ");

	// variables that we will we will be taking from command line
	int option;
	char *numberOfStreets;
	char *noOfLines;
	char *waitSeconds;
	char *cordRange;
	int inumberOfStreets, inoOfLines, iwaitSeconds = 5, icordRange;

	// declaring values for 2 ends of the pipe
	int read_end = 0;
	int write_end = 1;

	// declaring 2 pipes.
	// 2 pipes because we will be communication between 3 programs - rgen, a1ece650 and a2ece650
	int fds[2];
	pipe(fds);

	int fds1[2];
	pipe(fds1);

	// Loop through command line arguments using getopt function
	while ((option = getopt(argc, argv, ":s:n:l:c:")) != -1)
	{
		// Switch statement to handle different options
		switch (option)
		{
		case 's':									  // Option for specifying the number of streets
			numberOfStreets = optarg;				  // Get the argument value for number of streets
			inumberOfStreets = stoi(numberOfStreets); // Convert string to integer
			if (inumberOfStreets < 2)				  // Check if number of streets is less than 2
			{
				cout << "Error: No. of streets should be greater than or equal to 2" << endl; // Print error message
				exit(0);																	  // Exit the program
			}
			break;
		case 'n':						  // Option for specifying the number of line segments
			noOfLines = optarg;			  // Get the argument value for number of line segments
			inoOfLines = stoi(noOfLines); // Convert string to integer
			if (inoOfLines < 1)			  // Check if number of line segments is less than 1
			{
				cout << "Error: No. of line segments should be greater than or equal to 1" << endl; // Print error message
				exit(0);																			// Exit the program
			}
			break;
		case 'l':							  // Option for specifying the wait seconds
			waitSeconds = optarg;			  // Get the argument value for wait seconds
			iwaitSeconds = stoi(waitSeconds); // Convert string to integer
			if (iwaitSeconds < 5)			  // Check if wait seconds is less than 5
			{
				cout << "Error: wait seconds should be greater than or equal to 5" << endl; // Print error message
				exit(0);																	// Exit the program
			}
			break;
		case 'c':						  // Option for specifying the coordinate range
			cordRange = optarg;			  // Get the axrgument value for coordinate range
			icordRange = stoi(cordRange); // Convert string to integer
			if (icordRange < 1)			  // Check if coordinate range is less than 1
			{
				cout << "Error: cord range should be greater than or equal to 1" << endl; // Print error message
				exit(0);																  // Exit the program
			}
			break;
		default:
			cout << "Invalid argument" << endl; // Print error message for invalid argument
			exit(0);							// Exit the program
			break;
		}
	}

	int rangewait = generateRandomNumber(5, iwaitSeconds);

	while (1)
	{
		// forking the parent
		pid_t rgenChild = fork();
		// if the process is child
		if (rgenChild == 0)
		{
			// connecting the stdout to write end of a pipe
			dup2(fds[write_end], STDOUT_FILENO);
			// closing the ends of pipe
			close(fds[read_end]);
			close(fds[write_end]);

			char *command = "./rgen";
			// giving control to the other program replacing the current program
			int coding = execvp(command, argv);
			// if fails, then print error message and return
			if (coding == -1)
			{
				cout << "Process did not terminate correctly\n";
				exit(1);
			}
		}
		// parent process
		else
		{
			// forking the parent
			pid_t a1Child = fork();
			int child1;
			// for the child process
			if (a1Child == 0)
			{
				// waiting for the first child to get over
				waitpid(rgenChild, &child1, 0);
				// connecting the stdin from read end of a pipe
				dup2(fds[read_end], STDIN_FILENO);
				// connecting the stdout of this to write end of other pipe
				dup2(fds1[write_end], STDOUT_FILENO);
				// closing the ends of the pipe
				close(fds[read_end]);
				close(fds[write_end]);
				close(fds1[read_end]);
				close(fds1[write_end]);
				// giving control to the other program replacing the current program
				char *command = "python3";
				char *argument_list[] = {"python3", "a1ece650.py", NULL};

				int coding = execvp(command, argument_list);
				// if fails, then print error message and return
				if (coding == -1)
				{
					cout << "Process did not terminate correctly\n";
					exit(1);
				}
			}
			// parent process
			else
			{
				// forking the parent process. This is done because the program repeats itself after certain time.
				// If the programmer forfully quits the program, the full program should end.
				const pid_t timeChild = fork();
				// making the child sleep
				if (timeChild == 0)
				{
					usleep(rangewait * 1000000);
					exit(0);
				}
				// forking process to run the 3rd program
				pid_t a2Child = fork();
				int child2;
				// if child
				if (a2Child == 0)
				{
					// wait for a1child to run completing
					waitpid(a1Child, &child2, 0);
					// get the data from stdin
					string plz = to_string(dup(STDIN_FILENO));
					int pli = stoi(plz);
					// connect it to the read end
					dup2(fds1[read_end], STDIN_FILENO);
					// close both the ends of pipe
					close(fds1[write_end]);
					close(fds1[read_end]);

					char *gamma = new char[plz.length() + 1];
					strcpy(gamma, plz.c_str());
					// giving control to the other program replacing the current program
					char *command = "./a2ece650";
					char *argument_list[] = {"./a2ece650", gamma, NULL};
					int coding = execv(command, argument_list);
					// if fails, then print error message and return
					if (coding == -1)
					{
						cout << "Process did not terminate correctly\n";
						exit(1);
					}
				}
				// finally the parent process
				else
				{

					int status = 0;
					// checking if the timechild finished first and a2 child finished first.
					// if timechild finished first, it means the program will run again.
					// if a2child finished first, it means the programmer forcefully wants to quit and we will exit()
					const pid_t finished_first = catchTheSignal(status, timeChild, a2Child);
					if (finished_first == timeChild)
					{
						// killing the childs
						kill(a1Child, SIGKILL);
						kill(rgenChild, SIGKILL);
						kill(a2Child, SIGKILL);
					}
					else if (finished_first == a2Child)
					{
						// killing the child and exiting.
						kill(a1Child, SIGKILL);
						kill(rgenChild, SIGKILL);
						kill(a2Child, SIGKILL);
						kill(timeChild, SIGKILL);
						exit(0);
					}
				}
			}
		}
	}
}
