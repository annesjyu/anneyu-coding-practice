/**
 * Use wait and notify to synchronize two threads
 */
public class OddEvenThreads {
  public static final boolean ODD_TURN = true;
  public static final boolean EVEN_TURN = false;
  public boolean turn = ODD_TURN;

  private synchronized void waitTurn(boolean oldTurn) {
    while (turn != oldTurn) {
      try {
        wait();
      } catch (InterruptedException ex) {
        System.err.println("InterruptedException in wait(): " + ex);
      }
    }
  }

  private synchronized void toggleTurn() {
    turn ^= true;
    notify();
  }

  private static class OddThread extends Thread {
    private final OddEvenThreads monitor;

    public OddThread(OddEvenThreads monitor) { this.monitor = monitor; }
    @Override
    public void run() {
      for (int i = 1; i < 100; i += 2) {
        monitor.waitTurn(ODD_TURN);
        System.out.println("[ " + Thread.currentThread().getName() + "] i = " + i);
        monitor.toggleTurn();
      }
    }
  }

  private static class EventThread extends Thread {
    private final OddEvenThreads monitor;
    public EventThread(OddEvenThreads monitor) { this.monitor = monitor; }
    @Override
    public void run() {
      for (int i = 2; i <= 100; i += 2) {
        monitor.waitTurn(EVEN_TURN);
        System.out.println("[ " + Thread.currentThread().getName() + "] i = " + i);
        monitor.toggleTurn();
      }
    }
  }

  public static void main(String[] args) throws InterruptedException {
    OddEvenThreads monitor = new OddEvenThreads();
    Thread t1 = new OddThread(monitor);
    Thread t2 = new EventThread(monitor);
    t1.start();
    t2.start();
    t1.join();
    t2.join();
  }
}