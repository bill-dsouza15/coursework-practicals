#!/bin/sh
<<Shebang
The line #!/bin/sh is a shebang or "bang" line.
It gives the path of Bash intepreter used for execution of the script.
Shebang

#"read -p" displays a prompt message before taking user input
read -p "Enter name: " name					    		  	#Read the name of the person
read -p "Enter mobilenumber: " mno                          #Read the mobile number of the person
read -p "Enter city: " city					     			#Read the city of the person
read -p "Enter address: " adrs								#Read the address of the record
echo "$name\t\t$mno\t\t$city\t\t$adrs" >> address.txt 		#Append the name,city,address fields to the file


