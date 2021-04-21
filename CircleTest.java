/*
a定义圆类Circle，其中包括：
    成员变量定义 private int radius
    方法定义 包括下列要求
        定义无参构造方法 ，给radius赋值为2，并添加语句System.out.println("this is a constructor");
        定义有参构造方法 ，接收用户给给radius赋值，如果用户输入半径为<=0,则让半径的值为2，并添加语句System.out.println("this is a constructor with para");
        为radius半径添加setter方法，接收用户输入的半径，如果用户输入半径为<=0,则让半径的值为2
        为radius半径添加getter方法，返回用户输入的半径
        定义求面积方法public int gerArea(),π使用Math.PI代替，面积的结果强制转换为int返回
        定义toString方法，public String toString( )方法体为：
            return "Circle [radius=" + radius + "]";
b定义Main类，在main方法中，完成下列操作
    定义并创建Circle的第一个对象c1，并使用println方法输出c1
        求c1的面积并输出
定义并创建Circle的第一个对象c2，并使用println方法输出c2
        从键盘接收整数半径，并赋值给c2的半径，使用println方法输出c2
        求c2的面积并输出
从键盘接收整数半径，并创建Circle的第三个对象c3，并将用户输入整数半径通过有参构造方法传递给出c3，使用println方法输出c3
        求c3的面积并输出
*/
import java.util.Scanner;
public class CircleTest {
    public static void main(String[] agrs){
        Scanner sc = new Scanner(System.in);
        Circle c1 = new Circle();
        System.out.println(c1.toString());
        System.out.println("c1:area=" + c1.getArea());
        Circle c2 = new Circle();

    }
    
  

}
class Circle{
    private int radius;
    Circle(){
        this.radius = 2;
        System.out.println("this is a constructor");
    }

    Circle(int radius){
        if(radius <= 0){
            this.radius = 2;
            System.out.println("this is a constructor with para");
        }
        else
            this.radius = radius;
    }

    void setter(int radius){
        if(radius <= 0){
            this.radius = 2;
        }
        else
            this.radius = radius;
    }

    int getter(){
        return this.radius;
    }

    public void getArea(){
        System.out.println(":" + (int)(Math.PI * radius * radius));//?
    }

    public String toString(){
        return "Circle [radius=" + radius + "]";//?
    }
}
