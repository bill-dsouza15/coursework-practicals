#!/bin/sh
<<Shebang
The line #!/bin/sh is a shebang or "bang" line.
It gives the path of Bash intepreter used for execution of the script.
Shebang

read -p "Enter the name of record to be found: " nfind		#Read name of person whose record is to be found
echo "Name\t\tMobileNumber\t\tCity\t\tAddress"				#Creating a tabular look
grep -w "$nfind" address.txt								#Search the file address.txt for word "nfind" and display the line
echo "\n"													#newline
