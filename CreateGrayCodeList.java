import java.util.*;

/**
 * Created by anneyu on 6/17/16.
 * Generate gray code with n as input,
 * 000, 001, 011, 111 etc.
 */
public class CreateGrayCodeList {
  private static List<Integer> createGrayCode(final int n, List<Integer> currGrayCode, Set<Integer> countTable) {
    if (currGrayCode.size() == (1 << n)) {
      return currGrayCode;
    }
    int lastGrayCode = currGrayCode.get(currGrayCode.size() - 1);
    System.out.println("lastGrayCode = ");
    printBits(lastGrayCode, n);
    for (int i = 0; i < n; i++) {
      int newGrayCode = lastGrayCode ^ (1 << i);
      System.out.println("Trying grayCode = ");
      printBits(newGrayCode, n);
      if (!countTable.contains(newGrayCode)) {
        currGrayCode.add(newGrayCode);
        countTable.add(newGrayCode);
        System.out.println("Found newGrayCode = ");
        printBits(newGrayCode, n);
        List<Integer> newGrayCodeList = createGrayCode(n, currGrayCode, countTable);
        if (newGrayCodeList != null) {
          return newGrayCodeList;
        }
        currGrayCode.remove(currGrayCode.size() - 1);
        countTable.remove(newGrayCode);
      }
    }
    return null;
  }

  private static void printBits(final int val, final int n) {
    int x = val;
    String valStr = "";
    for (int j = n - 1; j >= 0; j--) {
      if ((x & (1 << j)) > 0) {
        valStr += "1";
      } else {
        valStr += "0";
      }
    }
    System.out.println(valStr);
  }

  private static List<String> createGrayCode2(final int n) {
    List<String> grayCode = new ArrayList<>(Arrays.asList("0", "1"));
    for (int i = 1; i < n; i++) {
      List<String> newGrayCode = new ArrayList<>();
      for (String code : grayCode) {
        newGrayCode.add("0" + code);
      }
      Collections.reverse(grayCode);
      for (String code : grayCode) {
        newGrayCode.add("1" + code);
      }
      System.out.println("i = " + i);
      System.out.println("grayCode = " + grayCode.toString());
      System.out.println("newGrayCode = " + newGrayCode.toString());
      grayCode.clear();
      grayCode.addAll(newGrayCode);
      //grayCode = newGrayCode;
    }
    return grayCode;
  }

  public static void main(String[] args) {
    System.out.println("CreateGrayCodeList main func");
    final int N = 4;

    /*
    for (int n = N; n <= N; n ++) {
      List<Integer> currGrayCode = new ArrayList<>();
      currGrayCode.add(0);
      Set<Integer> countTable = new HashSet<>();
      countTable.add(0);
      List<Integer> grayCode = createGrayCode(n, currGrayCode, countTable);
      System.out.println("++++++++++++++++Final gray code list1++++++++++++++++");
      Collections.sort(grayCode);
      for (int i : grayCode) {
        printBits(i, n);
      }
      */

    List<String> grayCode2 = createGrayCode2(N);
    System.out.println("++++++++++++++++Final gray code list2++++++++++++++++");
    System.out.println(grayCode2.toString());
  }
}
