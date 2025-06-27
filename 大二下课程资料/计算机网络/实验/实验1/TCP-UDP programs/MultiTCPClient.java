import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;


public class MultiTCPClient {
	/**
	 * @param args
	 */
	public static void main(String[] args) {

		//String serverName = args[0];
		//int port = Integer.parseInt(args[1]);

	    ExecutorService threadPool = Executors.newFixedThreadPool(25);
	    for(int i=0; i<100;i++){
	    	//threadPool.submit(new TCPClientRunnable(serverName, port, "Task-"+i));
	    	threadPool.execute(new TCPClientRunnable("localhost", 8080, "Task-"+i));
	    }

	    threadPool.shutdown();
	    while(!threadPool.isTerminated());
	    System.out.println("MultiTCPClient stoped");
	}
}
