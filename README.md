The current project is a classic task about dining philosophers. In fisrt and second cases threads are used, while in the first it is realised with mutexes, in the second one it is realised with semaphores. In the third variant processess and semaphores are used.
To test a program use an executables in each folder (Makefile is presented and default rule builds the project). 
Arguments used by each program in order:
◦number_of_philosophers: is the number of philosophers and also 
the number of forks
◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting his last meal or the beginning of the simulation, it
dies
◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time he will need to keep the two forks.
◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.
◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.
Works on MacOs (on Linux systems may have problems).
