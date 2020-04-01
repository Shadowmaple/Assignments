// package cn.edu.ccnu.cs;

import java.util.Scanner;

public class Equation {
	public static Resolution resolve(double a, double b, double c) throws WrongParameterException, NoResolutionException {
		if (a == 0) {
			// 一元二次方程系数不为0
			throw new WrongParameterException("一元二次方程最高项系数不能为0！");
		}
		double delta = b * b - 4 * a * c;
		if (delta < 0) {
			// 无实数解
			throw new NoResolutionException("无实数解");
		}

		Resolution r = new Resolution();
		r.x1 = (-b + Math.sqrt(delta)) / (2 * a);
		r.x2 = (-b - Math.sqrt(delta)) / (2 * a);

		return r;
	}

	public static void main(String[] args) throws Exception {
		System.out.println("请输入一元二次方程的三个系数: ");
		double a, b, c;
		Scanner scanner = new Scanner(System.in);
		a = scanner.nextDouble();
		b = scanner.nextDouble();
		c = scanner.nextDouble();

		System.out.printf("一元二次方程为: %.1fx^2 + %.1fx + %.1f = 0\n", a, b, c);
		try
		{
			Resolution r = Equation.resolve(a, b, c);
			System.out.println("一元二次方程有两实数根, x1=" + r.x1 + ", x2=" + r.x2);
		} catch (WrongParameterException w) {
			// 系数错误
			System.out.println(w.getMessage());
		} catch (NoResolutionException n) {
			// 无实数解
			System.out.println(n.getMessage());
		} catch (Exception ex) {
			throw ex;
		}
	}
}

class Resolution {
	double x1;
	double x2;
}

// 定义异常类  WrongParameterException
class WrongParameterException extends Exception {
	public WrongParameterException(String message) {
		super(message);
	}
}

// 定义异常类 NoResolutionException
class NoResolutionException extends Exception {
	public NoResolutionException(String message) {
		super(message);
	}
}
