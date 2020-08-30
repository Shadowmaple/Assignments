// package cn.edu.ccnu.cs;

// 编写程序，以不同的算法和不同的标准来对学生数组进行排序，以下是程序的基本框架（尽量遵守该框架）
import java.util.ArrayList;
import java.util.Collections;
// import java.util.LinkedList;
import java.util.List;
// import java.util.Vector;

// 添加类，或者完成省略号处的代码
// 接口与接口的关系是 继承  extends
interface Comparator extends java.util.Comparator<Student> {
    @Override
    public int compare(Student s1, Student s2);
}

interface Sorter {
    public void sort(List<Student> ss, Comparator c);
}

class Student {
    public int sno; // 学号
    public int chinese; // 语文成绩
    public int math; // 数学成绩
    public int english; // 英语成绩

    public Student(int sno, int chinese, int math, int english) {
        this.sno = sno;
        this.chinese = chinese;
        this.math = math;
        this.english = english;
    }

    public void show() {
        System.out.println("SNO:" + sno + "  C:" + chinese + "   M:" + math + "  E:" + english);
    }
}

// 用匿名内部类 或 lambda 表达式 替换
// class ChineseComparator implements Comparator;
// 用匿名内部类 或 lambda 表达式 替换
// class MathComparator implements Comparator;
// 用匿名内部类 或 lambda 表达式 替换
// class EnglishComparator implements Comparator;
class BubbleSorter implements Sorter {
    @Override
    public void sort(List<Student> ss, Comparator c) {
        for (int i = 0; i < ss.size()-1; i++) {
            for (int j = ss.size()-1; j > i; j--) {
                if (c.compare(ss.get(j), ss.get(j-1)) >= 0) {
                    Student temp = ss.get(j);
                    ss.set(j, ss.get(j-1));
                    ss.set(j-1, temp);
                }
            }
        }
    }
}

class QuickSorter implements Sorter {
    @Override
    public void sort(List<Student> ss, Comparator c) {
        quickSort(ss, c, 0, ss.size()-1);
    }

    protected void quickSort(List<Student> ss, Comparator c, int l, int r) {
        if (l >= r) return ;
        Student key = ss.get(l);
        int i = l, j = r;
        while (i < j) {
            while (c.compare(key,ss.get(j)) >= 0 && i < j) j--;
            if (i < j) ss.set(i, ss.get(j));
            while (c.compare(key, ss.get(i)) < 0 && i < j) i++;
            if (i < j) ss.set(j, ss.get(i));
        }
        ss.set(i, key);
        quickSort(ss, c, l, i - 1);
        quickSort(ss, c, i + 1, r);
	}
}

class SwtichSorter implements Sorter {
    @Override
    public void sort(List<Student> ss, Comparator c) {
        for (int i = 0; i < ss.size()-1; i++) {
            int k = i;
            for (int j = i+1; j < ss.size(); j++) {
                if (c.compare(ss.get(k), ss.get(j)) < 0)
                    k = j;
            }
            if (k != i) {
                Student temp = ss.get(k);
                ss.set(k, ss.get(i));
                ss.set(i, temp);
            }
        }
    }
}

public class StudentSorter {

    public static void main(String[] args) {
        // 定义数据
        int count = 1000;
        List<Student> ss = new ArrayList<Student>();
        // List<Student> ss = new Vector<Student>();
        // List<Student> ss = new LinkedList<Student>();

        for (int i = 0; i < count; i++) {
            Student s = new Student(i + 1, (int) (Math.random() * 100), (int) (Math.random() * 100),
                    (int) (Math.random() * 100));
            ss.add(s);
        }

        // 开始定义排序器：冒泡、快排、交换排序
        Sorter[] sorters = new Sorter[3];
        sorters[0] = new BubbleSorter();
        sorters[1] = new QuickSorter();
        sorters[2] = new SwtichSorter();

        // 开始定义比较器：语文 数学 英语
        Comparator[] comps = new Comparator[3];
        comps[0] = (s1, s2) -> (s1.chinese - s2.chinese);
        comps[1] = (s1, s2) -> (s1.math - s2.math);
        comps[2] = (s1, s2) -> (s1.english - s2.english);

        // 开始排序
        long now = 0;
        for (int i = 0; i < sorters.length; i++) {
            for (Comparator c : comps) {
                now = System.currentTimeMillis();
                sorters[i].sort(ss, c);
                System.out.println("Time:" + (System.currentTimeMillis() - now));
            }
        }

        for (Comparator c : comps) {
            now = System.currentTimeMillis();
            Collections.sort(ss, c);
            System.out.println("Time by Collections:" + (System.currentTimeMillis() - now));
        }
    }
}
