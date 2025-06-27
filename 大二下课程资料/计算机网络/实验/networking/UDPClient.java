
import java.io.IOException;
import java.io.InterruptedIOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


/**
 * �ο� http://blog.csdn.net/ns_code/article/details/14128987
 * @author chunhuachen@scut.edu.cn
 *
 */
public class UDPClient {
	private static final int TIMEOUT = 10000;  //���ý������ݵĳ�ʱʱ��
	private static final int MAXNUM = 5;      //�����ط����ݵ�������
	public static void main(String args[])throws IOException{
		String serverName = args[0];
		String str_send = "Hello UDPserver";
		byte[] buf = new byte[1024];
		//�ͻ�����9000�˿ڼ������յ�������
		DatagramSocket socket = new DatagramSocket(9000);
		InetAddress host = InetAddress.getByName(serverName);
		//���������������ݵ�DatagramPacketʵ��
		DatagramPacket packet_send= new DatagramPacket(str_send.getBytes(),str_send.length(),host,3000);
		//���������������ݵ�DatagramPacketʵ��
		DatagramPacket packet_receive = new DatagramPacket(buf, 1024);
		//���ݷ��������3000�˿�
		socket.setSoTimeout(TIMEOUT);              //���ý�������ʱ�������ʱ��
		int tries = 0;                         //�ط����ݵĴ���
		boolean receivedResponse = false;     //�Ƿ���յ����ݵı�־λ
		//ֱ�����յ����ݣ������ط������ﵽԤ��ֵ�����˳�ѭ��
		while(!receivedResponse && tries<MAXNUM){
			//��������
			socket.send(packet_send);
			try{
				//���մӷ���˷��ͻ���������
				//receive()����û�з���void
				//ע��Ƚ�TCP�е�accept()
				socket.receive(packet_receive);
				//������յ������ݲ�������Ŀ���ַ�����׳��쳣
				if(!packet_receive.getAddress().equals(host)){
					throw new IOException("Received packet from an umknown source");
				}
				//������յ����ݡ���receivedResponse��־λ��Ϊtrue���Ӷ��˳�ѭ��
				receivedResponse = true;
			}catch(InterruptedIOException e){
				//�����������ʱ������ʱ���ط�������һ���ط��Ĵ���
				tries += 1;
				System.out.println("Time out," + (MAXNUM - tries) + " more tries..." );
			}
		}
		if(receivedResponse){
			//����յ����ݣ����ӡ����
			System.out.println("client received data from server��"+packet_receive.getSocketAddress());
			String str_receive = new String(packet_receive.getData(),0,packet_receive.getLength()) + 
					" from " + packet_receive.getAddress().getHostAddress() + ":" + packet_receive.getPort();
			System.out.println(str_receive);
			//����packet_receive�ڽ���������֮�����ڲ���Ϣ����ֵ���Ϊʵ�ʽ��յ���Ϣ���ֽ�����
			//��������Ҫ��packet_receive���ڲ���Ϣ����������Ϊ1024
			packet_receive.setLength(1024);   
		}else{
			//����ط�MAXNUM�����ݺ���δ��÷��������ͻ��������ݣ����ӡ������Ϣ
			System.out.println("No response -- give up.");
		}
		socket.close();
	}  
} 