/**
 * Created by anneyu on 6/22/16.
 * Practice read and write locks using ReentrantReadWriteLock
 */
import java.util.Map;
import java.util.HashMap;
import java.util.concurrent.Callable;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.stream.IntStream;

public class TestReadWriteLock {
  private final static int MAP_SIZE = 100;
  private final static int POOL_SIZE = 100;
  private Map<String, String> map = new HashMap<>(MAP_SIZE);
  private ExecutorService pool = Executors.newFixedThreadPool(POOL_SIZE);
  private ReadWriteLock lock = new ReentrantReadWriteLock();

  TestReadWriteLock() {

  }

  public String read(String key) {
    Callable task = () -> {
      lock.readLock().lock();
      try {
        System.out.println(Thread.currentThread().getName() + ": read");
        if (map.containsKey(key)) {
          return map.get(key);
        } else {
          return null;
        }
      } finally {
        lock.readLock().unlock();
      }
    };
    Future<String> future = pool.submit(task);
    if (future.isDone()) {
      try {
        String result = future.get(1, TimeUnit.SECONDS);
        return result;
      } catch (Exception ex) {
        return null;
      }
    } else {
      return null;
    }
  }

  /**
   *
   * @param key
   * @param val
   * @return old_val or null if none
   */
  public String write(String key, String val) {
    Callable task = () -> {
      lock.writeLock().lock();
      try {
        System.out.println(Thread.currentThread().getName() + ": write");
        if (map.containsKey(key)) {
          return map.get(key);
        } else {
          map.put(key, val);
          return null;
        }
      } finally {
         lock.writeLock().unlock();
      }
    };
    Future<String> future = pool.submit(task);
    if (future.isDone()) {
      try {
        String result = future.get(1, TimeUnit.SECONDS);
        return result;
      } catch (Exception ex) {
        return null;
      }
    } else {
      return null;
    }
  }

  public void shutdownAndWaitForTermination() {
    pool.shutdown();
    try {
      if (!pool.awaitTermination(15, TimeUnit.SECONDS)) {
        pool.shutdownNow();
        if (!pool.awaitTermination(15, TimeUnit.SECONDS)) {
          System.err.println("can not terminate threads");
        }
      }
    } catch (InterruptedException ex) {
      pool.shutdownNow();
      Thread.currentThread().interrupt();
    }
  }

  public static void main(String[] args) {
    TestReadWriteLock testReadWriteLock = new TestReadWriteLock();
    ExecutorService testPool = Executors.newFixedThreadPool(10);
    IntStream.range(1, 100)
        .forEach(i -> {
          int r = 1 + (int)(Math.random() * ((100 - 1) + 1));
          if ((r & 1) == 1) {
            String key = "key" + String.valueOf(i);
            String val = "val" + String.valueOf(i);
            System.out.println("writing " + key + " = " + val + ", original val = " + testReadWriteLock.write(key, val));
          } else {
            String key = "key" + String.valueOf(i);
            System.out.println("reading " + key + " = " + testReadWriteLock.read(key));
          }
        });
    testReadWriteLock.shutdownAndWaitForTermination();
  }
}
