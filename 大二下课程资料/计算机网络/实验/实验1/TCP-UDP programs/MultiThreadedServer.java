import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.IOException;

/**
 * ���̷߳����� Ĭ����8080�˿ڼ��������ܿͻ��˵�TCP���� ���ÿ���ͻ��˵������½�һ���߳������������ ���ܣ����û�����һ��HTML��ʽ���ַ���
 * �ο�:
 * http://tutorials.jenkov.com/java-multithreaded-servers/multithreaded-server
 * .html
 * 
 * @author chunhuachen@scut.edu.cn
 * 
 */
public class MultiThreadedServer implements Runnable {

	protected int serverPort = 8080;
	protected ServerSocket serverSocket = null;
	protected boolean isStopped = false;
	protected Thread runningThread = null;

	public MultiThreadedServer(int port) {
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
				// ���ܿͻ���TCP����
				clientSocket = this.serverSocket.accept();
				System.out.println("----------------- Request NO. " + index
						+ " ------------------------");
			} catch (IOException e) {
				if (isStopped()) {
					System.out.println("Server Stopped.");
					return;
				}
				throw new RuntimeException("Error accepting client connection",
						e);
			}

			// �½�һ�����̴߳���ͻ�������
			Thread workerTread = new Thread(new WorkerRunnable(clientSocket,
					"Multi Threaded Server"));
			workerTread.start();

			index++;

		}
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

		MultiThreadedServer server = new MultiThreadedServer(8080);
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