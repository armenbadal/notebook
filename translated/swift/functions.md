# Ֆունկցիաներ

> Թարգմանված է https://docs.swift.org/swift-book/LanguageGuide/Functions.html

_Ֆունկցիաները_ կոդի ինքնաբավ կտորներ են, որոնք կատարում են որոշակի աշխատանք։ Ֆունկցիային անուն եք տալիս, որը ցույց է տալիս, թե ինչ է այն անում, և այդ անունն օգտագործվում է որպեսզի ֆունկցիան «կանչվի» և կատարի իր գործը։

Swift-ի ֆունկցիայի քերականությունը բավարար ճկուն է, որպեսզի հնարավորություն տա արտահայտել որևէ բան՝ սկսզծ C-ոճի առանց պարամետրերի անունների ֆունկցիաներից, մինչև Objective-C-ոճի բարդ մեթոդ՝ ամեն մի պարամետրի համար անունով ու պիտակով։ ?? պարամետրերը կարող են ունենալ լռելության արժեքներ՝ ֆունկցիայի կանչը պարզեցնելու համար, և կարող են փոխանցվել որպես in-out պարամետրեր, որոնք ֆունկցիայի կատարումից հետո փոխում են փոխանցված փոփոխականի արժեքը։

Swift-ում յուրաքանչյուր ֆունկցիա ունի տիպ, որը բաղկացած է ֆունկցիայի պարամետրերի տիպերից և վերադարձվող արժեքի տիպից։ Այս տիպը կարող եք օգտագործել Swift-ի կամայական այլ տիպի պես. սա հնարավորություն է տալիս ֆունկցիաները որպես պարամետր փոխանցել այլ ֆունկցիաների, և ֆունկցիան վերադարձնել մի այլ ֆունկցիայից։ ֆունկցիաները կարող են սահմանվել նաև մի այլ ֆունկցիայի մեջ՝ սահմանափակելով օգտակար ֆունկցիոնալությունը պարփակող ֆունկցիայի տիրույթում։ 


## Ֆունկցիաների սահմանելն ու կանչելը

Երբ դուք ֆունկցիա եք սահմանում, կարող եք սահմանել նաև _պարամետր_ կոչվող մեկ կամ ավելի անվանված, տիպիզացված արժեքներ, որոնք ֆունկցիան ստանում է որպես մուտքային արժեքներ։ Կարող եք նաև սահմանել այն արժեքի տիպը, որը ֆունկցիան վերադարձնելու է որպես ելքային արժեք. դա _վերադարձվող արժեքի տիպն_ է։ Թե՛ պարամետրերը, թե՛ վերադարձվող արժեքի տիպը պարտադիր չեն։

Բոլոր ֆունկցիաներն ունեն _ֆունկցիայի անուն_, որով նկարագրվում է ֆունկցիայի կատարելիք խնդիրը։ Ֆունկցիան օգտագործելու համար այն «կանչում» եք իր անունով և դրա մուտքին փոխանցում եք ֆունկցիայի պարամետրերի տիպերին համապատասխանող արժեքներ՝ _արգումենտներ_։ Ֆունկցիայի արգումենտները միշտ պետք է փոխանցվեն պարամետրերի հերթագայությանը համապատասխան։ 

Ստորև բերված օրինակի ֆունկցիան անվանված է `greet(person:)`, որովհետև դա հենց այն է, ինչ նա անում է՝ մուտքում վերցնում է մարդու անունը և վերադարձնում է այդ մարդու համար ողջույնի տեքստը։ Դրան հասնելու համար սահմանում եք մեկ մուտքային պարամետր՝ `String` արժեք `person` անունով, վերադարձվող արժեքի տիպն էլ՝ նորից `String`, որն էլ պարունակելու է տվյալ անձի ողջույնի տեքստը.

```Swift
func greet(person: String) -> String {
    let greeting = "Hello, " + person + "!"
    return greeting
}
```

Ամբողջ այս տեղեկույթը պարփակված է ֆունկցիայի սահմանման մեջ, որը սկսվում է `func` ծառայողական բառով։ Ֆունկցիայի վերադարձվող արժեքի տիպը նշվում է _`->` վերադարձնող սլաքով_ (գծիկ, որին հաջորդում է մեծի նշանը), որին էլ հետևում է վերադարձվող արժեքի տիպի անունը։

Սահմանումը նկարագրում է, թե ֆունկցիան ինչ է անում, ինչ է սպասում ստանալ և ինչ է վերադարձնելու երբ ավարտվի։ Սահմանումը հեշտացնում է կոդի ցանկացած հատվածում ֆունկցիայի միարժեք կանչը.

```Swift
print(greet(person: "Anna"))
// Prints "Hello, Anna!"
print(greet(person: "Brian"))
// Prints "Hello, Brian!"
```

Դուք `greet(person:)` ֆունկցիան կանչում եք դրան `String` արժեք փոխանցելով արգումենտի `person` պիտակից հետո, օրինակ, `greet(person: "Anna")`։ Քանի որ ֆունկցիան վերադարձնում է `String` արժեք, `greet(person:)`-ի կանչը կարող է ներդրվել `print(_:separator:terminator:)` ֆունկցիայի կանչի մեջ, որպեսզի արտածվի այդ տողը և ցույց տրվի վերադարձված արժեքը։ 

> NOTE `print(_:separator:terminator:)` ֆունկցիայի առաջին արգումենտը պիտակ չունի, իսկ մյուս արգումենտները ոչ պարտադիր են, քանի որ ունեն լռելության արժեքներ։ Ֆունկցիայի քերականության այսպիսի տարբերակներ քննարկվում են ստորև՝  Function Argument Labels and Parameter Names և Default Parameter Values ենթագլուխներում։

`greet(person:)` ֆունկցիայի մարմինը սկսվում է `greeting` անունով `String` հաստատունի սահմանումով, որին վերագրվում է ողջույնի տեքստը։ Կոդի `return greeting` տողում ֆունկցիան ավարտում է իր կատարումը և վերադարձնում է `greeting`-ի ընթացիկ արժեքը։

`greet(person:)` ֆունկցիան կարող եք մի քանի անգամ կանչել՝ տարբեր արգումենտներով։ Վերը բերված օրինակը ցույց է տալիս, թե ինչ է կատարվում, երբ այն կանչվել է `Anna` և `Brian` մուտքային արժեքներով։ Ամեն մի տեպքի համար ֆունկցիան վերադարձնում է հարմարեցված ողջույնի տեքստ։

Այս ֆունկցիայի մարմինն ավելի կարճ գրելու համար կարող եք հաղորդագրության կառուցումն ու `return` հրամանի միատեղել մեկ տողում.

```Swift
func greetAgain(person: String) -> String {
    return "Hello again, " + person + "!"
}
print(greetAgain(person: "Anna"))
// Prints "Hello again, Anna!"
```


## Ֆունկցիայի պարամետրերն ու վերադարձվող արժեքները

Swift-ի ֆունկցիայ պարամետրերն ու վերադարձվող արժեքների հնարավորությունները զարմանալիորեն բազմազան են։ Դուք կարող եք սահմանել ամեն ինչ՝ սկսած միակ անանուն պարամետրով պարզ օգնական ֆունկցիայից, մինչև բարդ ֆունկցիա՝ պարամետրերի արտահայտիչ անուններով և պարամետրերի զանազան հատկություններով։

### Առանց պարամետրի ֆունկցիաներ

Պարտադիր չէ, որ ֆունկցիաները սահմանվեն մուտային պարամետրերով։ Ահա մի ֆունկցիա՝ առանց պարամետրերի, որը միշտ, երբ էլ որ կանչվի, վերադարձնում է նույն `String` տիպի հաղորդագրությունը։ 

```Swift
func sayHelloWorld() -> String {
    return "hello, world"
}
print(sayHelloWorld())
// Prints "hello, world"
```

Այս դեպքում նույնպես ֆունկցիայի սահմանումը պահանջում է անունից հետո գրել փակագծերի զույգ, թեև այն պարամետրեր չունի։ Ֆունկցիայի կանչի ժամանակ էլ պետք է անունից հետո գրել փակագծերի դատարկ զույգը։


### Մի քանի պարամետրերով ֆունկցիաներ

Ֆունկցիաները կարող են ունենալ մի քանի մուտքսյին պարամետրեր, որոնք գրված են կլոր փակագծերի մեջ՝ ստորակետով անջատված։

Հետևյալ ֆունկցիան մուտքում ստանում է մարդու անունը և թե արդյո՞ք այդ մարդն արդեն ողջունվել է, ապա այդ մարդու համար վերադարձնում է ողջույնի համապատասխան տեքստը։

```Swift
func greet(person: String, alreadyGreeted: Bool) -> String {
    if alreadyGreeted {
        return greetAgain(person: person)
    } else {
        return greet(person: person)
    }
}
print(greet(person: "Tim", alreadyGreeted: true))
// Prints "Hello again, Tim!"
```

Դուք կանչում եք `greet(person:alreadyGreeted:)` ֆունկցիան՝ փակագծերում, ստորակետով անջատված դրան փոխանցելով `person` պիտակով տեքստային արգումենտը և `alreadyGreeted` պիտակով բուկյան արգումենտը։ Ուշադրություն դարձրեք, որ այս ֆունկցիան տարբեր է վերը հիշատակված `greet(person:)` ֆունկցիայից։ Չնայած որ երկու ֆունկցիաներն էլ սկսվում են `greet` բառով, `greet(person:alreadyGreeted:)` ֆունկցիան սպասում է երկու արգումենտ, իսկ `greet(person:)`-ը՝ միայն մեկը։

### Առանց վերադարձվող արժեքի ֆունկցիաներ

Պարտադիր չէ, որ ֆունկցիաները արժեք վերադարձնեն։ Ահա `greet(person:)` ֆունկցիայի մի տարբերակ, որը, վերադարձնելու փոխարեն, արտածում է ողջույնի տեքստը։

```Swift
func greet(person: String) {
    print("Hello, \(person)!")
}
greet(person: "Dave")
// Prints "Hello, Dave!"
```

Քանի որ այս ֆունկցիան արժեք չի վերադարձնում, դրա սահմանումը չի պարունակում սլաքը (`->`) և վերադարձվող արժեքի տիպը։

> NOTE Ավելի խիստ ասած, `greet(person:)`-ի այս տարբերակը արժեք վերադարձնում է, չնայած որ վերադարձվող արժեքի տիպ սահմանված չէ։ Առանց վերադարձվող արժեքի տիպի սահմանված ֆունկցիաները վերադարձնում են `Void` տիպի հատուկ արժեք։ Դա պարզապես դատարկ n-յակ է (tuple), որը գրվում է `()` տեսքով։

Ֆունկցիան կանչելիս դրա վերադարձրած արժեքը կարող է անտեսվել.

```Swift
func printAndCount(string: String) -> Int {
    print(string)
    return string.count
}
func printWithoutCounting(string: String) {
    let _ = printAndCount(string: string)
}
printAndCount(string: "hello, world")
// prints "hello, world" and returns a value of 12
printWithoutCounting(string: "hello, world")
// prints "hello, world" but doesn't return a value
```

Առաջին ֆունկցիան՝ `printAndCount(string:)`-ը, տպում է տողը, ապա վերադարձնում է դրա նիշերի քանակը որպես `Int` արժեք։ Երկրորդ ֆունկցիան՝ `printWithoutCounting(string:)`-ը, կանչում է առաջինին, բայց անտեսում է դրա վերադարձրած արժեքը։ Երբ երկրորդ ֆունկցիան կանչվում է, հաղորդագրությունը նորից տպվում է առաջին ֆունկցիայի միջոցով, բայց վերադարձրած արժեքը չի օգտագործվում։

> NOTE Վերադարձվող արժեքները կարող են անտեսվել, բայց եթե ֆունկցիան սահմանված է որպես արժեք վերադարձնող, ապա պետք է այն վերադարձնի։ Վերադարձվող արժեքի տիպով սահմանված ֆունկցիան չի կարող թույլ տալ, որ ղեկավարումը հասնի ֆունկցիայի վերջին, առանց արժեք վերադարձնելու, և դրա փորձը կբերի կոմպիլյացիայի ժամանակի սխալի։


### Մի քանի վերադարձվող արժեքներով ֆունկցիաներ

Բաղադրյալ արժեքի տեսքով մի քանի արժեքներ վերադարձնելու համար դուք կարող եք որպես ֆունկցիայի վերադարձվող արժեքի տիպ օգտագործել n-յակի (tuple) տիպը։

Ստորև բերված օրինակում սահմանված է `minMax(arraj:)` ֆունկցիան, որը `Int` տիպի արժեքների զանգվածում գտնում է ամենափոքր և ամենամեծ տարրերը։

```Swift
func minMax(array: [Int]) -> (min: Int, max: Int) {
    var currentMin = array[0]
    var currentMax = array[0]
    for value in array[1..<array.count] {
        if value < currentMin {
            currentMin = value
        } else if value > currentMax {
            currentMax = value
        }
    }
    return (currentMin, currentMax)
}
```

`minMax(array:)` ֆունկցիան վերադարձնում է երկու `Int` արժեք պարունակող n-յակ (tuple)։ Այս արժեքները նշված են `min` և `max` պիտակներով, որպեսզի հնարավոր լինի ֆունկցիայի վերադարձրած արժեքից դրանց դիմել այդ պիտակներով։

`minMax(array:)` ֆունկցիայի մարմինը սկսվում է երկու աշխատանքային փոփոխականների սահմանումով՝ `currentMin` և `currentMax`, որոնց վերագրվում է ամբողջ թվերի զանգվածի առաջին տարրը։ Այնուհետև ֆունկցիան թվարկում է զանգվածի մյուս տարրերը և ստուգում է, թե դրանցից յուրաքանչյուրն արդյոք փո՞քր է, թե՞ մեծ է `currentMin`-ի և `currentMax`-ի արժեքներից համապատասխանաբար։ Վերջապես, հաշվարկված ամենամեծ ու ամենափոքր արժեքները վերադարձվում են որպես `Int` արժեքների զույգ։

Քանի որ n-յակի անդամների անունները ֆունկցիայի վերադարձվող արժեքի տիպի սահմանաման մաս են, դրանց կարելի է դիմել _կետ_ (`.`) գործողությամբ՝ գտնված ամենափոքր ու ամենամեծ արժեքները ստանալու համար։

```Swift
let bounds = minMax(array: [8, -6, 2, 109, 3, 71])
print("min is \(bounds.min) and max is \(bounds.max)")
// Prints "min is -6 and max is 109"
```

Ուշադրություն դարձրեք, որ կարիք չկա n-յակի անդամներին անուններ տալ այն կետում, որտեղ n-յակը վերադարձվում է ֆունկցիայից, քանի որ դրանց անուններն արդեն նշվել էին որպես ֆունկցիայի վերադարձվող արժեքի մաս։


