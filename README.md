*This project has been created as part of the 42 curriculum by **ls-phabm***

# Description
> the project, including its goal and a brief overview

### Project
Sort data in a stack using a limited set of instructions: dive into sorting algorithms & their complexities

### Goal

- achieve the lowest possible number of action
- calculate and display the shortest sequence of instructions needed to sort the given numbers

### Means

- work with various algorithms
- choose the most appropriate one for optimized data sorting

### Tools 

- set of ints
- 2 stacks a & b
- set of instructions to manipulate both stacks (see table below)

| Code  | Instruction                              | Action                                                                 |
| ---   |    -----------------------------------   |  --------------------------------------------------------------------- |
| sa    | swap a                                   | Swap the top 2 elements of stack a                                     |
| sb    | swap b                                   | Swap the top 2 elements of stack b                                     |
| ss    | swap a + swap b                          | sa and sb at the same time                                             |
| pa    | push a                                   | Take the first element at the top of b and put it at the top of a      |
| pb    | push b                                   | Take the first element at the top of a and put it at the top of b      |
| ra    | rotate a                                 | Shift up all elements of stack a by 1                                  |
| rb    | rotate b                                 | Shift up all elements of stack b by 1                                  |
| rr    | rotate a + rotate b                      | ra and rb at the same time                                             |
| rra   | reverse rotate a                         | Shift down all elements of stack a by 1                                |
| rrb   | reverse rotate b                         | Shift down all elements of stack b by 1                                |
| rrr   | reverse rorate a + reverse rotate b      | rra and rrb at the same time                                           |

# Algorithm
For stacks up to 5, a simple algorithm is used `algo_mini`.

The primary algorithm uses a fixed chunk-based and greedy approach, according to the following logic:
1. Parse
	1. Split arguments if necessary
	2. Check if arguments are valid numbers
	3. Check if no duplicate
	4. Create stack a as a list of arguments
2. Sort
	1. Normalize stack a by index based on argument value
	2. Split stack a into 12 chunks (most optimal factor for project validation)
	3. Push lowest eligible integers by growing chunks to b, rotate b if not chunk threshold to keep lowest integers in the middle of "K" final shape, until a contains 3 largest arguments
	4. Rotate maximum integers pushed at the top of b, push to a
	5. Et voila!

> Example to illustrate "K" shape in b : 
* n = 24
* chunk_size == 2

| pb  | pb + rb |
| --- | --- |
| 0-2 | 2-4 |
| 1-3 | 3-5 |
| 2-4 | 4-6 |
| ... | ... |

# Performance
This push_swap algorithm achieves the following number of instructions (averages are given with 500 iterations):

| n   | maximum | average |
| --- | ---     | ---     |
| 3   | 2       | 1.2     | 
| 4   | 7       | 5       |
| 5   | 10      | 7.3     |
| 100 | 666     | 605     |
| 500 | 5293    | 5040    |

The algorithm is sufficient for project requirements *(3 points for 100 in fewer than 700, 4 points for 500 fewer than 5500)*.

# Instructions
> any relevant information about compilation, installation, and/or execution

- The program takes as an argument the stack a formatted as a list of integers. 
- During the evaluation process, the number of instructions found by the program will be compared against a limit: the **maximum number of operations tolerated**. If the program either displays a **longer list** or if the numbers **aren’t sorted properly**, the grade will be **0**.
- If no parameters are specified, the program must not display anything and should return to the prompt.
- In case of error, it must display **"Error" followed by an \n’ on the standard error.**
- Errors include, for example: *some arguments not being integers, some arguments exceeding the integer limits, and/or the presence of duplicates.*

Command to execute checker_linux:

`ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker_linux $ARG`

> If the program checker_linux displays "KO", it means that the push_swap came up with a list of instructions that doesn’t sort the numbers.

Commands to execute program:

`./push_swap 3 2 1`

`./push_swap "3 2 1"`

`ARG="4 67 3 87 23"; ./push_swap $ARG | wc -l`

`ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' ') ./push_swap $ARG | wc -l`

Command to execute tester.py:

`python tester.py {number of integers} {number of trials}`

# Resources
> listing classic references related to the topic (documentation, articles, tutorials, etc.)
> a description of how AI was used — which tasks and which parts of the project.

* Push Swap subject : <https://cdn.intra.42.fr/pdf/pdf/192339/en.subject.pdf>
* Linked lists : <https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/>
* Sorting algorithms : <https://www.linkedin.com/pulse/push-swap-art-sorting-two-stacks-anass-outiskte-bjsje>
* push swap visualizer : <https://github.com/o-reo/push_swap_visualizer>
* funcheck : <https://github.com/froz42/funcheck>

AI was used to break down *parsing logic, understand linked list manipulation and chunk sorting.*
