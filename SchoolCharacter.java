/*
学校需要构建综合系统，使用者包含多种角色。角色Role分两类：学生Student和雇员Employee；
雇员又分为教员Faculty和职员Staff。 每个角色都有姓名、性别。学生有学号、班级。一个雇员有工号、入职日期。教员有职称。职员有职位称号
*/
public class SchoolCharacter {
    public static void main(String[] args) {
        Faculty fac = new Faculty("张三",32,"33006","2019","10","25","讲师");
        Student stu=new Student("李四",19,"20201103","202011");
        Staff sta = new Staff("王五",27,"32011","2015","6","17","教务员");        
        fac.show();
        sta.show();
        stu.show();
    }
}

class People{
    String name;
    int age;
}

class Student extends People{
    String stunum;
    String clnum;
    void show(){
      System.out.println("我是"+this.name+"，年龄"+this.age+"岁。学号是"+this.stunum+"，来自"+this.clnum+"班。");  
    }
    Student(String name, int age, String stunum, String clnum){
        this.name = name;
        this.age = age;
        this.stunum = stunum;
        this.clnum = clnum;
    }
}

class Employee extends People{
    String empnum;
    String inyear;
    String inmonth;
    String inday;
}

class Faculty extends Employee{
    String jobtitle;
    Faculty(String name, int age, String empnum, String inyear, String inmonth, String inday, String jobtitle){
        this.name = name;
        this.age = age;
        this.empnum = empnum;
        this.inyear = inyear;
        this.inmonth = inmonth;
        this.inday = inday;
        this.jobtitle = jobtitle;
    }
    void show(){
        System.out.println("我是"+this.name+"，年龄"+this.age+"岁。工号是"+this.empnum+"，"+this.inyear+"年"+this.inmonth+"月"+this.inday+"日入职。是一名教师，"+this.jobtitle+"职称。");
    }

}

class Staff extends Employee{
    String position;
    Staff(String name, int age, String empnum, String inyear, String inmonth, String inday, String position){
        this.name = name;
        this.age = age;
        this.empnum = empnum;
        this.inyear = inyear;
        this.inmonth = inmonth;
        this.inday = inday;
        this.position = position;
    }
    void show(){
        System.out.println("我是"+this.name+"，年龄"+this.age+"岁。工号是"+this.empnum+"，"+this.inyear+"年"+this.inmonth+"月"+this.inday+"日入职。是一名"+this.position+"。");
    }
}
