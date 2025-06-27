import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;


/**
 * 
 * ²Î¿¼ http://www.tutorialspoint.com/java/java_networking.htm
 * @author chunhuachen@scut.edu.cn
 *
 */
public class SingleTCPClient {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		String serverName = args[0];
		int port = Integer.parseInt(args[1]);
		try {
			System.out.println("Connecting to " + serverName + " on port "
					+ port);
			Socket client = new Socket(serverName, port);
			System.out.println("Just connected to "
					+ client.getRemoteSocketAddress());
			
			OutputStream outToServer = client.getOutputStream();
			DataOutputStream out = new DataOutputStream(outToServer);

			out.writeUTF("Hello from " + client.getLocalSocketAddress());
			
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
