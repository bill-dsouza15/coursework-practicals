import java.io.*;
import java.net.*;
import java.util.*;
import java.lang.*;
import java.swing.*;
import java.awt.*;

public class Client
{
	static DataInputStream din;
	static DataOutputStream dout;
	public static void main(String[] args)
	{
		String name;
		String message = "";
		Scanner sc = new Scanner(System.in);
		int port = 4444;
		try
		{
			InetAddress ip = InetAddress.getByName("192.168.1.106");
			Socket s = new Socket(ip,port);
 			
			System.out.println("Connection established!");
						
			dout = new DataOutputStream(s.getOutputStream());
			din = new DataInputStream(s.getInputStream());
			
			//Read username
			System.out.println("Enter your name: ");
			name = sc.nextLine(); 
			dout.writeUTF(name);
			
			PrintMessage pm = new PrintMessage(s,din);
			Thread t = new Thread(pm);
			t.start();
			
			while(!message.equals("bye") && !s.isClosed())
			{
				//System.out.print(name + ": "); 
				message = sc.nextLine();
				dout.writeUTF(message);
				dout.flush();
				
				while(din.available() > 0)
				{
					System.out.println(din.readUTF());
				}
			}
			s.close();
			dout.close();
			sc.close();
		}
		catch(IOException e)
		{
			System.out.println("Could not send message!"); 
		}		
	}
}

class PrintMessage extends Client implements Runnable
{
	Socket ps;
	DataInputStream pin;
	String msg = "";
	PrintMessage(Socket s,DataInputStream din)
	{
		this.ps = s;
		this.pin = din;
	}
    
    @Override
    public void run()
    {
    	while(!this.ps.isClosed())
    	{
			try
			{
				msg = pin.readUTF();
				System.out.println(msg);
			}
			catch(IOException e)
			{
				System.out.println("You have logged out!"); 
			}
		}
		try
		{
			pin.close();
		}
		catch(IOException e)
		{
			System.out.println("Could not close stream!"); 
		}
    }
}
    	
