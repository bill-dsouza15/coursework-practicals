import java.util.*;
import java.sql.*;
public class Database
{
	public static void main(String[] args)
	{
		Connection conn = null;
		Statement st = null;
		PreparedStatement pst = null;
		Scanner sc = new Scanner(System.in);
		try
		{
			Class.forName("com.mysql.cj.jdbc.Driver");
		}
		catch(Exception e)
		{
    			e.printStackTrace();
	    }
	    try
	    {
			String url = "jdbc:mysql://localhost:3306/student"; 
			String uname = "root";
			String pswd = "mysqlroot";
	    	//Create connection to sql//	
    		conn = DriverManager.getConnection(url,uname,pswd);
    		
    		//Creating statement to execute//
    		st = conn.createStatement();
	    }
	    catch(SQLException e)
	    {
	    	e.printStackTrace();
	    }
	    
    	int ch = 0;
    	int srno = 1;
    	String grno="";
    	String name="";
    	String address="";
    	String mobno="";
    	
    	System.out.println("//////////////DATABASE/////////////");
    	System.out.println("The following options are available for database manipulation :");
    	System.out.println("1. Create table 	2. Insert records	3. Delete record	4. Update record	5. Display records	6. Drop table	7. Exit");
    	
    	while(ch!=7)
    	{
    		try
    		{
	    		System.out.println("Enter your choice :");
	    		String n = sc.nextLine();
				ch = Integer.parseInt(n);
    		}
    		catch(NumberFormatException e)
    		{
    			e.printStackTrace();
    		}
	    	switch(ch)
	    	{
	    		case 1:		//Create table
	    			try
	    			{
	    				st.executeUpdate("CREATE TABLE Student_info(SrNo INT NOT NULL,GrNo VARCHAR(8) NOT NULL,Name VARCHAR(20) NOT NULL,MobileNo VARCHAR(10) NOT NULL,Address VARCHAR(50) NOT NULL,PRIMARY KEY(GrNo))");
	    				System.out.print("Table created!\n\n");
	    			}
	    		    catch(SQLException e)
	    		    {
	    		    	System.out.print("Table already exists!\n\n");
	    		    }	
	    			break;
	    			
	    		case 2:		//Insert records
	    			try
	    			{
	    				int num=0;
	    				try
	    	    		{
	    		    		System.out.println("Enter number of records to be inserted :");
	    		    		String t = sc.nextLine();
	    					num = Integer.parseInt(t);
	    	    		}
	    	    		catch(NumberFormatException e)
	    	    		{
	    	    			e.printStackTrace();
	    	    		}
			    		while(num>0)
			    		{
				    		System.out.print("Enter grno : ");
				    		grno = sc.nextLine();
				    		System.out.print("Enter name : ");
				    		name = sc.nextLine();
				    		System.out.print("Enter mobno : ");
				    		mobno = sc.nextLine();
				    		System.out.print("Enter address : ");
				    		address = sc.nextLine();
				    		
				    		pst = conn.prepareStatement("INSERT INTO Student_info VALUES(?,?,?,?,?);");
				    		pst.setInt(1, srno);
				    		pst.setString(2, grno);
				    		pst.setString(3, name);
				    		pst.setString(4, mobno);
				    		pst.setString(5, address);
				    		pst.executeUpdate();
				    		System.out.println("Record added!\n\n");
				    		srno++;
				    		num--;
			    		}
	    			}
	    		    catch(SQLException e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    		
	    		case 3:		//Delete record
	    			try
	    			{
		    			System.out.print("Enter the grno of the record to be deleted : ");
		    			System.out.println("");
			    		grno = sc.nextLine();
		    			pst = conn.prepareStatement("DELETE FROM Student_info WHERE GrNo = ?;");
			    		pst.setString(1, grno);
			    		pst.executeUpdate();
			    		System.out.println("Record deleted!\n\n");
	    			}
	    		    catch(SQLException e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    			
	    		case 4:		//Update record
	    			try
	    			{
		    			System.out.print("Enter the grno of the record to be updated : ");
		    			System.out.println("");
			    		grno = sc.nextLine();
			    		System.out.print("Enter new name : ");
			    		name = sc.nextLine();
			    		System.out.print("Enter new mobno : ");
			    		mobno = sc.nextLine();
			    		System.out.print("Enter new address : ");
			    		address = sc.nextLine();
		    			pst = conn.prepareStatement("UPDATE Student_info SET Name = ?, Address = ?, MobileNo = ? WHERE GrNo = ?;");
			    		pst.setString(1, name);
			    		pst.setString(2, address);
			    		pst.setString(3, mobno);
			    		pst.setString(4, grno);
			    		pst.executeUpdate();
			    		System.out.println("Record updated!\n\n");
	    			}
	    		    catch(SQLException e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    		
	    		case 5:		//Display record
	    			try
	    			{
		    			System.out.print("The table is as follows : \n");
		    			System.out.print("SrNo\tGrNo\t\tName\t\tAddress\t\tMobileNo\n");
		    			ResultSet rs = st.executeQuery("SELECT * FROM Student_info;");
		    			while(rs.next())
		    			{
		    				System.out.print(rs.getInt("SrNo")+"\t");
		    				System.out.print(rs.getString("GrNo")+"\t");
		    				System.out.print(rs.getString("Name")+"\t");
		    				System.out.print(rs.getString("Address")+"\t");
		    				System.out.print(rs.getString("MobileNo")+"\n");
		    			}
			    		System.out.println("\nRecords displayed!\n\n");
	    			}
	    		    catch(SQLException e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    		
	    		case 6:		//Drop table
	    			try
	    			{
	    				st.executeUpdate("DROP TABLE Student_info;");
			    		System.out.println("Table dropped!");
	    			}
	    		    catch(SQLException e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    		
	    		case 7:		//Exit
	    			try
	    			{
	    				sc.close();
	    	    		conn.close();
	    	    		System.out.print("Exiting!");
	    	    		break;
	    			}
	    			catch(SQLException e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    		
	    		default:
	    			System.out.print("Incorrect option");
		    }
    	}
	}
}
