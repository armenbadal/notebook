# Խառը գրառումներ Կոտլինի մասին

## Տիպերի հիերարխիայի մասին

Կոտլին սովորելու համար ժամանակ առ ժամանակ բզբզում եմ [Ալգորիթմական լեզվի](https://github.com/armenbadal/algorithmic-kt) իրականացման պրոյեկտում։ Այդ լեզվի համար իրականացրել եմ տիպերի պարզագույն մի համակարգ։ Կա `VOID` տիպը, որը ծառայում է միայն ալգորիթմի ֆունկցիա կամ պրոցեդուրա լինելը տարբերելու համար։ Երբ ալգորիթմի վերադարձվող արժեքի տիպը `VOID` է, ապա այն պրզապես _պրոցեդուրա_ է, հակառակ դեպքում՝ _ֆունկցիա_ է։ Կա `Scalar` տիպը՝ իր երեք տարատեսակներով. `REAL` — իրական թիվ, `TEXT` — տեքստ եւ `BOOL` — տրամաբանական արժեք։ Եւ կա _միաչափ զանգված_՝ `Array`:

```Kotlin
interface Type

object Void : Type

enum class Scalar : Type {
    Real,
    Text,
    Bool
}

class Table(val size: Int, val base: Type) : Type
```


