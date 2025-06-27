import java.io.*;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;

public class WorkerRunnable implements Runnable {

	protected Socket clientSocket = null;
	protected String serverText = null;

	public WorkerRunnable(Socket clientSocket, String serverText) {
		this.clientSocket = clientSocket;
		this.serverText = serverText;
	}

	public void run() {
		try {
			// ���ܿͻ�������
			InputStream input = clientSocket.getInputStream();
			DataInputStream in = new DataInputStream(input);
			System.out.println("--------------------------------------");
			System.out.println(in.readUTF());
			System.out.println("--------------------------------------");
			// �ظ��ͻ���
			DataOutputStream output = new DataOutputStream(
					clientSocket.getOutputStream());
			SimpleDateFormat dateFormat = new SimpleDateFormat(
					"yyyy-MM-dd HH:mm:ss");
			String date = dateFormat.format(new Date());
			// ��ǰ�̵߳�id
			String threadID = String.valueOf(Thread.currentThread().getId());
			output.writeUTF(("HTTP/1.1 200 OK\n\n<html><body>" + "<H1>"
					+ serverText + "</H1><H1>Time: " + date
					+ "</H1><H1>Server Socket: "
					+ clientSocket.getLocalSocketAddress()
					+ "</H1><H1>Client Socket: "
					+ clientSocket.getRemoteSocketAddress()
					+ "</H1><H1>Processed by Thread: " + threadID + "</H1></body></html>"));
			output.close();
			input.close();
			
			System.out.println("Request processed: " + date);
			System.out.println("Server Socket:"
					+ clientSocket.getLocalSocketAddress());
			System.out.println("Client Socket:"
					+ clientSocket.getRemoteSocketAddress());
			System.out.println("By Thread: "
					+ Thread.currentThread().getId());

		} catch (IOException e) {
			// report exception somewhere.
			e.printStackTrace();
		}
	}
}