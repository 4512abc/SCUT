package test;

// 抽象类Speakable，定义抽象方法speak
abstract class Speakable {
  public abstract void speak();
}

// 抽象类Runner，定义抽象方法run
abstract class Runner {
  public abstract void run();
}

// Dog类继承Speakable和Runner抽象类，实现抽象方法
class Dog extends Runner implements Speakable {
  public void speak() {
    System.out.println("狗的声音:汪、汪！");
  }

  public void run() {
    System.out.println("狗用四肢跑步");
  }
}

// Person类继承Runner抽象类并实现Speakable接口，实现抽象方法
class Person extends Runner implements Speakable {
  public void speak() {
    System.out.println("人们见面时经常说:您好！");
  }

  public void run() {
    System.out.println("人用两腿跑步");
  }
}

// 新增 Bird 类继承 Speakable 抽象类
class Bird extends Speakable {
  public void speak() {
    System.out.println("鸟的声音:叽叽喳喳！");
  }
}

public class TestAbstract {
  public static void main(String[] args) {
    Dog d = new Dog();
    d.speak();
    d.run();

    Person p = new Person();
    p.speak();
    p.run();

    // 创建 Bird 类的实例并输出其特征
    Bird b = new Bird();
    b.speak();
  }
}