# OSAssignment2
### 2nd Assignment for the NYUAD Operating Systems Course, submitted March 13th 2021
### by Liam Richards

## HOW TO RUN THE PROGRAM
The myhie program runs simply using G++ commands. A make file is used to facilitate separate compilation, so to run the program the "make" command must be used before arguments can be passed.
The myhie program arguments also have the following format (in no particular order):
    ./myhie -i InputFile -k NumOfWorkers -r -a AttributeNumber -o Order -s OutputFile

So, commands to run the program from scratch on a UNIX-based shell would be as follows:
```
    >> make
    >> ./myhie -i 1batch-1000.csv -k NumOfWorkers -r -a AttributeNumber -o Order -s OutputFile
```
The output (of the time statistics and signal statistics) is displayed directly on the terminal and no further user input is required.

## PROGRAM STRUCTURE 
The main structures of the program are separated into the following C++ (.cpp) files:
- myhie.cpp, which is the root node of the program. This node handles the command line arguments, spawns the coordinator node, and receives SIGUSR1 and SIGUSR2 signals from the sorter and merger nodes, respectively.
- csv.cpp, which handles the main csv functions such as reading from the input csv file, writing to the output csv file, and getting the size of a csv file.
- coord.cpp, which contains the coordinator node. This node spawns the sorter nodes and handles the range of data points that each sorter node has to sort through.
- merger.cpp, which contains the merger node. This node is intended to receive the partially sorted data points from each node and return a fully sorted array to the root node, alerting the root (myhie) node with a SIGUSR2 signal.
- taxpayer.cpp contains the Taxpayer data type. This allows the myhie program to create an array of type Taxpayer to easily store the information from the input CSV file.
- bubblesort.cpp & selectionsort.cpp contain both sorting programs that sort through the Taxpayer array. It is provided an order (ascending or descending order) as well as the attribute to sort by (RID, income, # of Dependents, or zipcode).

## DESIGN CHOICES
The 2 sorting algorithms of choice for the myhie program were Selection Sort and Bubble Sort. 
Although the time complexity for each of these sorting algorithms is O(n^2) which is rather slow, these were both chosen for simplicity's sake. 

'K' sorting node(s) are spawned by the coord node, and print their time spent running and send the root node a SIGUSR1 signal before terminating.
**It is important to note that the sorter nodes themselves do not do any sorting, due to an unfortunate last-minute bug causing the sorter nodes to not sort after the first sorter node.
So, what is really happening is that the root node runs a Bubble Sort of the entire data set before outputting the results to a file. This works fine for smaller data sets, but starts to take a while at the 100,000 data points mark. 

As for when the random flag (-r) is set, I chose to distribute a minimum of 1 data point to each sorter node inside coord.cpp. 
With the leftover data points (stored in the variable leftoverRandom), I then randomly generate a number anywhere from 1 to the maximum value of leftoverRandom and assign it to a random sorter node, determined by generating a random index in my array of sorter nodes.
