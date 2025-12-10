# From the subject

__Summary:__  
In short: This project will make you recode the command “ls”.  
Version: 3.1  

• Your project must be written in C.  
• You must submit a Makefile.  
• Libc is not allowed (libft is)  

• Its behavior must be identical to the original ls command with the following variations:  
◦ Amongst the numerous options available, we are asking you to create the following: -l, -R, -a, -r and -t.  
◦ You do not have to deal with the multiple column format for the exit when the option -l isn’t in the arguments.  
◦ You are not required to deal with ACL and extended attributes.  
◦ The overall display, depending on each option, must stay as identical as possible to the system command.  

__Bonus__  
• Management of ACL and extended attributes. (ls doesn't show attributes on linux)
• Management of the columns without the option -l. (I have 1 column)
• Management of options -u, -f, -g, -d, ... (I added -U, -g, -o, -d, --si (as -h))
• Optimization of your code (What is the response time of your ls on a BIG ls -lR for example?) (about 10% slower)

# Usage
`make` then `./ft_ls [opts] [args=.]`. `--` means end of options. Available options : `-adghlorRtU`.
