package sextant;

import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;
import java.net.SocketException;

public class TCPHub implements Runnable {

	private Socket[] sockets;
	private String[] hosts;
	private int[] ports;
	private int index;
	public final static int MAX_BUFFER_SIZE = 4096;
	public final static int WAITING_TIME = 5000;

	public static void main(String args[]) {
		if (args.length < 2 || args.length % 2 != 0) {
			System.err.println("Wrong number of arguments.");
			System.err
					.println("Usage: java sextant.TCPHub server1Host1 server1Port ... servernHost servernPort");
			System.exit(0);
		}
		int nbServers = args.length / 2;
		Socket[] sockets = new Socket[nbServers];
		String[] hosts = new String[nbServers];
		int[] ports = new int[nbServers];
		for (int i = 0; i < nbServers; i++) {
			// Initialize host names and ports
			hosts[i] = args[(i * 2)];
			ports[i] = Integer.parseInt(args[(i * 2) + 1]);
			try {
				// Create all client sockets
				sockets[i] = new Socket(hosts[i], ports[i]);
			} catch (IOException e) {
				// In case of failure, sockets[i] == null
				System.err.println(e.getMessage() + ". Unable to reach "
						+ hosts[i] + ":" + ports[i]);
			}
		}
		for (int i = 0; i < sockets.length; i++) {
			// Create and start a thread for each client socket
			new Thread(new TCPHub(sockets, hosts, ports, i)).start();
		}

		System.out.println("TCP hub started.");
	}

	public TCPHub(final Socket[] sockets, final String[] hosts,
			final int[] ports, final int index) {
		this.sockets = sockets;
		this.hosts = hosts;
		this.ports = ports;
		this.index = index;
	}

	public void run() {
		String inHost = hosts[index] + ":" + ports[index];
		while (true) {
			try {
				if (sockets[index] == null || sockets[index].isClosed()) {
					// The sending server cannot be reached, wait before
					// retrying to
					// connect
					try {
						Thread.sleep(WAITING_TIME);
					} catch (InterruptedException e) {

					}
					System.out.println("Trying to connect to " + inHost + ".");
					sockets[index] = new Socket(hosts[index], ports[index]);
					System.out.println("Connection to " + inHost
							+ " succeeded.");
				}
				InputStream is = sockets[index].getInputStream();
				byte[] buffer = new byte[MAX_BUFFER_SIZE];
				int b = 0;
				while ((b = is.read(buffer)) != -1) {
					System.out.println("Receiving data from " + inHost + ": "
							+ String.valueOf(new String(buffer, 0, b)));
					// Forward the data from the sending server to other servers
					for (int i = 0; i < sockets.length; i++) {
						if (i != index) {
							String outHost = hosts[i] + ":" + ports[i];
							System.out.println("Sending data to " + outHost
									+ ": "
									+ String.valueOf(new String(buffer, 0, b)));
							try {
								if (sockets[i] == null || sockets[i].isClosed()) {
									// The receiving server is not connected,
									// try to connect
									sockets[i] = new Socket(hosts[i], ports[i]);
								}
								sockets[i].getOutputStream()
										.write(buffer, 0, b);
							} catch (SocketException se) {
								// The receiving server is unreachable
								System.err.println(se.getMessage()
										+ ". Unable to reach " + outHost);
								try {
									if (sockets[i] != null)
										sockets[i].close();
								} catch (IOException e) {

								}
							}
						}
					}
				}
				// The sending server is disconnected
				System.err.println("Connection closed with " + inHost + ".");
			} catch (IOException e) {
				System.err.println(e.getMessage() + ". Unable to reach "
						+ inHost + ".");
			} finally {
				try {
					if (sockets[index] != null)
						sockets[index].close();
				} catch (IOException e) {
				}
			}
		}
	}
}
