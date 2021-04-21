/*（1）成员变量：商品编号（String） 、商品名称(String)、商品单价(double)
（2）成员变量封装，定义为私有属性，并为每个成员变量定义getXXXX，setXXXX方法
（3）定义构造方法，要求带三个参数，参数值用于给成员变量赋值。
（4）重写toString（）方法，将对象转换为字符串，格式：商品编号，商品名称，商品单价
*/
import java.util.Scanner;
public class test{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String number = new String();
        String name = new String();
        number = sc.next();
        name = sc.next();
        double price = sc.nextDouble();
        
        Item mt = new Item(number, name, price);
        System.out.println(mt.getNumber() + "," + mt.getName() + "," + mt.getPrice());
        }
    }

class Item{
    private String number;
    private String name;
    private double price;
    Item(String number, String name, double price){
        setName(name);
        setNumber(number);
        setPrice(price);
    }
    String getNumber(){
        return number;
    }

    String getName(){
        return name;
    }

    double getPrice(){
        return price;
    }

    void setNumber(String number){
        this.number = number;
    }

    void setName(String name){
        this.name = name;
    }

    void setPrice(double price){
        this.price = price;
    }
}