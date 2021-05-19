# Ծանոթություն Swift լեզվին

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