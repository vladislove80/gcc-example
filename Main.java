/**
 * Created by Vladyslav on 16.09.2015.
 */
import java.util.Date;
import java.io.*;

public class Fibonachi {
    //Iteration
    public static int fib_iterativ(int n) {
        int fn0 = 0;
        int fn1 = 1;
        int fn2 = 0;
        if(n==0) return fn0;
        if(n==1) return fn1;

        for(int i=2; i<(n+1); i++) {
            fn2 = fn0 + fn1;
            fn0 = fn1;
            fn1 = fn2;
        }
        return fn2;
    }

    //Recursion
    public static int fib_recursive(int n) {
        if ( n == 0 || n == 1 ) return(n);
        return(fib_recursive(n-1) + fib_recursive(n-2));
    }

    public static void main(String[] args) throws FileNotFoundException {
        final int numOfNum = 40;
        long result;
        long before, after, currentTime;
        double methodTime;

        //file
        File file = new File("result.dat");

        before = System.nanoTime();
        result = fib_iterativ(numOfNum);
        after = System.nanoTime();
        currentTime = after - before;
        methodTime = currentTime/1000000000.0;
        String textIterative = "iterative time " + methodTime + " s, result " + result;

        before = System.currentTimeMillis();
        result = fib_recursive(numOfNum);
        after = System.currentTimeMillis();
        currentTime = after - before;
        methodTime = currentTime/1000.0;
        String textRecursive = "recursive time " + methodTime + " s, results " + result;


        try {
            //check file exist
            if(!file.exists()){
                file.createNewFile();
            }

            //PrintWriter provides logging features
            PrintWriter out = new PrintWriter(file.getAbsoluteFile());

            try {
                //text to file
                out.println(textIterative);
                out.println(textRecursive);
            } finally {
                //file close
                out.close();
            }
        } catch(IOException e) {
            throw new RuntimeException(e);
        }
    }
}
