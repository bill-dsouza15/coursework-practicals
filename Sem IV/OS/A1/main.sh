#!/bin/sh
<<Shebang
The line #!/bin/sh is a shebang or "bang" line.
It gives the path of Bash intepreter used for execution of the script.
Shebang

#Granting execution permission to the script file	
chmod +x add.sh			
chmod +x list.sh		
chmod +x delete.sh
chmod +x find.sh

#Creating a tabular look
echo "Name\t\tMobileNumber\t\tCity\t\tAddress" > address.txt
ch=0

#While loop is for looping through the address book operation choices till user exits using option 5
while [ "ch" != "5" ]
do
      echo "******************ADDRESS BOOK******************"
      echo "1. Add a record"
      echo "2. List the records"
      echo "3. Delete a record"
      echo "4. Find a record"
      echo "5. Exit"
      read -p "Enter your choice: " ch		#Read user's choice

      #switch case for "ch"
      case $ch in	
            
            1) ./add.sh		#Add a record
               clear;;
               
            #case 2
            2) clear		#Lists the records
               ./list.sh;;

            #case 3
            3) clear		#Delete a record
               ./delete.sh;;
               
            #case 4
            4) clear 		#Search a record and display it
               ./find.sh;;

            #case 5
            5) exit;;		#Exit
      esac
done


