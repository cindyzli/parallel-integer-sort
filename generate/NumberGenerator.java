package generate;

import java.util.Random;

class NumberGenerator {
    // static int N = 1_000_000;
    static int N = 10000;
    public static void main (String[] args) {
        if (args.length > 0) {
            N = Integer.parseInt(args[0]);
        }
        Random gen = new Random();
        for (int i = 0; i < N; i++) {
            System.out.println(gen.nextInt());
        }
    }
}