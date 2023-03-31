# Խառը գրառումներ BCEL գրադարանի մասին

[Apache Commons BCEL™](https://commons.apache.org/proper/commons-bcel/)-ը (Byte Code Engineering Library) _Ջավայի վիրտուալ մեքենայի_ (JVM) համար ստեղծված _բայթ-կոդի_ հետ աշխատող գրադարան է։ Այն հնարավորություն է տալիս կարդալ բայթ-կոդի `*.class` ֆայլը, թվարկել, վերլուծել դրա պարունակությունը և, անհրաժեշտության դեպքում, փոփոխություններ կատարել։ BCEL-ի հնարավորություն է տալիս նաև հենց սկզբից ստեղծել ամբողջական class ֆայլ։

Ստորև բերված օրինակներում վերլուծության ու ձևափոխության առարկա է լինելու `Point` դասը.

```Java
public class Point {
  private double _x = 0.0;
  private double _y = 0.0;

  public Point(double x, double y) {
    _x = x;
    _y = y;
  }

  public double x() {
    return _x;
  }

  public double y() {
    return _y;
  }

  public double distance(Point other) {
    var dx = _x - other._x;
    var dy = _y - other._y;
    return Math.sqrt(dx * dx + dy * dy);
  }
}
```

## Դասի անդամների թվարկում

Շատ հեշտ է գրել մեթոդ, որն արտածում է տրված դասի բոլոր անդամների ու մեթոդների անուններն իրենց տիպերի հետ։ Դրա համար պետք է BCEL-ի `ClassParser`-ով ստեղծել `JavaClass` օբյեկտ, ապա դրանից վերցնել անդամների ու մեթոդների նկարագրությունները՝ համապատասխանաբար `getFields()` և `getMethods()` մեթոդներով։ Մոտավորապես այսպես.

```Java
public class Explorer {
    public static void explore(String file) throws IOException {
        var cls = new ClassParser(file).parse();

        Arrays.stream(cls.getFields()).forEach(System.out::println);
        System.out.println();
        Arrays.stream(cls.getMethods()).forEach(System.out::println);
    }
}
```


## Մեթոդում հաղորդագրության արտածման ավելացում


## Դասում ստատիկ անդամի ու մեթոդի ավելացում
