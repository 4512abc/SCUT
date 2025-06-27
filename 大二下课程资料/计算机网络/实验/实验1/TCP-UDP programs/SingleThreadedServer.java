import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * 单线程服务器
 * 默认在8080端口监听，接受客户端的TCP请求
 * 在监听线程处理该请求，在处理请求时，无法接受下一个用户请求
 * 功能：给用户返回一串HTML格式的字符串
 * 
 * 参考: http://tutorials.jenkov.com/java-multithreaded-servers/singlethreaded-server.html
 * @author chunhuachen@scut.edu.cn
 *
 */
public class SingleThreadedServer implements Runnable {

	protected int serverPort = 8080;
	protected ServerSocket serverSocket = null;
	protected boolean isStopped = false;
	protected Thread runningThread = null;

	public SingleThreadedServer(int port) {
		this.serverPort = port;
	}

	public void run(){
    	
        synchronized(this){
            this.runningThread = Thread.currentThread();
        }
        
        openServerSocket();
        System.out.println("Server is now waiting on port: "+this.serverPort);
		int index = 1;
		while (!isStopped()) {
        	
            Socket clientSocket = null;
            try {
                clientSocket = this.serverSocket.accept();
				System.out.println("----------------- Request NO. " + index
						+ " ------------------------");
				
            } catch (IOException e) {
            	
                if(isStopped()) {
                    System.out.println("Server Stopped.") ;
                    return;
                }
                throw new RuntimeException(
                    "Error accepting client connection", e);
            }
            try {
            	// 使用当前线程处理客户端请求
                processClientRequest(clientSocket);
            } catch (IOException e) {
                //log exception and go on to next request.
            }
            
            index++;
        }
        
        System.out.println("Server Stopped.");
    }

	private void processClientRequest(Socket clientSocket) throws IOException {
		InputStream input = clientSocket.getInputStream();
		DataOutputStream output = new DataOutputStream(clientSocket.getOutputStream());
		//当前线程的id
		String threadID = String.valueOf(Thread.currentThread().getId());
        SimpleDateFormat dateFormat = new SimpleDateFormat(
                "yyyy-MM-dd HH:mm:ss");
        String date = dateFormat.format(new Date());
        output.writeUTF(("HTTP/1.1 200 OK\n\n<html><body>"
				+ "<H1>Single Threaded Server: </H1><H1>Time: " + date + "</H1><H1>Server Socket: "+clientSocket.getLocalSocketAddress()+"</H1><H1>Client Socket: "+clientSocket.getRemoteSocketAddress()+"</H1><H1>by Thread: "+ threadID +"</H1></body></html>"));
		output.close();
		input.close();
		
        System.out.println("Request processed: " + date);
        System.out.println("Server Socket:" + clientSocket.getLocalSocketAddress());
        System.out.println("Client Socket:" + clientSocket.getRemoteSocketAddress());
        System.out.println("By Thread: " + Thread.currentThread().getId());
	}

	private synchronized boolean isStopped() {
		return this.isStopped;
	}

	public synchronized void stop() {
		this.isStopped = true;
		try {
			this.serverSocket.close();
		} catch (IOException e) {
			throw new RuntimeException("Error closing server", e);
		}
	}

	private void openServerSocket() {
		try {
			this.serverSocket = new ServerSocket(this.serverPort);
		} catch (IOException e) {

			throw new RuntimeException("Cannot open port " + this.serverPort, e);
		}
	}

	public static void main(String [] args){
	
		SingleThreadedServer server = new SingleThreadedServer(8080);
		new Thread(server).start();
		try {
			// 延迟一定时间后关闭进程，单位毫秒
			Thread.sleep(100 * 1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Stopping Server ... ...");
		server.stop();
	}
}