import java.util.*;
import java.lang.*;

public class ProdCons
{
    public final static Queue<Integer> DataBuffer = new LinkedList<Integer>(); 
    public final static int maxSize = 5;
	public static void main(String[] args) 
	{
	    try
	    {
    	    Producer P = new Producer(DataBuffer,maxSize);
    	    Consumer C = new Consumer(DataBuffer,maxSize);
    		Thread tp = new Thread(P);
    		Thread tc = new Thread(C);
    		tp.start();
    		tc.start();
	    }
	    catch(Exception e)
	    {
	        e.printStackTrace();
	    }
	}
}

class Producer extends ProdCons implements Runnable 
{
    int item = 10;
    Queue<Integer> prodbuff;
    int pMaxSize;
    
    Producer(Queue<Integer> Buff, int maxSize)
    {
        this.prodbuff = Buff;
        this.pMaxSize = maxSize;
    }
    
    @Override
    public void run()
    {
        try
        {
            while(true)
            {
                synchronized(this.prodbuff)
                {
                    while( this.prodbuff.size() == pMaxSize )
                    {
                        System.out.println("Data Buffer is full");
                        this.prodbuff.wait();
                    }
                }
                synchronized(this.prodbuff)
                {
	                //Thread.sleep(10);
                    this.prodbuff.add(item);
                    this.prodbuff.notifyAll();
                    System.out.println("Item is PRODUCED");
                }
            }
        }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }
    }
}

class Consumer extends ProdCons implements Runnable 
{
    Queue<Integer> consbuff;
    int cMaxSize;
    
    Consumer(Queue<Integer> Buff, int maxSize)
    {
        this.consbuff = Buff;
        this.cMaxSize = maxSize;
    }
    
    @Override
    public void run()
    {
        try
        {
            while(true)
            {
                synchronized(this.consbuff)
                {
                    while( this.consbuff.isEmpty() )
                    {
                        System.out.println("Data Buffer is empty");
                        this.consbuff.wait();
                    }
                }
                synchronized(this.consbuff)
                {
                    this.consbuff.remove();
                    this.consbuff.notifyAll();
                    System.out.println("Item is CONSUMED");  
                }
            }
        }
        catch(InterruptedException e)
        {
            e.printStackTrace();
        }
    }
}
