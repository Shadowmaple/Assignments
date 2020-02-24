// 题目：输入一元二次方程三个参数a，b，c，利用韦达定理求两个解
// 时间：2020.2.24

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.println("请输入三个数a, b和c：");
        double a = input.nextDouble();
        double b = input.nextDouble();
        double c = input.nextDouble();
        input.close();

        if (a == 0) {
            System.out.println("一元二次方程参数a不能为0");
            return ;
        }

        double v = b*b - 4*a*c;
        if (v < 0) {
            System.out.println("无实数解");
            return ;
        }

        double x1 = (-b + Math.sqrt(v)) / (2*a);
        double x2 = (-b - Math.sqrt(v)) / (2*a);
        System.out.printf("解：x1 = %f, x2 = %f\n", x1, x2);
    }
}