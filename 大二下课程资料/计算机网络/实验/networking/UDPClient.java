
import java.io.IOException;
import java.io.InterruptedIOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


/**
 * 参考 http://blog.csdn.net/ns_code/article/details/14128987
 * @author chunhuachen@scut.edu.cn
 *
 */
public class UDPClient {
	private static final int TIMEOUT = 10000;  //设置接收数据的超时时间
	private static final int MAXNUM = 5;      //设置重发数据的最多次数
	public static void main(String args[])throws IOException{
		String serverName = args[0];
		String str_send = "Hello UDPserver";
		byte[] buf = new byte[1024];
		//客户端在9000端口监听接收到的数据
		DatagramSocket socket = new DatagramSocket(9000);
		InetAddress host = InetAddress.getByName(serverName);
		//定义用来发送数据的DatagramPacket实例
		DatagramPacket packet_send= new DatagramPacket(str_send.getBytes(),str_send.length(),host,3000);
		//定义用来接收数据的DatagramPacket实例
		DatagramPacket packet_receive = new DatagramPacket(buf, 1024);
		//数据发向服务器3000端口
		socket.setSoTimeout(TIMEOUT);              //设置接收数据时阻塞的最长时间
		int tries = 0;                         //重发数据的次数
		boolean receivedResponse = false;     //是否接收到数据的标志位
		//直到接收到数据，或者重发次数达到预定值，则退出循环
		while(!receivedResponse && tries<MAXNUM){
			//发送数据
			socket.send(packet_send);
			try{
				//接收从服务端发送回来的数据
				//receive()函数没有返回void
				//注意比较TCP中的accept()
				socket.receive(packet_receive);
				//如果接收到的数据不是来自目标地址，则抛出异常
				if(!packet_receive.getAddress().equals(host)){
					throw new IOException("Received packet from an umknown source");
				}
				//如果接收到数据。则将receivedResponse标志位改为true，从而退出循环
				receivedResponse = true;
			}catch(InterruptedIOException e){
				//如果接收数据时阻塞超时，重发并减少一次重发的次数
				tries += 1;
				System.out.println("Time out," + (MAXNUM - tries) + " more tries..." );
			}
		}
		if(receivedResponse){
			//如果收到数据，则打印出来
			System.out.println("client received data from server："+packet_receive.getSocketAddress());
			String str_receive = new String(packet_receive.getData(),0,packet_receive.getLength()) + 
					" from " + packet_receive.getAddress().getHostAddress() + ":" + packet_receive.getPort();
			System.out.println(str_receive);
			//由于packet_receive在接收了数据之后，其内部消息长度值会变为实际接收的消息的字节数，
			//所以这里要将packet_receive的内部消息长度重新置为1024
			packet_receive.setLength(1024);   
		}else{
			//如果重发MAXNUM次数据后，仍未获得服务器发送回来的数据，则打印如下信息
			System.out.println("No response -- give up.");
		}
		socket.close();
	}  
} 