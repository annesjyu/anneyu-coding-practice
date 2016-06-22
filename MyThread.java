import java.util.concurrent.*;
import java.util.Arrays;
import java.util.List;

/**
 * Created by anneyu on 6/19/16.
 * Implement a couple of concurrency examples in JDK8
 * Thread, Callable, Runnable, ExecutorService,
 * ScheduledExecutorService
 */
public class MyThread {

  private static void tryThreadClass() {
    Runnable runnable = () -> {
      try {
        String name = Thread.currentThread().getName();
        System.out.println("start tryThreadClass thread name = " + name);
        TimeUnit.SECONDS.sleep(1);
        System.out.println("end tryThreadClass thread name = " + name);
      } catch (InterruptedException ex) {
        ex.printStackTrace();
      }
    };
    Thread thread = new Thread(runnable);
    thread.start();
  }

  private static void tryExectuorService() {
    ExecutorService executor = Executors.newSingleThreadExecutor();
    executor.submit(() -> {
      String threadName = Thread.currentThread().getName();
      System.out.println(threadName);
    });
    try {
      System.out.println("attempt to shutdown executor");
      executor.shutdown();
      executor.awaitTermination(5, TimeUnit.SECONDS);
    } catch (InterruptedException ex) {
      ex.printStackTrace();
      System.err.println("tasks interrupted");
    } finally {
      if (!executor.isTerminated()) {
        System.err.println("cancel non-finished tasks");
      }
      executor.shutdownNow();
      System.out.println("shutdown finished");
    }
  }

  private static void tryCallable() {
    Callable<String> task = () -> {
      try {
        TimeUnit.SECONDS.sleep(1);
        return "thread name [" + Thread.currentThread().getName() + "]";
      } catch (InterruptedException ex) {
        throw new IllegalStateException("task interrupted", ex);
      }
    };
    ExecutorService executor = Executors.newFixedThreadPool(1);
    Future<String> future = executor.submit(task);
    //System.out.println("attempt to shutdown executor");
    //executor.shutdown();
    try {
      System.out.println("future done? " + future.isDone());
      String result = future.get(1, TimeUnit.SECONDS);
      System.out.println("future done? " + future.isDone());
      System.out.println("result = " + result);
    } catch (ExecutionException|InterruptedException|TimeoutException ex) {
      System.err.println("callable task exception: " + ex);
    }
  }

  private static void tryInvokeAll() {
    ExecutorService executor = Executors.newWorkStealingPool();
    List<Callable<String>> callables = Arrays.asList(
        () -> "task1",
        () -> "task2",
        () -> "task3");
    try {
      executor.invokeAll(callables)
          .stream()
          .map(future -> {
            try {
              return future.get();
            } catch (Exception ex) {
              throw new IllegalStateException(ex);
            }
          })
          .forEach(System.out::println);
    } catch (InterruptedException ex) {
      System.err.println("callables exception = " + ex);
    }
  }

  private static Callable<String> callable(String threadName, long sleepSeconds) {
    try {
      TimeUnit.SECONDS.sleep(sleepSeconds);
      return new Callable<String>() {
        @Override
        public String call() throws Exception {
          System.out.println("running " + threadName);
          return Thread.currentThread().getName();
        }
      };
    } catch (InterruptedException ex) {
      System.err.println("callable exception = " + ex);
      return null;
    }
  }

  public static void testInvokeAny() {
    ExecutorService executor = Executors.newWorkStealingPool();
    List<Callable<String>> callables = Arrays.asList(
        callable("T1", 2),
        callable("T2", 1),
        callable("T3", 3));
    try {
      String result = executor.invokeAny(callables);
      System.out.println(result);
    } catch (InterruptedException | ExecutionException ex) {
      System.out.println("Exception " +  ex);
    }
  }

  public static void testScheduledExecutorService() throws InterruptedException {
    ScheduledExecutorService executor = Executors.newScheduledThreadPool(1);
    Runnable task = () -> System.out.println("scheduling: " + System.nanoTime());
    ScheduledFuture<?> future = executor.schedule(task, 3, TimeUnit.SECONDS);
    TimeUnit.MILLISECONDS.sleep(10);
    long remainingDelay = future.getDelay(TimeUnit.MILLISECONDS);
    System.out.printf("remaining delay: %sms\n", remainingDelay);
  }

  public static void testScheduledExecutorService2() throws InterruptedException {
    ScheduledExecutorService executor = Executors.newScheduledThreadPool(2);
    Runnable task = () -> {
      try {
        TimeUnit.SECONDS.sleep(2);
        System.out.println(Thread.currentThread().getName() + " scheduling: " + System.nanoTime());
      } catch (InterruptedException ex) {
        System.err.println("task interrupted");
      }
    };
    executor.scheduleWithFixedDelay(task, 0, 1, TimeUnit.SECONDS);
    TimeUnit.SECONDS.sleep(10);
    System.out.println("attempt shot down concurrent tasks");
    executor.shutdown();
  }

  public static void main(String[] args) throws InterruptedException {
    System.out.println("MyThread main func");
    //tryThreadClass();
    testScheduledExecutorService2();
  }
}
