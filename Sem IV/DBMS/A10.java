import java.util.Scanner;

import org.bson.Document;
import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoCursor;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Indexes;
import com.mongodb.client.model.Updates;

public class MongoDbConn {

	public static void main(String[] args) {
		MongoDatabase db = null;
		MongoClient m = null;
		Scanner sc = new Scanner(System.in);
		try
		{
			
			m = new MongoClient(new MongoClientURI("mongodb://127.0.0.1:27017")); 
			db = m.getDatabase("StaffInfo");
			System.out.println("Connected to database succesfully!");
		}
		catch(Exception e)
		{
			System.out.println("Couldnt connect to database!");
		}
		
		//Create and get collection Employee//
		try
		{
			db.createCollection("Employee");
			System.out.println("Collection 'Employee' selected succesfully!");
		}
		catch(Exception e)
		{
			System.out.println("Collection 'Employee' exists! Using collection...");
		}
		MongoCollection<Document> collection = db.getCollection("Employee");
		//Creating index on _id, EmpNo and EmpName//
		try
		{
			collection.createIndex(Indexes.ascending("_id","EmpNo","EmpName"));
		}
		catch(Exception e)
		{
			System.out.println("Index exists! Using Index...");
		}
		
		int ch = 0;
		String EmpNo = "";
    	String EmpName = "";
    	String Designation = "";
    	String Salary = "";
    	
    	System.out.println("//////////////DATABASE/////////////");
    	System.out.println("The following options are available for database manipulation :");
    	System.out.println("1. Create document 	2. Retrieve documents	3. Update document	4. Delete document	5. Exit");
    	
    	while(ch!=5)
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
	    		case 1:		//Create document
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
		    			try
		    			{
		    				System.out.print("Enter EmpNo : ");
				    		EmpNo = sc.nextLine();
				    		System.out.print("Enter EmpName : ");
				    		EmpName = sc.nextLine();
				    		System.out.print("Enter Designation : ");
				    		Designation = sc.nextLine();
				    		System.out.print("Enter Salary : ");
				    		Salary = sc.nextLine();
		    				Document document = new Document("EmpNo",EmpNo)
		    						.append("EmpName",EmpName)
		    						.append("Designation",Designation)
		    						.append("Salary",Salary);
		    				collection.insertOne(document);
		    				System.out.print("Document inserted successfully!\n\n");
		    			}
		    		    catch(Exception e)
		    		    {
		    		    	System.out.print("Document already exists!\n\n");
		    		    }
		    			num--;
    				}
	    			break;
	    			
	    		case 2:		//Retrieve documents
	    			try
	    			{
	    				FindIterable<Document> docfind = collection.find();
	    				MongoCursor<Document> it = docfind.iterator();
	    				while(it.hasNext())
			    		{
				    		System.out.println(it.next());
			    		}
	    			}
	    		    catch(Exception e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    		
	    		case 3:		//Update record
	    			try
	    			{
		    			System.out.print("Enter the EmpNo of the document to be updated : ");
		    			System.out.println("");
			    		EmpNo = sc.nextLine();
			    		
			    		try
			        	{
			    	    	System.out.println("Enter choice : 1.Update Name	2.Update Designation	3.Update Salary");
			    	    	String n = sc.nextLine();
			    			ch = Integer.parseInt(n);
			        	}
			        	catch(NumberFormatException e)
			        	{
			        		e.printStackTrace();
			        	}
			    		switch(ch)
			    		{
			    			case 1:
			    				System.out.print("Enter new name : ");
			    				EmpName = sc.nextLine();
			    				collection.updateOne(Filters.eq("EmpNo",EmpNo),Updates.set("EmpName", EmpName));
			    				System.out.println("Document updated!\n\n");
			    				break;
			    				
			    			case 2:
			    				System.out.print("Enter new designation : ");
			    				Designation = sc.nextLine();
			    				collection.updateOne(Filters.eq("EmpNo",EmpNo),Updates.set("Designation", Designation));
			    				System.out.println("Document updated!\n\n");
			    				break;
			    			
			    			case 3:
			    				System.out.print("Enter new salary : ");
			    				Salary = sc.nextLine();
			    				collection.updateOne(Filters.eq("EmpNo",EmpNo),Updates.set("Salary", Salary));
			    				System.out.println("Document updated!\n\n");
			    				break;
			    				
			    			default:
			    				System.out.println("Invalid choice for update!");
			    		}
	    			}
	    		    catch(Exception e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    			
	    		case 4:		//Delete record
	    			try
	    			{
		    			System.out.print("Enter the Empno of the record to be deleted : ");
			    		EmpNo = sc.nextLine();
		    			collection.deleteOne(Filters.eq("EmpNo",EmpNo));
			    		System.out.println("Document deleted!\n\n");
	    			}
	    		    catch(Exception e)
	    		    {
	    		    	e.printStackTrace();
	    		    }
	    			break;
	    			
	    		case 5:		//Exit
	    			try
	    			{
	    				sc.close();
	    	    		System.out.print("Exiting!");
	    	    		break;
	    			}
	    			catch(Exception e)
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

