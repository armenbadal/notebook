# Swift լեզվի ներածություն

_Թարգմանված է [A Swift Tour](https://docs.swift.org/swift-book/GuidedTour/GuidedTour.html)-ից_

Ավանդությունն ասում է, որ նոր լեզվով գրված առաջին ծրագիրը պետք է էկրանին արտածի «Hello, world!» բառերը։ Swift-ում դա կարելի է անել մի տողով.

```Swift
print("Hello, world!")
// Prints "Hello, world!"
```

Եթե դուք արդեն կոդ եք գրել C-ով կամ Objective-C-ով, ապա այս շարահյուսությունը ծանոթ է ձեզ. Swift լեզվում կոդի այս միակ տողը ամբողջական ծրագիր է։ Դուք կարիք չունեք առանձին գրադարան ներմուծել այնֆիսի ֆունկցիոնալության համար, ինչպիսիք են ներմուծում/արտածումը կամ տողերի մշակումը։ Գլոբալ տիրույթում գրված կոդը ծառայում է որպես ծրագրի մուտքի կետ, այսինքն՝ `main()` ֆունկցիայի կարիքն էլ չունեք։ Կարիք չունեք նաև ամեն մի հրամանի վերջում կետ-ստորակետ դնելու։

Այս ներածականը ձեզ բավարար տեղեկություններ կտա սկսել կոդ գրել Swift լեզվով՝ ցույց տալով, թե ինչպես են լուծվում ծրագրավորման զանազան խնդիրները։ Մի անհանգստացեք, եթե ինչ-որ բան չեք հասկանում. այս ներածականում ներկայացված ամեն ինչ մանրամասն բացատրված է գրքի շարունակության մեջ։


## Պարզ արժեքներ

`let`-ը օգտագործեք հաստատուն ստեղծելու համար, իսկ `var`-ը՝ փոփոխականի համար։ Անհրաժեշտ չէ, որ հաստատունի արժեքը հայտնի լինի կոմպիլյացիայի ժամանակ, բայց դուք պետք է դրան արժեք վերագրեք միայն մեկ անգամ։ Սա նշանակում է, որ հաստատունը կարող եք օգտագործել ինչ-որ արժեքի անուն տալու համար, որը սահամանում եք մի անգամ, բայց օգտագործում եք շատ տեղերում։

```Swift
var myVariable = 42
myVariable = 50
let myConstant = 42
```

Հաստատունը կամ փոփոխականը պետք է ունենան այն նույն տիպը, ինչ տիպ որ ունի դրանց վերագրվող արժեքը։ Այնուամենայնիվ, ամեն անգամ տիպը բացահայտ նշելու կարիք չկա։ Հաստատուն կամ փոփոխական ստեղծելու ժամանակ տրված արժեքը կոմպիլյատորին թույլ է տալիս դուրս բերել դրա տիպը։ Բերված օրինակում կոմպիլյատորը որոշում է, որ `myVariable`-ը ամբողջ թիվ է, քանի որ որպես արժեք տրված է ամբողջ թիվ։

Եթե սկզբնական արժեքը բավարար տեղեկություն չի տրամադրում (կամ այն սկզբնական արժեք չէ), տիպը գրեք փոփոխականի անունից հետո՝ անջատված երկու կետով։

```Swift
let implicitInteger = 70
let implicitDouble = 70.0
let explicitDouble: Double = 70
```

> __Վարժություն։__ Սահմանեք հաստատուն՝ տիպը բացահայտ նշելով `Float` և տալով `4` արժեքը։

Արժեքները երբեք անբացահայտ այլ տիպի չեն փոխարկվում։ Եթե ձեզ պետք է արժեքն այլ տիպով ներկայացնել, ապա բացահայտորեն ստեղծեք պահանջվող տիպի նմուշը։

```Swift
let label = "The width is "
let width = 94
let widthLabel = label + String(width)
```

> __Վարժություն։__ Փորձեք վերջին տողում հեռացնել `String`-ի փոխարկումը։ Ի՞նչ սխալ եք ստանում։

Արժեքները տողի մեջ ներառելու ավելի պարզ եղանակ կա. արժեքը վերցրեք փակագծերի մեջ և բացվող փակագծից առաջ գրեք `\`։ Օրինակ.

```Swift
let apples = 3
let oranges = 5
let appleSummary = "I have \(apples) apples."
let fruitSummary = "I have \(apples + oranges) pieces of fruit."
```

> __Վարժություն։__ `\()` փակագծերն օգտագործեք տողի մեջ սահող կետով հաշվարկներ ավելացնելու համար, և ողջույնի տողում ինչ-որ մեկի անունն ավելացնելու համար։

Երեք հատ կրկնակի չակերտի նիշերն (`"""`) օգտագործեք մի քանի տող զբաղեցնող տեքստերը նշելու համար։ Եթե հերթական տողի խորությունը համընկնում է տեքստն ավարտող չակերտների խորության հետ, ապա այն անտեսվում է։ Օրինակ.

```Swift
let quotation = """
I said "I have \(apples) apples."
And then I said "I have \(apples + oranges) pieces of fruit."
"""
```

Զանգվածներ (array) և բառարաններ (dictionary) ստեղծեք քառակուսի փակագծերով (`[]`), և դրանց տարրերին դիմեք քառակուսի փակագծերում ինդեքսը կամ բանալին գրելով։ Վերջին տարրից հետո գրված ստորակետը թույլատրելի է։

```Swift
var shoppingList = ["catfish", "water", "tulips"]
shoppingList[1] = "bottle of water"

var occupations = [
    "Malcolm": "Captain",
    "Kaylee": "Mechanic",
]
occupations["Jayne"] = "Public Relations"
```

Զանգվածները ինքնուրույն ընդարձակվում են տարրեր ավելացնելու հետ միասին։

```Swift
shoppingList.append("blue paint")
print(shoppingList)
```

Դատարկ զանգված կամ բառարան ստեղծելու համար օգտագործեք սկզբնարժեքավորման գրելաձևը։

```Swift
let emptyArray = [String]()
let emptyDictionary = [String: Float]()
```

Եթե տիպի մասին տեղեկությունները հնարավոր է դուրս բերել, ապա դատարկ զանգվածը կարող եք նշանակել որպես `[]`, իսկ դատարկ բառարանը՝ `[:]`. օրինակ, երբ նոր արժեք եք վերագրում փոփոխականին, կամ ֆունկցիայի արգումենտ եք փոխանցում։

```Swift
shoppingList = []
occupations = [:]
```


## Ծրագրի ընթացքի ղեկավարում

Պայմաններ գրելու համար օգտագործեք `if` և `switch`, իսկ կրկնությունների համար՝ `for-in`, `while` և `repeat-while`: Պայմանի կամ ցիկլի փոփոխականի շուրջ դրված փակագծերը պարտադիր չեն։ Մարմինն ընդգրկող ձևավոր փակագծերը պարտադիր են։

```Swift
let individualScores = [75, 43, 103, 87, 12]
var teamScore = 0
for score in individualScores {
    if score > 50 {
        teamScore += 3
    } else {
        teamScore += 1
    }
}
print(teamScore)
// Prints "11"
```

`if` հրամանում պայմանը պետք է լինի տրամաբանական (Boolean) արտահայտություն. սա նշանակում է, որ `if score { ... }` տեսքի կոդը սխալ է. բացակայում է զրոյի հետ բացահայտ համեմատումը։

Կարող եք `if`-ը և `let`-ը համատեղ օգտագործել այն դեպքերում, երբ հետաքրքրող արժեքը կարող է բացակայել։ Այդպիսի արժեքները կոչվում են `optional`-ներ։ Optional արժեքը կա պարունակում է իրական արժեքը կամ էլ `nil`՝ ի նշան արժեքի բացակայության։ Արժեքի optional լինելը նշելու համար նրա տիպից հետո գրեք `?` նշանը։ 

```Swift
var optionalString: String? = "Hello"
print(optionalString == nil)
// Prints "false"

var optionalName: String? = "John Appleseed"
var greeting = "Hello!"
if let name = optionalName {
    greeting = "Hello, \(name)"
}
```

> __Վարժություն։__ `optionalName`-ը փոխարինեք `nil`-ով։ Ի՞նչ ողջույնի տեքստ եք ստանում։ Ավելացրեք `else` ճյուղը, որը `optionalName`-ի `nil` լինելու դեպքում ավահովում է այլ ողջույնի տեքստ։

Եթե optional արժեքը `nil` է, ապա պայմանը կեղծ է և ձևավոր փակագծերի կոդը չի կատարվում։ Հակառակ դեպքում optional-ի արժեքը բացվում է (unwrapped) և վերագրվում է `let`-ով սահմանվող հաստատունին, որն էլ բացված արժեքը հասանելի է դարձնում կոդի բլոկում։

Optional արժեքների հետ աշխատելու մի այլ հնարավորություն է `??` օպերատորով լռելության արժեք վերագրելը։ Եթե արժեքը բացակայում է, ապա դրա փոխարեն օգտագործվում է լռելությամբ տրվածը։

```Swift
let nickname: String? = nil
let fullName: String = "John Appleseed"
let informalGreeting = "Hi \(nickname ?? fullName)"
```

Ընտրության կառուցվածքները (switch) աշխատում է ցանկացած տիպի տվյալների և տարատեսակ համեմատման գործողությունների հետ. դրանք սահմանափակված չեն միայն ամբողջ թվերով և հավասարության ստուգման գործողությամբ։

```Swift
let vegetable = "red pepper"
switch vegetable {
case "celery":
    print("Add some raisins and make ants on a log.")
case "cucumber", "watercress":
    print("That would make a good tea sandwich.")
case let x where x.hasSuffix("pepper"):
    print("Is it a spicy \(x)?")
default:
    print("Everything tastes good in soup.")
}
// Prints "Is it a spicy red pepper?"
```

> __Վարժություն։__ Փորձեք հեռացնել `default` ճյուղը։ Ի՞նչ սխալ եք ստանում։

Ուշադրություն դարձրեք, թե ինչպես կարելի է `let`-ը օգտագործել ձևանմուշի մեջ՝ այդ ձևանմուշին համընկնող արժեքը հաստատունին վերագրելու համար։

Մի որևէ `case`-ի մարմնի կատարումով `switch` կառուցվածքի կատարումն ավարտվում է։ Կատարումը չի անցնում հաջորդ `case` բլոկին, այսինքն՝ դուք կարիք չունեք ամեն մի `case`-ի վերջում բացահայտորեն ընդհատելու `switch`-ի կատարումը։

`for-in` կառուցվածքն օգտագործում եք բառարանի տարրերով «վազելու» համար՝ բանալի-արժեք զույգերի համար տրամադրելով փոփոխականների զույգ։ Բառարանները չկարգավորված բազմություններ են, հետևաբար դրանց բանալիներն ու արժեքները թվարկվում են կամայական կարգով։

```Swift
let interestingNumbers = [
    "Prime": [2, 3, 5, 7, 11, 13],
    "Fibonacci": [1, 1, 2, 3, 5, 8],
    "Square": [1, 4, 9, 16, 25],
]
var largest = 0
for (_, numbers) in interestingNumbers {
    for number in numbers {
        if number > largest {
            largest = number
        }
    }
}
print(largest)
// Prints "25"
```

> __Վարժություն։__ Փոխարինեք `_`-ը փոփոխականի անունով և պարզեք, թե ինչ տեսակի է ամենամեծ թիվը։

`while`-ը օգտագործեք կոդի բլոկը կրկնելու համար՝ քանի դեռ պայմանը տեղի ունի։ Ցիկլի պայմանը կարող է գրվել նաև վերջում՝ ապահովելով մարմնի գոնե մեկ անգամ կատարվելը։

```Swift
var n = 2
while n < 100 {
    n *= 2
}
print(n)
// Prints "128"

var m = 2
repeat {
    m *= 2
} while m < 100
print(m)
// Prints "128"
```

Ցիկլում կարող եք ինդեքս ունենալ՝ `..<` օպերատորով ստեղծելով ինդեքսների միջակայք։

```Swift
var total = 0
for i in 0..<4 {
    total += i
}
print(total)
// Prints "6"
```

`..<` օպերատորը օգտագործեք կիսափակ (վերին եզրը չընդգրկող) միջակայք ստեղծելու համար, իսկ `...` օպերատորը՝ փակ միջակայքի համար։


## Ֆունկցիաներ և Closure-ներ

Ֆունկցիա սահմանելու համար օգտագործեք `func` բառը։ Ֆունկցիան կանչեք նրա անունից հետո կլոր փակագծերում տալով արգումենտների ցուցակը։ `->` նշանակմամբ առանձնացրեք ֆունկցիայի պարամետրերի անուններն ու տիպերը դրա վերադարձվող արժեքի տիպից։

```Swift
func greet(person: String, day: String) -> String {
    return "Hello \(person), today is \(day)."
}
greet(person: "Bob", day: "Tuesday")
```


> __Վարժություն։__ Հեռացրեք `day` պարամետրը։ Add a parameter to include today’s lunch special in the greeting. ??

Լռելությամբ ֆունկցիաներն իրենց պարամետրերի անուններն օգտագործում են որպես արգումենտների պիտակներ։ Պարամետրի անունից առաջ կարող եք գրել ձեր պիտակը, կամ գրեք `_`՝ պիտակի օգտագործումից հրաժարվելու համար։

```Swift
func greet(_ person: String, on day: String) -> String {
    return "Hello \(person), today is \(day)."
}
greet("John", on: "Wednesday")
```

Բաղադրյալ արժեք ստեղծելու համար օգտագործեք tuple (n-յակ). օրինակ, ֆունկցիայից մի քանի արժեք վերադարձնելու համար։ N-յակի տարրերին կարելի է դիմել կամ անունով, կամ համարով։

```Swift
func calculateStatistics(scores: [Int]) -> (min: Int, max: Int, sum: Int) {
    var min = scores[0]
    var max = scores[0]
    var sum = 0

    for score in scores {
        if score > max {
            max = score
        } else if score < min {
            min = score
        }
        sum += score
    }

    return (min, max, sum)
}
let statistics = calculateStatistics(scores: [5, 3, 100, 3, 9])
print(statistics.sum)
// Prints "120"
print(statistics.2)
// Prints "120"
```

Ֆունկցիաները կարող են ներդրված լինել։ Ներդրված ֆունցկիաներին հասանելի են այն արտաքին ֆունկցիայի փոփոխականները, որում ինքը հայտարարված է։ Ներդրված ֆունկցիաները կարող եք օգտագործել երկար կամ բարդ ֆունկցիաների կոդը վերակազմակերպելու համար։

```Swift
func returnFifteen() -> Int {
    var y = 10
    func add() {
        y += 5
    }
    add()
    return y
}
returnFifteen()
```

Ֆունկցիաները առաջին դասի տիպեր են։ Սա նշանակում է, որ ֆունկցիան կարող է որպես արժեք վերադարձնել մի այլ ֆունկցիա։

```Swift
func makeIncrementer() -> ((Int) -> Int) {
    func addOne(number: Int) -> Int {
        return 1 + number
    }
    return addOne
}
var increment = makeIncrementer()
increment(7)
```

Ֆունկցիան կարող է իր արգումենտներում ստանալ մի որևէ այլ ֆունկցիա։

```Swift
func hasAnyMatches(list: [Int], condition: (Int) -> Bool) -> Bool {
    for item in list {
        if condition(item) {
            return true
        }
    }
    return false
}
func lessThanTen(number: Int) -> Bool {
    return number < 10
}
var numbers = [20, 19, 7, 12]
hasAnyMatches(list: numbers, condition: lessThanTen)
```

Ֆունկցան իրականում closure-ի տեսակ է. այն կոդի բլոկ է, որը կարելի է կանչել ավելի ուշ։ Closure-ի կոդին հասանելի են այն բաները, ինչպիսիք են փոփոխականներն ու ֆունկցիաները, որոնք հասանելի էին այն տիրույթում (scope), որտեղ closure-ն ստեղծվել է, նույնիսկ եթե closure-ը կատարվում է այլ տիրույթում. սրա օրինակն արդեն դուք տեսաք ներդրված ֆունկցիաների դեպքում։ Կարող եք առանց անունի closure սահմանել՝ դրա կոդն ընդգրկելով ձևավոր փակագծերում (`{}`)։ `in` բառով անջատեք արգումենտներն ու վերադարձվող արժեքի տիպը մարմնից։

```Swift
numbers.map({ (number: Int) -> Int in
    let result = 3 * number
    return result
})
```

> __Վարժություն։__ Ձևափոխեք closure-ն այնպես, որ այն զրո վերադարձնի բոլոր կենտ թվերի համար։

Դուք closure-ները ավելի համառոտ սահմանելու մի քանի հնարավորություն ունեք։ Եթե closure-ի տիպն արդեն հայտնի է, such as the callback for a delegate, ապա դուք կարող եք բաց թողնել պարամետրերի տիպըեր, վերադարձվող արժեքի տիպը կամ երկուսն էլ միասին։ Միակ հրաման պարունակող closure-ը անուղղակիորեն վերադարձնում է իր այդ միակ հրամանի արժեքը։

```Swift
let mappedNumbers = numbers.map({ number in 3 * number })
print(mappedNumbers)
// Prints "[60, 57, 21, 36]"
```

Անունների փոխարեն պարամետրերը կարելի է օգտագործել նաև դրանց համարները. այս մոտեցումը հատկապես օգտակար է կարճ closure-ներն օգտագործելիս։ Որպես ֆունկցիայի վերջին արգումենտ փոխանցվող closure-ը կարող է գրառվել անմիջապես արգումենտների փակագծերից հետո։ Եթե closure-ը ֆունկցիայի միակ արգումենտն է, ապա կարող եք ամբողջությամբ բաց թողնել նաև փակագծերը։

```Swift
let sortedNumbers = numbers.sorted { $0 > $1 }
print(sortedNumbers)
// Prints "[20, 19, 12, 7]"
```


## Օբյեկտներ և դասեր

Նոր դաս սահմանելու համար օգտագործեք `class` բառը, որին հաջորդում է դասի անունը։ Դասի հատկությունները սահմանվում են նույն կերպ, ինչպես հաստատունները կամ փոփոխականները, տարբերությամբ որ կոնտեքստը դասինն է։ Իրար նման են նաև մեթոդների ու ֆունկցիաների սահմանումները։

```Swift
class Shape {
    var numberOfSides = 0
    func simpleDescription() -> String {
        return "A shape with \(numberOfSides) sides."
    }
}
```

> __Վարժություն։__ `let`-ի օգնությամբ ավելացրեք հաստատուն հատկությունը, ավելացրեք նաև մեթոդ, որը արգումենք է սպասում։

Դասի նմուշ (instance) ստեղծեք դասի անունից հետո գրելով կլոր փակագծեր։ Նմուշի հատկություններին ու մեթոդներին դիմելու համար օգտագործեք կետը (`.`)։

```Swift
var shape = Shape()
shape.numberOfSides = 7
var shapeDescription = shape.simpleDescription()
```

`Shape` դասի այս տարբերակում մի կարևոր բան բացակայում է. սկզբնարժեքավորումը, երբ նմուշն է ստեղծվում։ Դրա համար օգտագործեք `init`-ը։

```Swift
class NamedShape {
    var numberOfSides: Int = 0
    var name: String

    init(name: String) {
        self.name = name
    }

    func simpleDescription() -> String {
        return "A shape with \(numberOfSides) sides."
    }
}
```

Ուշադրություն դարձրեք, թե ինչպես է `self`-ը օգտագործվում `name` արգումենտով `name` հատկությունն արժեքավորելու համար։ Դասի նմուշը ստեղծելիս սկզբնարժեքավորիչին արգումենտները փոխանցվում են ճիշտ նույն կերպ, ինչպես փոխանցվում են ֆունկցիայի կանչի ժամանակ։ Յուրաքանչյուր հատկություն պետք է արժեք ստանա կամ հայտարարության մեջ (ինչպես `numberOfSides`-ը), կամ սկզբնարժեքավորիչում (ինչպես `name`-ը)։

Օբյեկտի ոչնչացումից առաջ ինչ-որ մաքրություն անելու համար օգտագործեք `deinit`-ը։ 

Ենթադաս սահմանելիս գերդասի անունը գրվում է սահմանվող դասի անունից հետո՝ բաժանված `:`-ով։ Պարտադիր չէ, որ սահմանվող դասը ժառանգի ինչ-որ ստանդարտ բազային դաս, այսինքն՝ կարող եք բազային դասի անունը գրել կամ չգրել։

Ենթադասի այն մեթոդները, որոնք վերասահմանում (override) են բազային դասի մեթոդի իրականացումը, նշվում են `override` բառով. առանց `override` բառի մեթոդի պատահական վերասահմանումը կոմպիլյատորի կողմից դիտարկվում է որպես սխալ։ Կոմպիլյատորը նաև հայտնաբերում է `override` բառով նշված այն մեթոդները, որոնք իրականում ոչ մի մեթոդ էլ չեն վերասահմանում։

```Swift
class Square: NamedShape {
    var sideLength: Double

    init(sideLength: Double, name: String) {
        self.sideLength = sideLength
        super.init(name: name)
        numberOfSides = 4
    }

    func area() -> Double {
        return sideLength * sideLength
    }

    override func simpleDescription() -> String {
        return "A square with sides of length \(sideLength)."
    }
}
let test = Square(sideLength: 5.2, name: "my test square")
test.area()
test.simpleDescription()
```

> __Վարժություն։__ `NamedShape` դասից ժառանգեք `Circle` անունով ևս մի դաս, որի արժեքավորիչի արգումենտներն են շառավիղն ու անունը։ `Circle` դասի համար իրականացրեք `area()` և `simpleDescription()` մեթոդները։

Ի լրումն հասարակ հատկությունների, կարող ենք սահմանել նաև `get` ու `set` մեթոդներով հատկություններ։

```Swift
class EquilateralTriangle: NamedShape {
    var sideLength: Double = 0.0

    init(sideLength: Double, name: String) {
        self.sideLength = sideLength
        super.init(name: name)
        numberOfSides = 3
    }

    var perimeter: Double {
        get {
            return 3.0 * sideLength
        }
        set {
            sideLength = newValue / 3.0
        }
    }

    override func simpleDescription() -> String {
        return "An equilateral triangle with sides of length \(sideLength)."
    }
}
var triangle = EquilateralTriangle(sideLength: 3.1, name: "a triangle")
print(triangle.perimeter)
// Prints "9.3"
triangle.perimeter = 9.9
print(triangle.sideLength)
// Prints "3.3000000000000003"
```

`perimeter`-ի set բլոկին փոխանցված նոր արժեքն ունի `newValue` ենթադրվող անունը։ Այլ անուն կարող եք տալ՝ `set` բառից հետո փակագծերում նշելով։

Ուշադրություն դարձրեք, որ `EquilateralTriangle`-ի արժեքավորիչը պարունակում է երեք տարբեր քայլեր.

1. Արժեքներ վերագրել ենթադասի հայտարարած հատկություններին։
2. Կանչել գերդասի արժեքավորիչը.
3. Գերդասում սահմանված հատկությունների արժեքների փոփոխում։ Ցանկացած այլ գործ, որ օգտագործում է մեթոդներ, `set`-եր կամ `get`-եր, նույնպես կարող է կատարվել ասյ կետում։

Եթե չեք ուզում հաշվարկել հատկության արժեքը, բայց այնումաենայնիվ ուզում եք գրել կոդ, որը կատարվում է նոր արժեք վերագրելուց առաջ և հետո, ապա օգտագործեք `willSet`-ը և `didSet`-ը։ Ձեր գրած կոդը աշխատում է ամեն անգամ, երբ հատկության արժեքը փոխվում է արժեքավորիչից դուրս։ Օրինակ, ստորև բերված դասը երաշխավորում է, որ իր եռանկյան կողի երկարությունը միշտ նույնն է, ինչ որ իր քառակուսու կողինը։

```Swift
class TriangleAndSquare {
    var triangle: EquilateralTriangle {
        willSet {
            square.sideLength = newValue.sideLength
        }
    }
    var square: Square {
        willSet {
            triangle.sideLength = newValue.sideLength
        }
    }
    init(size: Double, name: String) {
        square = Square(sideLength: size, name: name)
        triangle = EquilateralTriangle(sideLength: size, name: name)
    }
}
var triangleAndSquare = TriangleAndSquare(size: 10, name: "another test shape")
print(triangleAndSquare.square.sideLength)
// Prints "10.0"
print(triangleAndSquare.triangle.sideLength)
// Prints "10.0"
triangleAndSquare.square = Square(sideLength: 50, name: "larger square")
print(triangleAndSquare.triangle.sideLength)
// Prints "50.0"
```

Optoinal արժեքների հետ աշխատելիս գործողություններից առաջ, ինչպիսք են մեթոդները, հատկություններ և ինդեքսավորումը, կարող եք գրել `?` նիշը։ Եթե `?` նշանից առաջ գրած արժեքը `nil` է, ապա `?`-ին հաջորդող ամեն ինջ անտեսվում է և ամբողջ արտահայտության արժեքը համարվում է `nil`։ Հակառակ դեպքում optional արժեքը բացվում է և `?`-ին հետևող ամեն ինչ ծառայում է որպես բացված արժեք. Երկու դեպքում էլ ամբողջ արտահայտության արժեքը optional արժեք է։

```Swift
let optionalSquare: Square? = Square(sideLength: 2.5, name: "optional square")
let sideLength = optionalSquare?.sideLength
```


## Թվարկումներ և ստրուկտուրաներ

Թվարկում ստեղծելու համար օգտագործեք `enum`-ը։ Ինչպես և այլ անվանված տիպերը, թվարկումներն էլ կարող են իրենց հետ համապատասխանեցված մեթոդներ ունենալ։

```Swift
enum Rank: Int {
    case ace = 1
    case two, three, four, five, six, seven, eight, nine, ten
    case jack, queen, king

    func simpleDescription() -> String {
        switch self {
        case .ace:
            return "ace"
        case .jack:
            return "jack"
        case .queen:
            return "queen"
        case .king:
            return "king"
        default:
            return String(self.rawValue)
        }
    }
}
let ace = Rank.ace
let aceRawValue = ace.rawValue
```

> __Վարժություն։__ Գրեք ֆունկցիա, որը երկու `Rank` արժեքներ համեմատում է՝ դրանց raw ? արժեքները համեմատելով։

Լռելությամբ Swift-ը raw ? արժեքները սկում է զրոյից և ամեն անգամ ավելացնում է մեկով, սակայն այս վարքը կարող եք փոխել՝ բացահայտ արժեքներ նշելով։ Վերը բերված օրինակում `ace`-ին բացահայտ տրված է `1` արժեքը, իսկ մյուս անդամներին տրված են հաջորդական արժեքներ։ Որպես թվարկման raw ? տիպ կարող եք օգտագործել նաև տողը (string) կամ սահող կետով թվերը։ Թվարկման անդամի հետ կապված արժեքը ստանալու համար օգտագործեք `rawValue` հատկությունը։ 

Պարզ արժեքից թվարկման նմուշ ստանալու համար օգտագործեք `init?(rawValue:)` արժեքավորիչը։ Այն կամ վերադարձնում  տրված արժեքին համապատասխանող թվարկման անդամը, կամ էլ `nil`, եթե համապատասխանող չկա։

```Swift
if let convertedRank = Rank(rawValue: 3) {
    let threeDescription = convertedRank.simpleDescription()
}
```

Թվարկման անդամերն իրական արժեքներ են, այլ ոչ թե պարզ արժեքների մի այլ գրառման եղանակ։ In fact, in cases where there isn’t a meaningful raw value, you don’t have to provide one.

```Swift
enum Suit {
    case spades, hearts, diamonds, clubs

    func simpleDescription() -> String {
        switch self {
        case .spades:
            return "spades"
        case .hearts:
            return "hearts"
        case .diamonds:
            return "diamonds"
        case .clubs:
            return "clubs"
        }
    }
}
let hearts = Suit.hearts
let heartsDescription = hearts.simpleDescription()
```

> __Վարժություն։__ `Suit`-ին ավելացրեք `color()` մեթոդը, որը `spaces`-ի և `clubs`-ի համար վերադարձնում է `black`, իսկ `hearts`-ի և `diamonds`-ի համար՝ `red`:

Ուշադրություն դարձրեք վերը բերված ծրագրում `hearts` անվան երկու տարբեր գրառումներին. երբ արժեք է վերագրվում `hearts` հաստատունին, թվարկման անդամը հիշատակվում է իր լրիվ անունով՝ `Suit.hearts`, քանի որ հաստատունի տիպը բացահայտ նշված չէ։ `switch` կառուցվածքում թվարկման անդամը հիշատակվում է `.hearts` համառոտ գրառմամբ, որովհետև `self`-ի տիպը հայտնի է։ Համառոտ գրառումը կարող եք օգտագործել բոլոր այն տեղերում, որտեղ դիտարկվող արժեքի տիպն արդեն հայտնի է։

If an enumeration has raw values, those values are determined as part of the declaration, which means every instance of a particular enumeration case always has the same raw value. Another choice for enumeration cases is to have values associated with the case—these values are determined when you make the instance, and they can be different for each instance of an enumeration case. You can think of the associated values as behaving like stored properties of the enumeration case instance. For example, consider the case of requesting the sunrise and sunset times from a server. The server either responds with the requested information, or it responds with a description of what went wrong.

```Swift
enum ServerResponse {
    case result(String, String)
    case failure(String)
}

let success = ServerResponse.result("6:00 am", "8:09 pm")
let failure = ServerResponse.failure("Out of cheese.")

switch success {
case let .result(sunrise, sunset):
    print("Sunrise is at \(sunrise) and sunset is at \(sunset).")
case let .failure(message):
    print("Failure...  \(message)")
}
// Prints "Sunrise is at 6:00 am and sunset is at 8:09 pm."
```

> __Վարժություն։__ `ServerResponse`-ի համար ավելացրեք երրորդ դեպքը և լրացրեք `switch`-ում։

Ուշադրություն դարձրեք, թե ինչպես են `sunrise` և `sunset` արժեքները ստացվում `ServerResponse` արժեքից՝ որպես `switch`-ի ճյուղին համապատասխանեցման արժեք։

Ստրուկտուրա սահմանելու համար օգտագործեք `struct` բառը։ Ստրուկտուրաները վարքով շատ նման են դասերին՝ ներառյալ մեթոդներն ու արժեքավորիչները։ Ստրուկտուրաների ու դասերի կարևոր տարբերություններից մեկն այն է, որ կոդում այս կամ այն տեղը փոխանցելիս ստրուկտուրաների նմուշները միշտ պատճենվում են, իսկ դասերի նմուշները փոխանցվում են հղումով։

```Swift
struct Card {
    var rank: Rank
    var suit: Suit
    func simpleDescription() -> String {
        return "The \(rank.simpleDescription()) of \(suit.simpleDescription())"
    }
}
let threeOfSpades = Card(rank: .three, suit: .spades)
let threeOfSpadesDescription = threeOfSpades.simpleDescription()
```

> __Վարժություն։__ Գրեք ֆունկցիա, որը վերադարձնում է քարտերի լրիվ կապոցը, որտեղ ամե մի քարտը `Rank`-ի ու `Suit`-ի համադրություն է։


## Համաձայնագրեր և ընդլայնումներ

Համաձայնագիր (protocol) սահմանելու ամար օգտագործեք `protocol` բառը։

```Swift
protocol ExampleProtocol {
    var simpleDescription: String { get }
    mutating func adjust()
}
```

Դասերը, թվարկումները և ստրուկտուրաները կարող են ներառել (adopt), ընդունել համաձայնագրերը։ 

```Swift
class SimpleClass: ExampleProtocol {
    var simpleDescription: String = "A very simple class."
    var anotherProperty: Int = 69105
    func adjust() {
        simpleDescription += "  Now 100% adjusted."
    }
}
var a = SimpleClass()
a.adjust()
let aDescription = a.simpleDescription

struct SimpleStructure: ExampleProtocol {
    var simpleDescription: String = "A simple structure"
    mutating func adjust() {
        simpleDescription += " (adjusted)"
    }
}
var b = SimpleStructure()
b.adjust()
let bDescription = b.simpleDescription
```

> __Վարժություն։__ Եվս մի պահանջ ավելացրեք `ExampleProtocol`-ում։ Ի՞նչ փոփոխություններ պետք է անեք `SimpleClass`-ում և `SimpleStructure`-ում, որպեսզի դրանք շարունակեն ընդունել համաձայնագիրը։

Ուշադրություն դարձրեք `SimpleStructure`-ի սահմանման մեջ օգտագործված `mutating` ծառայողական բառին, որով նշվում է այն մեթոդը, որը փոփոխություններ է կատարում ստրուկտուրայում։ `SimpleClass`-ի սահմանման մեջ կարիք չկա որևէ մեթոդ նշել որպես `mutating`, քանի որ դասի մեթոդները միշտ կարող են փոփոխել դասի նմուշի արժեքները։

Գոյություն ունեցող տիպին նոր ֆունկցիոնալություն, ինչպիսիք են նոր մեթոդը կամ հաշվարկված հատկությունը, ավելացնելու համար օգտագործեք `extension`-ը։ Ընդլայնման հնարավորությունը կարող եք օգագործել մի այլ տեղում սահմանված կամ նույնիսկ գրադարանից ներմուծված տիպին համաձայնագիր կապելու համար։

```Swift
extension Int: ExampleProtocol {
    var simpleDescription: String {
        return "The number \(self)"
    }
    mutating func adjust() {
        self += 42
    }
}
print(7.simpleDescription)
// Prints "The number 7"
```

> __Վարժություն։__ `Double` տիպի համար գրեք `absoluteValue` հատկությունն ավելացնող ընդլայնում։

Համաձայնագրի անունը կարող եք օգտագործել ինչպես որևէ այլ տիպի անուն, օրինակ, որպեսզի ստեղծենք հավաքածու այնպիսի օբյեկտների համար, որոնց տիպերը տարբեր են, բայց բոլորն էլ ընդունում են նույն համաձայնագիրը։ Երբ աշխատում եք այնպիսի արժեքների հետ, որոնք տիպը համաձայնագրի տիպ է, ապա համաձայնագրից դուրս սահմանված մեթոդները հասանելի չեն։

```Swift
let protocolValue: ExampleProtocol = a
print(protocolValue.simpleDescription)
// Prints "A very simple class.  Now 100% adjusted."
// print(protocolValue.anotherProperty)  // Uncomment to see the error
```

Չնայած որ `protocolValue` փոփոխականը կատարման ժամանակ ունի `SimpleClass` տիպը, կոմպիլյատորն այն դիտարկում է հայտարաված `ExampleProtocol` տիպով։ Սա նշանակում է, որ չեք կարող պատահաբար հասանելիություն ստանալ այն մեթոդներին ու հատկություններին, որոնք դասը իրականացնում է ի լրումն իր համաձայնագրելի համապատասխանության։


## Սխալների մշակում

սխաները կարող եք ներկայացնել որևէ տիպով, որը ընդունում է `Error` համաձայնագիրը։

```Swift
enum PrinterError: Error {
    case outOfPaper
    case noToner
    case onFire
}
```

Սխալ գեներացնելու համար օգտագործեք `throw` բառը, իսկ `throws` բառը՝ սխալ գեներացնող ֆունկցիան նշելու համար։ Եթե ֆունկցիայի մեջ սխալ եք գեներացնում, ապա ֆունցկաին անմիջապես ավարտվում է, և այդ ֆունկցիան կանկչող կոդը մշակում է սխալը։

```Swift
func send(job: Int, toPrinter printerName: String) throws -> String {
    if printerName == "Never Has Toner" {
        throw PrinterError.noToner
    }
    return "Job sent"
}
```

Սխալների մշակման մի քանի եղանակներ կան։ Մի եղանակը `do`-`catch` կառուցվածքն է։ `do` բլոկում նշում եք այն կոդը, որը կարող է սխալ գեներացնել՝ դրա դիմաց գրելով `try` բառը։ `catch` բլոկում սխալին ավտոմատ տրվում է `error` անունը, եթե այլ անուն չեք նշել։

```Swift
do {
    let printerResponse = try send(job: 1040, toPrinter: "Bi Sheng")
    print(printerResponse)
} catch {
    print(error)
}
// Prints "Job sent"
```

> __Վարժություն։__ Տպիչի անունը դարձրեք «Never Has Toner», որպեսզի `send(job:toPrinter:)` ֆունկցիայի կանչը սխալ գեներացնի։

Տարբեր տիպի սխալներ մշակելու համար կարող եք մի քանի `catch` բլոկներ գրել։ `catch`-ից հետո կարող եք ձևանմուշ գրել. ճիշտ այնպես, ինչպես `switch`-ի `case`-ից հետո։

```Swift
do {
    let printerResponse = try send(job: 1440, toPrinter: "Gutenberg")
    print(printerResponse)
} catch PrinterError.onFire {
    print("I'll just put this over here, with the rest of the fire.")
} catch let printerError as PrinterError {
    print("Printer error: \(printerError).")
} catch {
    print(error)
}
// Prints "Job sent"
```

> __Վարժություն։__ Ավելացրեք կոդ, որը սխալ կգեներացնի `do` բլոկում։ Ի՞նչ տիպի սխալ պետք է գեներացնեք, որ այն մշակվի առաջին `catch` բլոկում։ Իսկ ինչպիսի՞ն՝ երկրորդ և երրորդ `catch` բլոկներում մշակվելու համար։

Սխալները մշակելու մի այլ եղանակ է `try?`-ի օգնությամբ արժեք optional-ի ձևափոխելը։ Եթե ֆունկցիան սխալ է գեներացնում, ապա սխալի օբյեկտը դեն է նետվում և արդյունքը համարվում է `nil`։ Հակառակ դեպքում արդյունքը optional է, որը պարունակում է ֆունկցիայի վերադարձրած արժեքը։ 

```Swift
let printerSuccess = try? send(job: 1884, toPrinter: "Mergenthaler")
let printerFailure = try? send(job: 1885, toPrinter: "Never Has Toner")
```

Ֆունկցիայի ամբողջ կոդը կատարվելուց հետո և հենց ֆունկցիայի ավարտից առաջ կատարվող կոդ գրելու համար օգտագործեք `defer`-ը։ Այդ կոդը կատարվում է նույնիսկ եթե ֆունկցիայում սխալ է գեներացվել։ `defer`-ը կարող եք օգտագործել կարգավորումների (setup) ու մաքրման (cleanup) կոդերն իրար մոտ գրելու համար, թեկուզ և դրանք կատարվում են տարբեր ժամանակ։

```Swift
var fridgeIsOpen = false
let fridgeContent = ["milk", "eggs", "leftovers"]

func fridgeContains(_ food: String) -> Bool {
    fridgeIsOpen = true
    defer {
        fridgeIsOpen = false
    }

    let result = fridgeContent.contains(food)
    return result
}
fridgeContains("banana")
print(fridgeIsOpen)
// Prints "false"
```


## Generic-ներ

Ընդհանրացված (generic) ֆունկցիա կամ տիպ սահմանելու համար դրա անունից հետո, անկյունավոր փակագծերում գրեք պարամետրի անունը։

```Swift
func makeArray<Item>(repeating item: Item, numberOfTimes: Int) -> [Item] {
    var result = [Item]()
    for _ in 0..<numberOfTimes {
        result.append(item)
    }
    return result
}
makeArray(repeating: "knock", numberOfTimes: 4)
```

Կարող եք սահմանել ֆունկցիաների ու մեթոդների, ինչպես նաև դասերի, թվարկումների ու ստրուկտուրաների ընդհանրացված ձևերը։

```Swift
// Reimplement the Swift standard library's optional type
enum OptionalValue<Wrapped> {
    case none
    case some(Wrapped)
}
var possibleInteger: OptionalValue<Int> = .none
possibleInteger = .some(100)
```

`where` բառով սահմանեք նախապայմաններ՝ գրելով մարմնից անմիջապես առաջ, օրինակ, պահանջելու համար, որ տիպը ընդունի համաջայնագիրը, կամ պահանջելու համար, որ երկու տիպեր նույնը լինեն, կամ էլ պահանջելու համար, որ դասը ժառանգված լինի որևէ կոնկրետ դասից։

```Swift
func anyCommonElements<T: Sequence, U: Sequence>(_ lhs: T, _ rhs: U) -> Bool
    where T.Element: Equatable, T.Element == U.Element
{
    for lhsItem in lhs {
        for rhsItem in rhs {
            if lhsItem == rhsItem {
                return true
            }
        }
    }
    return false
}
anyCommonElements([1, 2, 3], [3])
```

> __Վարժություն։__ Ձևափոխեք `anyCommonElements(_:_:)` ֆունկցիան այնպես, որ վերադարձնի այն տարրերի ցուցակը, որոնք երկու հաջրդականություններում էլ առկա են։

`<T: Equatable>` գրառումը համարժեք է `<T> ... where T: Equatable` գրառմանը։
