import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

/**
 * ���̷߳�����
 * Ĭ����8080�˿ڼ��������ܿͻ��˵�TCP����
 * �ڼ����̴߳���������ڴ�������ʱ���޷�������һ���û�����
 * ���ܣ����û�����һ��HTML��ʽ���ַ���
 * 
 * �ο�: http://tutorials.jenkov.com/java-multithreaded-servers/singlethreaded-server.html
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
            	// ʹ�õ�ǰ�̴߳���ͻ�������
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
		//��ǰ�̵߳�id
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
			// �ӳ�һ��ʱ���رս��̣���λ����
			Thread.sleep(100 * 1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Stopping Server ... ...");
		server.stop();
	}
}