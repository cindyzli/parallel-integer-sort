package generate;

import java.util.Random;

class NumberGenerator {
    static int N = 100_000;
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