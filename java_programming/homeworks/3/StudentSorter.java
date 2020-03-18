// package cn.edu.ccnu.cs;

// 编写程序，以不同的算法和不同的标准来对学生数组进行排序，以下是程序的基本框架（尽量遵守该框架）
// 添加类，或者完成省略号处的代码

interface Comparator {
	public int compare(Student s1, Student s2);
}

interface Sorter {
	public void sort(Student[] s, Comparator c);
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

class ChineseComparator implements Comparator {
	@Override
	public int compare(Student s1, Student s2) {
		if (s1.chinese > s2.chinese) return 1;
		return 0;
	}
}

class MathComparator implements Comparator {
	@Override
	public int compare(Student s1, Student s2) {
		if (s1.math > s2.math) return 1;
		return 0;
	}
}

class EnglishComparator implements Comparator {
	@Override
	public int compare(Student s1, Student s2) {
		if (s1.english > s2.english) return 1;
		return 0;
	}
}

class BubbleSorter implements Sorter {
	@Override
	public void sort(Student[] s, Comparator c) {
		for (int i = 0; i < s.length-1; i++) {
			for (int j = s.length-1; j > i; j--) {
				if (c.compare(s[j], s[j-1]) == 1) {
					Student temp = s[j];
					s[j] = s[j-1];
					s[j-1] = temp;
				}
			}
		}
	}
}

class QuickSorter implements Sorter {
	@Override
	public void sort(Student[] s, Comparator c) {
		quickSort(s, c, 0, s.length-1);
	}

	protected void quickSort(Student[] s, Comparator c, int l, int r) {
		if (l >= r) return ;
		Student key = s[l];
		int i = l, j = r;
		while (i < j) {
			while (c.compare(key, s[j]) == 1 && i < j) j--;
			if (i < j) s[i] = s[j];
			while (c.compare(key, s[i]) == 0 && i < j) i++;
			if (i < j) s[j] = s[i];
		}
		s[i] = key;
		quickSort(s, c, l, i - 1);
		quickSort(s, c, i + 1, r);
	}
}

class SwtichSorter implements Sorter {
	@Override
	public void sort(Student[] s, Comparator c) {
		for (int i = 0; i < s.length-1; i++) {
			int k = i;
			for (int j = i+1; j < s.length; j++) {
				if (c.compare(s[k], s[j]) == 0)
					k = j;
			}
			if (k != i) {
				Student temp = s[k];
				s[k] = s[i];
				s[i] = temp;
			}
		}
	}
}

public class StudentSorter {
	public static void main(String[] args) {
		// 定义数据
		Student[] ss = new Student[10];
		for (int i = 0; i < ss.length; i++) {
			ss[i] = new Student(i + 1, (int) (Math.random() * 100), (int) (Math.random() * 100),
					(int) (Math.random() * 100));
		}

		// 开始定义排序器： 冒泡，快排，交换排序
		Sorter[] sorters = new Sorter[3];
		sorters[0] = new BubbleSorter();
		sorters[1] = new QuickSorter();
		sorters[2] = new SwtichSorter();

		// 开始定义比较器: 语文 数学 英语
		Comparator[] comps = new Comparator[3];
		comps[0] = new ChineseComparator();
		comps[1] = new MathComparator();
		comps[2] = new EnglishComparator();

		// 开始排序
		for (int i = 0; i < sorters.length; i++) {
			// System.out.println("================== "+i+" ====================");
			for (Comparator c : comps) {
				sorters[i].sort(ss, c);
				for (Student s : ss)
					s.show();
				System.out.println("--------------------------------------------\n");
			}
		}
	}
}
