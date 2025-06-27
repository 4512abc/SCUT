import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 多线程服务器-线程池版本 默认在8080端口监听，接受客户端的TCP请求 针对每个客户端的请求，从线程池中获取一个线程（如果存在空闲的线程）来处理该请求
 * 如果请求到来时，没有空闲线程，将中断（blocking）等待空闲线程出现 功能：给用户返回一串HTML格式的字符串 参考
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

			// 从线程池中获取一个空闲线程来处理客户端的请求
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
			// 延迟一定时间后关闭进程，单位毫秒
			Thread.sleep(100 * 1000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Stopping Server");
		server.stop();

	}
}