public class Student {
    int age;
    static void f(int n, Student s) {
        n = 5;
        s.age = 10;
    }

    public static void main(String[] args) {
        int n = 1;
        Student s = new Student();
        s.age = 2;

        f(n, s);

        System.out.println("n=" + n + "s.age=" + s.age);
    }
}