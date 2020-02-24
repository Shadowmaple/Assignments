// 题目：输入一元二次方程三个参数a，b，c，利用韦达定理求两个解
// 时间：2020.2.24

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("请输入三个整数a, b和c：");
        int a = input.nextInt();
        int b = input.nextInt();
        int c = input.nextInt();
        // System.out.printf("%d %d %d\n", a, b, c);

        int v = b*b - 4*a*c;
        if (v < 0) {
            System.out.println("无实数解");
            return ;
        }

        double x1 = (-b + Math.sqrt(v)) / (2*a);
        double x2 = (-b - Math.sqrt(v)) / (2*a);
        System.out.printf("解：x1 = %f, x2 = %f\n", x1, x2);
    }
}