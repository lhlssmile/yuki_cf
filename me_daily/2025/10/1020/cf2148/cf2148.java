import java.util.*;
import java.io.*;

public class cf2148 {
    static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter pw = new PrintWriter(System.out);
    static StringTokenizer st;
    
    static String next() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }
    
    static int nextInt() throws IOException {
        return Integer.parseInt(next());
    }
    
    static long nextLong() throws IOException {
        return Long.parseLong(next());
    }
    
    static long solve(long[] a) {
        List<Long> odds = new ArrayList<>();
        List<Long> evens = new ArrayList<>();
        long sumE = 0;
        
        for (long x : a) {
            if (x % 2 == 0) {
                evens.add(x);
                sumE += x;
            } else {
                odds.add(x);
            }
        }
        
        int k = odds.size();
        if (k == 0) return 0;
        
        Collections.sort(odds);
        
        long sumO = 0;
        for (long x : odds) {
            sumO += x;
        }
        
        int sac = k / 2;
        long sumSac = 0;
        for (int i = 0; i < sac; i++) {
            sumSac += odds.get(i);
        }
        
        return sumO - sumSac + sumE;
    }
    
    public static void main(String[] args) throws IOException {
        int t = nextInt();
        
        while (t-- > 0) {
            int n = nextInt();
            long[] a = new long[n];
            for (int i = 0; i < n; i++) {
                a[i] = nextLong();
            }
            
            long ans = solve(a);
            pw.println(ans);
        }
        
        pw.close();
    }
}