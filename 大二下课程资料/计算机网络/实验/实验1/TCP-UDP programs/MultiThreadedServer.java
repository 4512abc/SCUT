import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.io.IOException;

/**
 * 多线程服务器 默认在8080端口监听，接受客户端的TCP请求 针对每个客户端的请求，新建一个线程来处理该请求 功能：给用户返回一串HTML格式的字符串
 * 参考:
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
				// 接受客户端TCP请求
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

			// 新建一个新线程处理客户端请求
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
			// 延迟一定时间后关闭进程，单位毫秒
			Thread.sleep(100 * 1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Stopping Server");
		server.stop();

	}

}