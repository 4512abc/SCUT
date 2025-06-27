import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketTimeoutException;

/**
 * 参考 http://blog.csdn.net/ns_code/article/details/14128987
 * 
 * @author chunhuachen@scut.edu.cn
 * 
 */
public class UDPServer {
	private static final int TIMEOUT = 10000; // 设置接收数据的超时时间

	public static void main(String[] args) throws IOException {
		String str_send = "Hello UDPclient";
		byte[] buf = new byte[1024];
		// 服务端在3000端口监听接收到的数据（操作系统创建buffer）
		DatagramSocket socket = new DatagramSocket(3000);
		// 接收从客户端发送过来的数据 (用户空间)
		DatagramPacket packet_receive = new DatagramPacket(buf, 1024);
		socket.setSoTimeout(TIMEOUT); // 设置接收数据时阻塞的最长时间
		System.out
				.println("server is on，waiting for client to send data......");
		boolean f = true;
		while (f) {
			try {
				// 服务器端接收来自客户端的数据
				// receive()函数没有返回void
				// 注意比较TCP中的accept()
				socket.receive(packet_receive);
				System.out.println("server received data from client："
						+ packet_receive.getSocketAddress());
				String str_receive = new String(packet_receive.getData(), 0,
						packet_receive.getLength())
						+ " from "
						+ packet_receive.getAddress().getHostAddress()
						+ ":"
						+ packet_receive.getPort();
				System.out.println(str_receive);
				// 数据发动到客户端的9000端口
				DatagramPacket packet_send = new DatagramPacket(
						str_send.getBytes(), str_send.length(),
						packet_receive.getAddress(), 9000);
				socket.send(packet_send);
				// 由于packet_receive在接收了数据之后，其内部消息长度值会变为实际接收的消息的字节数，
				// 所以这里要将packet_receive的内部消息长度重新置为1024
				packet_receive.setLength(1024);
			} catch (SocketTimeoutException e) {
				f = false;
			}
		}
		socket.close();
		System.out.println("server stoped");
	}
}
