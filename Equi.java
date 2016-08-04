// For http://blog.codility.com/2011/03/solutions-for-task-equi.html
public class Equi {
    public int solution(int[] A) {
        // write your code in Java SE 8
        int len = A.length;
        long[] fromStart = new long[len];
        long[] fromEnd = new long[len];
        for (int i = 0; i < len; i++) {
            fromStart[i] = A[i] + ((i == 0) ? 0 : fromStart[i - 1]);
            fromEnd[len - 1 - i] = A[len - 1 - i] + ((i == 0) ? 0 : fromEnd[len - i]);
        }
        for (int i = 0; i < A.length; i++) {
            if (i == 0 && fromEnd[i] - A[i] == 0) {
                return i;
            }
            if (i == len - 1 && fromStart[i] - A[i] == 0) {
                return i;
            }
            if (fromStart[i] == fromEnd[i]) {
                return i;
            }
        }
        return -1;
    }

    public static void main(String[] args) {
        new Equi().solution(new int[]{1, 2, 3});
    }
}
