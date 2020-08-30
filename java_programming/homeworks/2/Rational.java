// 定义一个Rational类（有理数），包含2个私有成员：分子a和分母b
// 为该类定义四个基本函数：
// add（加一个有理数），sub（减去一个有理数），mul（乘一个有理数），div（除以一个有理数），show （显示有理数），

public class Rational {
    private int a, b; // 分子a，分母b

    public Rational(int a, int b) {
        this.a = a;
        this.b = b;
        // 负号移到分子上
        if (b < 0) {
            a *= -1;
            b *= -1;
        }
    }

    // 加
    public Rational add(Rational r) {
        Rational data = new Rational(a*r.b + b*r.a, b * r.b);
        data.simplify();
        return data;
    }

    // 减
    public Rational sub(Rational r) {
        Rational data = new Rational(a*r.b - b*r.a, b * r.b);
        data.simplify();
        return data;
    }

    // 乘
    public Rational mul(Rational r) {
        Rational data = new Rational(a * r.a, b * r.b);
        data.simplify();
        return data;
    }

    // 除
    public Rational div(Rational r) {
        Rational data = new Rational(a * r.b, b * r.a);
        data.simplify();
        return data;
    }

    public void show() {
        if (b == 1)      System.out.println(a);
        else if (a == 0) System.out.println(0);
        else             System.out.println(a + "/" + b);
    }

    // 分数化简
    private void simplify() {
        // 负号移到分子上
        if (b < 0) {
            a *= -1;
            b *= -1;
        }
        // 暂时将a作正数处理
        boolean neg = false;
        if (a < 0) {
            neg = true;
            a = -a;
        }

        int n, x = a, y = b;
        // 交换
        if (x < y) {
            x ^= y;
            y ^= x;
            x ^= y;
        }
        // 求最大公约数
        while (y > 0) {
            n = x % y;
            x = y;
            y = n;
        }
        // 化简
        a /= x;
        b /= x;
        if (neg) a = -a;
    }

    // 主函数，并计算如下运算结果
    public static void main(String[] args) {
        Rational r1 = new Rational(3, 5);
        Rational r2 = new Rational(4, 7);
        Rational res;
        res = r1.add(r2);
        res.show();
        res = r1.sub(r2);
        res.show();
        res = r1.mul(r2);
        res.show();
        res = r1.div(r2);
        res.show();
    }
}