# Mini-OS
 Built a mini uniprogramming virtual operating system using C++.

 Implemented paging and process management.

 Wrote a simple ALU routine to let programmer perform arithmetic and logical
operations.

 Handled page-faults(valid and invalid) and appropriate error conditions.

The instructions provided by programmer are equivalent to the assembly language instructions.

Whenever a new process comes in
    -A Page-table is allocated, randomly at any starting position of size 40 words.
    
    -Now all the instructions are stored in a memory of frame size 10 blocks(40-words).
    
    -The file-pointer points to the data-card of the input file.
    
    -According to the instructions given in the frame data will be fetched from the data-card line-by-line.


The error conditions that are handled:
    Each process had limit on:
        
        ->The time it can use -- Time limit exceeded error
        
        ->The numbers of lines it can output/write in the output file. -- Out-of-data error
        
        ->Invalid operand error
        
        ->Invalid opcode error.
        
        ->Valid and Invalid page-fault
        
        
