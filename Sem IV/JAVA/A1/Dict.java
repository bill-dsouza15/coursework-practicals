import java.util.*;
import java.io.*;
import java.nio.charset.StandardCharsets;  
public class Dict
{
	///////////////////////////////////////////Create dictionary function////////////////////////////////////
	
	public static Hashtable<String,LinkedList<String>> createDict(Hashtable<String,LinkedList<String>> h, String temp, String s)
	{
		LinkedList<String> l = new LinkedList<String>();
		if(!(h.containsKey(temp)))
		{
			l.add(s);
			h.put(temp,l);
		}
		else
		{
			l = h.get(temp);
			l.add(s);
			h.put(temp,l);
		}
		return h;
	}
	
	///////////////////////////////////////////Search dictionary function////////////////////////////////////
	
	public static void findWord(LinkedList<String> l1, String search)
	{
		if(l1.contains(search))
		{
			System.out.println("The word exists : " + search);
		}
		else
		{
			System.out.println("Did you mean? ");
			int flag=0,i=0,j;
			while(i<search.length())
			{
				String test;
				test = search.substring(0,(search.length())-i);
				j=0;
				while(j<l1.size())
				{
					String subs;
					subs = l1.get(j);
					if((subs.length() >= search.length()) && test.equals(subs.substring(0,search.length()-i)))
					{
						System.out.println(subs);
						flag=1;
					}
					j++;
				}
				if(flag==1)
				{
					break;
				}
				else
				{
					i++;
				}
			}
		}
	}
	
	public static void main(String args[])
	{  
		int n=0;
		Scanner s = new Scanner(System.in);
		List<String> k = new ArrayList<>();
		Hashtable<String,LinkedList<String>> h = new Hashtable<String,LinkedList<String>>();
		File file = new File("words.txt");
		try(Scanner f = new Scanner(file))
		{
		
		//////////////////////////////////////////User input/////////////////////////////////////////////
		
			System.out.print("The words are: \n");
			int i=0;
			while(f.hasNextLine())
			{
				n++;
				k.add(f.nextLine());
				System.out.println(k.get(n-1));
				i++;
			}
		
		///////////////////////////////////////Creating dictionary//////////////////////////////////////
		
			int x=0;
			i=0;
			while(i<n)
			{
			 	String temp;
				if((k.get(i)).charAt(0) >= 'a' && (k.get(i)).charAt(0) <= 'z')
				{
					temp = String.valueOf((k.get(i)).charAt(0));
					h = createDict(h,temp,(k.get(i)));		
				}
				else if((k.get(i)).charAt(0) >= 'A' && (k.get(i)).charAt(0) <= 'Z')
				{
					temp = String.valueOf((char)((int)((k.get(i)).charAt(0)) + 32));
					h = createDict(h,temp,(k.get(i)));
				}
				i++;
			}
						
		////////////////////////////////////Iterating through hashtable///////////////////////////////////
		
			Set entrySet = h.entrySet();
			Iterator it = entrySet.iterator();
			while(it.hasNext())
			{	
				System.out.println(it.next());  
			}  
		
		////////////////////////////////////Searching through hashtable///////////////////////////////////
		
			String ch,search;
			System.out.println("Do you want to search for an element? Y or N"); 
			ch = s.nextLine();
			if(ch.equals("Y"))
			{
				LinkedList<String> l1 = new LinkedList<String>();
				System.out.println("Enter what you want to search : "); 
				search = s.nextLine();
				if(search.charAt(0) >= 'a' && search.charAt(0) <= 'z')
				{
					l1 = h.get(String.valueOf(search.charAt(0)));
					findWord(l1,search);	
				}
				else if(search.charAt(0) >= 'A' && search.charAt(0) <= 'Z')
				{
					l1 = h.get(String.valueOf((char)((int)((search.charAt(0)) + 32))));
					findWord(l1,search);
				}
			}
			else if(ch.equals("N"))
			{
				System.out.println("Thank you!");
			}
		
		}
		catch(IOException e)
		{
			e.printStackTrace();
		}
	}
}  
