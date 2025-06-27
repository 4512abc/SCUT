import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;


public class TCPClientRunnable implements Runnable {
	
	protected String serverName = null;
	protected int port = 8080;
	protected String clientText = null;
	
	public TCPClientRunnable(String serverName, int port, String clientText) {
		this.serverName = serverName;
		this.port = port;
		this.clientText = clientText;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			System.out.println(this.clientText+ " connecting to " + serverName + " on port "
					+ port);
			Socket client = new Socket(serverName, port);
			//System.out.println("Just connected to "
			//		+ client.getRemoteSocketAddress());
			
			//OutputStream outToServer = client.getOutputStream();
			//DataOutputStream out = new DataOutputStream(outToServer);
			//out.writeUTF("Hello from " + client.getLocalSocketAddress());
			
			InputStream inFromServer = client.getInputStream();
			DataInputStream in = new DataInputStream(inFromServer);
			System.out.println("--------------------------------------");
			System.out.println(in.readUTF());
			System.out.println("--------------------------------------");
			client.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
