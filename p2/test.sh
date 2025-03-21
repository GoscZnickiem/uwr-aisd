#!/bin/bash

# Loop through values of k from 3000 to 10000
for ((k=2910; k<=100000; k+=1)); do
    # Print the value of k being used (optional for debugging)
    echo "Running with k=$k"
    
    # Run the command with the current value of k
    echo "$k 2000000" | ./a.out

done

