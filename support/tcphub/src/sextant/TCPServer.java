package sextant;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {

	private Socket socket;
	protected Reader reader;
	protected Writer writer;

	public static void main(String args[]) throws Exception {
		if (args.length != 1) {
			System.err.println("Wrong number of arguments.");
			System.err.println("Usage: java sextant.TCPServer port");
			System.exit(0);
		}
		int port = Integer.parseInt(args[0]);
		ServerSocket serverSocket = new ServerSocket(port);
		System.out.println("TCP Server ready on port " + port + ".");
		while (true) {
			final Socket socket = serverSocket.accept();
			System.out.println("Connected to "
					+ socket.getInetAddress().getCanonicalHostName() + ":"
					+ socket.getPort());
			TCPServer server = new TCPServer(socket);
			Thread wt = new Thread(server.writer);
			Thread rt = new Thread(server.reader);
			wt.start();
			rt.start();
			rt.join();
			System.out.println("Press enter to reinitialize.");
			wt.join();
			System.out.println("TCP Server ready on port "
					+ socket.getLocalPort() + ".");
		}
	}

	public TCPServer(Socket socket) {
		this.socket = socket;
		this.reader = new Reader();
		this.writer = new Writer();
	}

	class Reader implements Runnable {

		public final static int MAX_BUFFER_SIZE = 4096;

		public void run() {
			try {
				InputStream is = socket.getInputStream();
				byte[] buffer = new byte[MAX_BUFFER_SIZE];
				int b = 0;
				while ((b = is.read(buffer)) != -1) {
					System.out.println("Message received: "
							+ new String(buffer, 0, b) + "\n");
				}
			} catch (IOException e) {
				System.err.println(e.getMessage());
			} finally {
				try {
					System.out.println("Unable to reach client.");
					socket.close();
				} catch (IOException e) {
				}
			}
		}
	}

	class Writer implements Runnable {

		public void run() {
			try {
				while (true) {
					System.out.println("Please enter a message to send:");
					BufferedReader br = new BufferedReader(
							new InputStreamReader(System.in));
					String line = br.readLine();
					DataOutputStream outToClient = new DataOutputStream(socket
							.getOutputStream());
					outToClient.writeBytes(line);
					System.out.println("Message sent.\n");
				}
			} catch (IOException e) {
				System.err.println(e.getMessage());
			} finally {
				try {
					socket.close();
				} catch (IOException e) {
				}
			}
		}
	}
}