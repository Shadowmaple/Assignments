// package cn.edu.ccnu.cs;

// 编写程序，根据学号，以不同的方式来查找学生，以下是程序的基本框架（尽量遵守该框架）
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

class PStudent {
    public String sno; // 学号
    public int chinese; // 语文成绩
    public int math;    // 数学成绩
    public int english; // 英语成绩

    public PStudent(String sno, int chinese, int math, int english) {
        this.sno = sno;
        this.chinese = chinese;
        this.math = math;
        this.english = english;
    }

    public void show() {
        System.out.println("SNO:" + sno + "  C:" + chinese + "   M:" + math + "  E:" + english);
    }
}

public class StudentSearch {

    public static void main(String[] args) {
        // 定义数据
        int count = 1000000;
        Map<String, PStudent> ssMap = new HashMap<String, PStudent>();
        Map<String, PStudent> tsMap = new TreeMap<String, PStudent>();
        List<PStudent> ssList = new ArrayList<PStudent>();

        for (int i = 0; i < count; i++) {
            String sno = "S" + (i + 1);
            PStudent s = new PStudent(sno, (int) (Math.random() * 100), (int) (Math.random() * 100),
                    (int) (Math.random() * 100));
            ssMap.put(sno, s);
            tsMap.put(sno, s);
            ssList.add(s);
        }

        // 填空1，按学号排序，默认升序
        Collections.sort(ssList, (s1, s2)->(s1.sno.compareTo(s2.sno)));

        // 测试
        long now = 0;
        now = System.currentTimeMillis();
        for (int i = 0; i < (count >> 1); i++) {
            String sno = "S" + ((int)(Math.random() * count) + 1);
            PStudent s = new PStudent(sno, 0, 0, 0);
            // 填空2，按sno的值，采用 Collections.binarySearch 查找
            int index = Collections.binarySearch(ssList, s, (s1, s2)->(s1.sno.compareTo(s2.sno)));
            s = ssList.get(index);
        }
        System.out.println("Binary Search Time:" + (System.currentTimeMillis() - now));

        now = System.currentTimeMillis();
        for (int i = 0; i < (count >> 1); i++) {
            String sno = "S" + ((int)(Math.random() * count) + 1);
            PStudent s = new PStudent(sno, 0, 0, 0);
            // 填空3，按sno的值，从 ssMap 中查找
            s = ssMap.get(sno);
        }
        System.out.println("HashMap Time:" + (System.currentTimeMillis() - now));

        now = System.currentTimeMillis();
        for (int i = 0; i < (count >> 1); i++) {
            String sno = "S" + ((int)(Math.random() * count) + 1);
            PStudent s = new PStudent(sno, 0, 0, 0);
            // 填空4，按sno的值，从 tsMap 中查找
            s = tsMap.get(sno);
        }
        System.out.println("Tree Map Time:" + (System.currentTimeMillis() - now));
    }
}
