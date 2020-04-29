// package cn.edu.ccnu.cs;

class TicketStock {
	private int num;      // the count of tickets

	public TicketStock() {
		num = 0;
	}
	public TicketStock(int num) {
		this.num = num;
	}

	public synchronized int sell(int n) {
		num -= n;
		return num;
	}
}

class SellWorker implements Runnable {
	private String      name = null;
	private TicketStock ts = null;
	public SellWorker(String name, TicketStock ts) {
		this.name = name;
		this.ts = ts;
	}

	public void run() {
		int remainTicket;
		while (true) {
			remainTicket = ts.sell(10);
			if (remainTicket >= 0)
				System.out.println("Seller:" + name + " sells one ticket, left " + remainTicket);
			else
				break;

			try {
				Thread.sleep(500 + (int)(Math.random() * 2000));
			} catch (Exception e) {
			}
		}
	}
}

public class ThreadMain {
	public static void main(String[] args) {
		Thread[] tt = new Thread[10];
		TicketStock ts = new TicketStock(200);
		// Create the threads
		for (int i = 0; i < tt.length; i ++) {
			tt[i] = new Thread(new SellWorker("S" + i, ts));
		}

		// Start those threads
		for (int i = 0; i < tt.length; i ++) {
			tt[i].start();
		}

		// Wait for the threads to stop
		for (int i = 0; i < tt.length; i ++) {
			try {
				tt[i].join();
			} catch (Exception e) {
			}
		}

		// Print the ending sign
		System.out.println("Tickets are sold out!");
	}

}
