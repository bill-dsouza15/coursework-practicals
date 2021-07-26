#!/bin/sh
<<Shebang
The line #!/bin/sh is a shebang or "bang" line.
It gives the path of Bash intepreter used for execution of the script.
Shebang

read -p "Enter name of record to be deleted: " deln 	#Read the name of person whose record is to be deleted  
sed -i "/$deln/d" address.txt 							#Using sed -i the line with name field "deln" is deleted and the file is overwritten
echo "Record deleted!\n"								#Feedback for telling the user that record is deleted
