import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * ���̷߳�����-�̳߳ذ汾 Ĭ����8080�˿ڼ��������ܿͻ��˵�TCP���� ���ÿ���ͻ��˵����󣬴��̳߳��л�ȡһ���̣߳�������ڿ��е��̣߳������������
 * ���������ʱ��û�п����̣߳����жϣ�blocking���ȴ������̳߳��� ���ܣ����û�����һ��HTML��ʽ���ַ��� �ο�
 * http://tutorials.
 * jenkov.com/java-multithreaded-servers/thread-pooled-server.html
 * 
 * @author chunhuachen@scut.edu.cn
 * 
 */
public class ThreadPooledServer implements Runnable {

	protected int serverPort = 8080;
	protected ServerSocket serverSocket = null;
	protected boolean isStopped = false;
	protected Thread runningThread = null;
	protected ExecutorService threadPool = Executors.newFixedThreadPool(10);

	public ThreadPooledServer(int port) {
		this.serverPort = port;
	}

	public void run() {
		synchronized (this) {
			this.runningThread = Thread.currentThread();
		}
		openServerSocket();
		System.out.println("Server is now waiting on port: " + this.serverPort);
		int index = 1;
		while (!isStopped()) {

			Socket clientSocket = null;
			try {
				clientSocket = this.serverSocket.accept();
				System.out
				.println("----------------- Request NO. "+index+" ------------------------");
			} catch (IOException e) {
				if (isStopped()) {
					System.out.println("Server Stopped.");
					break;
				}
				throw new RuntimeException("Error accepting client connection",
						e);
			}

			// ���̳߳��л�ȡһ�������߳�������ͻ��˵�����
			this.threadPool.execute(new WorkerRunnable(clientSocket,
					"Thread Pooled Server"));
			
			index ++;
		}
		this.threadPool.shutdown();
		System.out.println("Server Stopped.");
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

	public static void main(String[] args) {

		ThreadPooledServer server = new ThreadPooledServer(8080);
		new Thread(server).start();

		try {
			// �ӳ�һ��ʱ���رս��̣���λ����
			Thread.sleep(100 * 1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Stopping Server");
		server.stop();

	}
}