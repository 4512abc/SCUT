import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketTimeoutException;

/**
 * �ο� http://blog.csdn.net/ns_code/article/details/14128987
 * 
 * @author chunhuachen@scut.edu.cn
 * 
 */
public class UDPServer {
	private static final int TIMEOUT = 10000; // ���ý������ݵĳ�ʱʱ��

	public static void main(String[] args) throws IOException {
		String str_send = "Hello UDPclient";
		byte[] buf = new byte[1024];
		// �������3000�˿ڼ������յ������ݣ�����ϵͳ����buffer��
		DatagramSocket socket = new DatagramSocket(3000);
		// ���մӿͻ��˷��͹��������� (�û��ռ�)
		DatagramPacket packet_receive = new DatagramPacket(buf, 1024);
		socket.setSoTimeout(TIMEOUT); // ���ý�������ʱ�������ʱ��
		System.out
				.println("server is on��waiting for client to send data......");
		boolean f = true;
		while (f) {
			try {
				// �������˽������Կͻ��˵�����
				// receive()����û�з���void
				// ע��Ƚ�TCP�е�accept()
				socket.receive(packet_receive);
				System.out.println("server received data from client��"
						+ packet_receive.getSocketAddress());
				String str_receive = new String(packet_receive.getData(), 0,
						packet_receive.getLength())
						+ " from "
						+ packet_receive.getAddress().getHostAddress()
						+ ":"
						+ packet_receive.getPort();
				System.out.println(str_receive);
				// ���ݷ������ͻ��˵�9000�˿�
				DatagramPacket packet_send = new DatagramPacket(
						str_send.getBytes(), str_send.length(),
						packet_receive.getAddress(), 9000);
				socket.send(packet_send);
				// ����packet_receive�ڽ���������֮�����ڲ���Ϣ����ֵ���Ϊʵ�ʽ��յ���Ϣ���ֽ�����
				// ��������Ҫ��packet_receive���ڲ���Ϣ����������Ϊ1024
				packet_receive.setLength(1024);
			} catch (SocketTimeoutException e) {
				f = false;
			}
		}
		socket.close();
		System.out.println("server stoped");
	}
}
