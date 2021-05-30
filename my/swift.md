# Խառը գրառումներ Swift-ի մասին

## Փորձեր «Սակրավոր» խաղի մոդելի համար

Ես ուզում եմ Swift-ով մոդելավորել հայտնի _Սակրավոր_ (_Minesweeper_) խաղի խաղադաշտը։ Ուրեմն, խաղադաշտը բաղկացած է բջիջներից, որոնք կարող են ական պարունակել կամ չպարունակել։ Խաղի ընթացքում բջիջը կարող է լինել երեք տարբեր վիճակներում. փակ (դեռ չբացված), բացված և դրոշակով նշված։ Բջջում պետք է պահել նաև նրա հարևան բջիջներում եղած ականների քանակը։

```Swift
class Cell {
    enum State: Int {
        case Closed   // փակ
        case Open     // բաց
        case Flagged  // նշված
    }

    var state = State.Closed  // վիճակ
    var hasMine = false       // ական
    var minesAround = 0       // հարևան ականներ
}
```

Բջջի տեաստային ներկայացումը ստանալու համար `Cell` դասը պետք է ընդունի `CustomStringConvertible` համաձայնագիրը (protocol)։ Այդ համաձայնագիրը պարունակում է `description` հատկության նկարագրությունը, որն էլ պիտի իրականացնել `Cell` դասի համար։

```Swift
class Cell: CustomStringConvertible {
    enum State: Int {
        case Closed   // փակ
        case Open     // բաց
        case Flagged  // նշված
    }

    var state = State.Closed  // վիճակ
    var hasMine = false       // ական
    var minesAround = 0       // հարևան ականներ

    // տեքստային ներկայացում
    var description: String {
        if self.state == .Closed {
            return "?"
        }

        if self.state == .Flagged {
            return "F"
        } 

        if self.hasMine {
            return "*"
        }

        return 0 == minesAround ? "." : String(minesAround)
    }
}
```

Խաղադաշտը բջիջների մատրից է՝ տրված քանակի տողերով ու սյուներով։ `Field` դասի արժեքավորիչի մեջ՝ `init` բլոկում, ստեղծում եմ `cells` (բջիջներ) մատրիցը։ Ինտերնետում քչփորելիս հանդիպեցի մատրիցը դինամիկ ստեղծելու մի հնարքի՝ `Range` օբյեկտի `map` գործողության օգնությամբ։ `map`-երից երկրորդը՝ ներդրվածը `Cell`-եր ստեղծելով կառուցում է մատրիցի տողը, իսկ արտաքինը՝ տողեր ստեղծելով կառուցում է մատրիցը։

Հետո պիտի դաշտում տեղադրեմ ականները։ Մտածեցի, որ ընդհանուր բջիջների 15-20 տոկոսում ական դնելը բավարար կլինի։ Ընտրում եմ պատահական բջիջներ ու դրանց `hasMine`-ը դարձնում եմ `true`: Դրանից հետո ամեն մի ական չունեցող բջջի համար հաշվում եմ դրա հարևան ականների քանակը ու պահում եմ բջջի `minesAround` հատկության մեջ։ `(r, c)` բջջի բոլոր ութ հարևաններին որոշելու համար պահել եմ տարբերությունների վեկտորը՝ `rcix`, որի ամեն մի տարրը զույգ է և որոշում է դիտարկվող բջջի և հարևանի դիրքերի տարբերությունը։

```Swift
class Field {
    let rows: Int        // տողերի քանակը
    let columns: Int     // սյուների քանակը
    var cells: [[Cell]]  // ականադաշտի մատրիցը
    let minesCount: Int  // ականների քանակը

    init(rows: Int, columns: Int) {
        self.rows = rows
        self.columns = columns

        // մատրիցի ստեղծելը
        cells = (0..<rows).map { _ in (0..<columns).map { _ in Cell() } }

        // ականների տեղադրելը
        minesCount = rows * columns * 15 / 100
        for _ in 0..<minesCount { 
            let r = Int.random(in: 0..<rows)
            let c = Int.random(in: 0..<columns)
            self.cells[r][c].hasMine = true
        }

        // հաշվել ամեն մի բջջի հարևան ականները
        let rcix = [(-1, -1), (0, -1), (1, -1), (-1, 0), (1, 0), (-1, 1), (0, 1), (1, 1)]
        for r in 0..<self.rows {
            for c in 0..<self.columns {
                if self.cells[r][c].hasMine {
                    continue
                }

                var count = 0
                for (dr, dc) in rcix {
                    let nr = r + dr
                    let nc = c + dc
                    if self.cells[nr][nc].hasMine {
                        count += 1
                    }
                }
                self.cells[r][c].minesAround = count
            }
        }
    }
}
```


## Առաջին ծրագիրը

Լեզվի տարրական հնարավորությունների մասին մի քիչ կարդալուց հետո և մանր-մունր արտահայտությունների վրա ինչ-որ փորձարկումներ անելուց հետո որոշեցի գրել հաշվարկման _տասական_ համակարգում գրված ամբողջ թվի _տասնվեցական_ ներկայացումը վերադարձնող ֆունկցիան։

Շատ պարզ խնդիր է, որը ես սովորաբար գրում եմ ռեկուրսիայի կիրառմամբ։ Օրինակ, Պիթոն լեզվով կարող եմ գրել.

```Python
def oHex(num):
    c = "0123456789abcdef"[num % 16]

    return c if num < 16 else oHex(num // 16) + c
```

Այս նույնն արտագրեցի Swift-ով՝ դեռևս ամենապարզ կառուցվածքներով.

```Swift
func oHex(num: Int) -> String {
    let digits = "0123456789abcdef"

    if num < 16 {
        return digits[num]
    }

    return oHex(num / 16) + digits[num % 16]
}
```

Ու, ինչպես ասում են, սկսվեց կինոն։ Բանից պարզվում է, որ Swift լեզվում տողի ինդեքսավորման գործողությունը սպասում է ոչ թե `Int` (ամբղջ թիվ), այլ ինչ-որ `Index` տիպի օբյեկտ, ու այդ օբյեկտը `num % 16` արժեքի համար կառուցվում է ինչ-որ խառը եղանակով։ Հետո պարզվեց, որ ֆունկցիայի կանչի ժամանակ պետք է գրել պարամետրի անունը (եթե ֆունկցիան սահմանելիս պարամետրից առաջ չի գրվել `_`)։ Ինտերնետում մի քիչ քչփորելուց հետո գրեցի հետևյալը.

```Swift
func oHex(number: Int) -> String {
    let digits = "0123456789abcdef"
    let inx = digits.index(digits.startIndex, offsetBy: number % 16)
    let sym = String(digits[inx])

    if number < 16 {
        return sym
    }

    return oHex(number: number / 16) + sym
}
```

Սա արդեն աշխատում է ու տրված թվի համար վերադարձնում է դրա տասնվեցական ներկայացումը՝ տողի տեսքով։


## Բարձր կարգի ֆունկցիա

Հաջորդ հարցը, որ ուզում էի ինձ համար պարզել, այն է, թե ինչպես է սահմանվում ու օգտագործվում _բարձր կարգի ֆունկցիան_՝  ֆունկցիա, որը արգումենտում սպասում է ֆունկցիա կամ որպես արժեք վերադարձնում է ֆունկցիա։ 

Որպես օրինակ վերցրել եմ, _[a, b]_ միջակայքի վրա սեղանների մեթոդով _f(x)_ ֆունկցիայի ինտեգրալի թվային հաշվարկի խնդիրը։ Պիթոն լեզվով ես դա կգրեմ մոտավորապես այսպես.

```Python
def integral(f, a, b):
    d = (b - a) / 1e6

    s = 0
    while a < b:
        b0 = f(a)
        b1 = f(a + d)
        s += (b0 + b1) / 2.0 * d
        a += d

    return s
```

Կիրառությունն էլ շատ պարզ է.

```Python
print(integral(lambda x: x * x, 0.0, 1.0))
```

Նախ փորձեցի նույնը արտագրել Swift լեզվով. ֆունկցիայի պարամետրերի անունները փոխեցի՝ Swift- գրառման ոճին ավելի սազական դարձնելու համար։

```Swift
func integral(of: (Double)->Double, from: Double, to: Double) -> Double {
    let delta = (to - from) / 1e6

    var value = 0.0
    var px = from
    while px < to {
        let h0 = of(px)
        let h1 = of(px + delta)
        value += (h0 + h1) / 2.0 * delta
        px += delta
    }
    
    return value
}
```

Ֆունկցիայի վերնագրում `of` պարամետրի տիպը ֆունկցիա է, որը սպասում է `Double` արժեք և վերադարձնում է `Double` արժեք։ Այսինքն `integral` ֆունկցիան կիրառելու ժամանակ պետք է տալ ֆունկցիա՝ `Closure`, լամբդա-ֆունկցիա կամ սահմանված ֆունկցիայի անուն։ Այսպես, օրինակ.

```Swift
let ri = integral(of: { (x: Double)->Double in return x * x }, from: -1.0, to: 1.0)
print(ri)
```

Կամ, եթե արդեն ունենք արդեն սահմանված `sqr` ֆունկցիան.

```Swift
func sqr(x: Double) -> Double {
    return x * x
}
```

Ապա կարելի է գրել.

```Swift
let ri = integral(of: sqr, from: -1.0, to: 1.0)
print(ri)
```

Հետո հայտնաբերեցի ավելի հետաքրքիրը։ Պարզվում է, որ եթե ֆունկցիայի վերջին պարամետրն է հայտարարված որպես ֆունկցիա, օրինակ.

```Swift
func integral(from: Double, to: Double, of: (Double)->Double) -> Double {
    // ...
}
```

ապա կիրառումը կարող է ստանալ լրիվ այլ տեսք.

```Swift
let ri = integral(from: -1.0, to: 1.0) {
    (x: Double)->Double in
        x * x
}
print(ri)
```

Այսինքն, տվյալ դեպքում, այն ֆունկցիան, որի ինտեգրալը պետք է հաշվել, կարելի է տալ ֆունկցիայի արգումենտների ցուցակի վերջում որպես `Closure`։ 

