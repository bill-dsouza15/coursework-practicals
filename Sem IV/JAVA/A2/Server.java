import java.util.*;
import java.io.*;
import java.net.*;

public class Server
{
	static java.util.concurrent.ConcurrentLinkedDeque<ClientThread> Clients = new java.util.concurrent.ConcurrentLinkedDeque<ClientThread>();
	
	public static void main(String[] args) throws IOException
	{	
		int port = 4444;
		ServerSocket ss = new ServerSocket(port);
		while(true)
		{
			Socket s = null;
			try
			{
				s = ss.accept();
				ClientThread ct = new ClientThread(s);
				Thread t = new Thread(ct);
				t.start();	
			}
			catch(Exception e)
			{
				s.close();
				System.out.println("Socket unavailable!"); 
			}
		}		
	}
}

class ClientThread extends Server implements Runnable
{
	Socket s1;
	String username = "";
	DataInputStream cin;
	DataOutputStream cout;
	Scanner sc = new Scanner(System.in);
	String ctmsg;
	
	ClientThread(Socket s)
	{
		this.s1 = s;
	}
	
	@Override
	public void run()
	{
		try
		{
			cin = new DataInputStream(s1.getInputStream());
			cout = new DataOutputStream(s1.getOutputStream());
			
			this.username = cin.readUTF();
			Clients.add(this);
			System.out.println("User " + Clients.getLast().username + " is connected!");
			
			//Read message from client and output to all clients
			while(!s1.isClosed())
			{
				this.ctmsg = cin.readUTF();
				if(ctmsg != null)
				{
					for(ClientThread ct : Clients)
					{
						if( !(ct.username).equals(this.username) )
						{
							ct.cout.writeUTF(this.username + ": " + ctmsg);
							ct.cout.flush();
						}
					}
				}
			}
		}
		catch(IOException e)
		{
			System.out.println("User " + this.username + " is disconnected!"); 
		}
		
		try
        { 
        	Clients.remove(this);
            this.cin.close(); 
            this.cout.close(); 
              
        }
        catch(IOException e)
        { 
            System.out.println("Could not close streams!"); 
        } 	
	}
}
