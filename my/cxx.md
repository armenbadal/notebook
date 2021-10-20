# Խառը գրառումներ C++-ի մասին

## Ստուգման նոր կանոն clang-tidy գործիքի համար

### Նախապատմություն

Ձելը բիլը տա՛կ։ Մի օր պարզվեց, որ մեր կոդի դասերից մեկում կա ժամանակային միավոր ներկայացնող մի անդամ, որի արժեքը ճիշտ չի ընթերցվում կոնֆիգուրացիայի ֆայլից։ Իրավիճակն ավելի լավ ներկայացնելու համար բերեմ պարզեցված C++ կոդը.

```C++
// կոնֆիգուրացիայի պարզեցված մոդելը
struct config {
    // ժամանակային ինտերվալը միլիվայրկյաններով
    int16_t intervalMs{0};
    // ինչ-որ տվյալների ինդեքս
    int16_t index{0};
    // ... և այլ
};
```

Այս կոդը ես էի գրել և, հավանաբար, անուշադրության պատճառով `intervalMs` անդամի տիպը թողել էի `int16_t`։ (Թե ինչու ժամանակային ինտերվալների համար չենք օգտագործում `std::chrono` անունների տիրույթի տիպերը՝ այլ խոսակցություն է։)

Այս ստրուկտուրայի առանձին դաշտերին արժեքներ վերագրելու համար սահմանված է մոտավորապես այսպիսի մի ֆունկցիա.

```C++
template<typename R>
void assign(R& place, const string& key, const json& data)
{
    if( const json_pointer jp{key}; data.contains(jp) )
        data.at(jp).get_as(place);
}

void read_config(config& cfg, const json& data)
{
    assign(cfg.intervalMs, "/interval-ms", data);
    assign(cfg.index, "/index", data);
}
```

Քանի դեռ կոնֆիգուրացիայում `interval-ms`-ն ուներ `int16_t` տիպում տեղավորվող արժեք, օրինակ, `12000`, ամեն ինչ լավ էր։ Օրինակ.

```C++
const auto example0 =
R"(
{
    "interval-ms": 12000,
    "index": 72
}
)"_json;
```

Բայց մի օր Հայկը կոնֆիգուրացիայում `interval-ms`-ի արժեքը դարձրեց `300000`, ու պարզվեց, որ ծրագիրը մեր սպասած վարքով չի աշխատում։ Կարճ ասած, սխալը գտանք, `intervalMs` անդամի տիպը փոխեցինք, ստուգեցինք, որ ամեն ինչ աշխատում է։ Ապահովության համար նորից անցանք կոնֆիգուրացիայի դասերի բոլոր այն անդամներով, որոնց անունն ունի `Ms` վերջածանցը ու համոզվեցինք, որ ուրիշ տեղ այդպիսի սխալ չունենք։

Ինչպե՞ս մեզ ապահվենք այս տիպի սխալներից։ Հայկը ոտի վրա ձևափոխեց `assign` ֆունկցիայի կաղապարն այնպես, որ ամբողջաթիվ տիպերի համար ստուգվի փոփոխականի գերհագեցումը (overflow): Մոտավորապես այսպես.

```C++
template<typename R>
void assign(R& place, const string& key, const json& data)
{
    if( const json_pointer jp{key}; data.contains(jp) ) {
        data.at(jp).get_to(place);

        if constexpr( is_integral_v<R> && !is_same_v<R, bool> ) {
            const auto vl = data.at(jp).get<uint64_t>();
            if( static_cast<int64_t>(place) != vl )
                throw runtime_error{"integer overflow detected"};
        }
    }
}
```

Սա մեզ հնարավորություն կտա կոնֆիգուրացիայի JSON ֆայլից տվյալները կարդալիս որսալ վերը նկարագրված սխալները։ Օրինակ, եթե մեր կոնֆիգուրացիան այսպիսինն է.

```json
const auto example2 = R"(
{
    "interval-ms": 300000,
    "count": 200
}
)"_json;
```

ապա հետևյալ կոդի կատարման արդյուքնում գեներացվելու է կատարման ժամանակի սխալ (`runtime_error`).

```C++
Config c;
assign(c.intervalMs, "/interval-ms", example2);
assign(c.count, "/count", example2);
```

### Պատմություն

Ես առաջարկեցի սկզբունքորեն այլ, թերևս նաև մի քիչ հումորային, լուծում։ Այն է՝ clang-tydi գործիքի ստատիկ ստուգումների կանոններին ավելացնել ևս մեկը, որը կգտնի `Ms` վերջածանցն ունեցող բոլոր անդամ-փոփոխականները և կստուգի, որ դրանց տիպը `int` (`int32_t`) է։ ԼԼՎՄ-ի հետ ունեցած իմ աշխատանքային փորձը հուշում էր, որ դա շատ հեշտ բան պիտի լինի։

[LLVM](https://llvm.org/) նախագծի [GitHub](https://github.com/llvm) էջից պատճենում ենք `llvm-project` շտեմարանը.

```bash
$ git clone --depth=1 https://github.com/llvm/llvm-project.git
```

_clang-tidy_-ի կոդը `clang-tools-extra` պրոյեկտի մեջ է։ Տեղափոխվում ենք այնտեղ.

```bash
$ cd llvm-project/clang-tools-extra/clang-tidy
```

Այստեղ մի սկրիպտ կա՝ `add_new_check.py`, որը մեզ օգնելու է ստուգման նոր կանոն ավելացնելու գործում. այն գեներացնում է բոլոր անհրաժեշտ ֆայլերը։ Ես գրեցի հետևյալը.

```bash
$ ./add_new_check.py misc variable-for-milliseconds
```

Սա նշանակում է, որ ես ուզում եմ `variable-for-milliseconds` անունով նոր կանոնն ավելացնել `misc` մոդուլին։ `git status` հրամանով կարող ենք տեղնել, թե `add_new_check.py` սկրիպտը ինչ նոր ֆայլեր է ստեղծել և թե որ ֆայլերում է փոփոխություններ կատարել.

```bash
git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
	modified:   misc/CMakeLists.txt
	modified:   misc/MiscTidyModule.cpp
	modified:   ../docs/ReleaseNotes.rst
	modified:   ../docs/clang-tidy/checks/list.rst

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	misc/VariableForMillisecondsCheck.cpp
	misc/VariableForMillisecondsCheck.h
	../docs/clang-tidy/checks/misc-variable-for-milliseconds.rst
	../test/clang-tidy/checkers/misc-variable-for-milliseconds.cpp

no changes added to commit (use "git add" and/or "git commit -a")
```

Սրանցից ինձ առաջին հերթին հետաքրքրում է `VariableForMillisecondsCheck.cpp` ֆայլը, որում էլ հենց գրելու եմ նոր կանոնի իրականացումը։ Այդ ֆայլում սահմանված են `VariableForMillisecondsCheck` դասի `registerMatchers` և `check` մեթոդները։


```C++
void VariableForMillisecondsCheck::registerMatchers(MatchFinder *Finder) {
  // ...
}

void VariableForMillisecondsCheck::check(const MatchFinder::MatchResult &Result) {
  // ...
}
```

Առաջինում, ինչպես երևում է անունից սահմանվում ու գրանցվում են աբստրակտ քերականական ծառի matcher-երը։ Matcher-ը պրեդիկատ է, որով որոշվում է ԱՔԾ-ի որևէ ենթածառ (մանրամասները տես այս [Matching the clang AST](https://clang.llvm.org/docs/LibASTMatchers.html))։ Տվյալ դեպքում ինձ հետաքրքրում են այն ենթածառերը, որոնցով մոդելավորված են դասի անդամ-փոփոխականների այն հայտարարությունները, որոնց տիպը `int` չէ։ Դա կարելի է գրել մոտավորապես այսպես.

```C++
void VariableForMillisecondsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(fieldDecl(unless(hasType(asString("int")))).bind("mv"), this);
}
```

Պրեդիկատների ցուցակը կարելի է գտնել [AST Matcher Reference](https://clang.llvm.org/docs/LibASTMatchersReference.html) էջում։

`VariableForMillisecondsCheck` դասի `check` մեթոդում էլ գրում եմ, թե ինչ պետք է անել այն դեպքերում, երբ հայտնաբերվել են matcherով նկարագրված ենթածառերը։ Տվյալ դեպքում պարզապես դուրս եմ բերում զգուշացնող հաղորդագրություն (warning)։

```C++
void VariableForMillisecondsCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<FieldDecl>("mv");
  if (MatchedDecl->getIdentifier() && MatchedDecl->getName().endswith("Ms"))
    diag(MatchedDecl->getLocation(), "member %0 is defined for milliseconds but it's size is not an int")
        << MatchedDecl;
}
```

clang-tidy-ն թույլ է տալիս նաև փոփոխություններ կատարել վերլուծության ծառում։ Տվյալ դեպքի համար, օրինակ, կարելի էր իրականացնել կտոր, որը մեզ հետաքրքրող հայտարարության տիպը դարձնում է `int`։ Բայց, ինչպես ասում էր դասականը, այդ մասին՝ հաջորդ դասին։

#### Build

LLVM-ի ծրագրերի կառուցման համակարգը գրված է CMake-ով։ Գեներացնում ենք մեզ անհրաժեշտ կոնֆիգուրացիան.

```bash
$ cd llvm-project
$ cmake -S llvm -B build -G Xcode -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra' -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD='X86'
```

Այստեղ ասել եմ, որ, ի լրումն LLVM միջուկի, ինձ հետաքրքրում են նաև `clang` ու `clan-tools-extra` նախագծերը։ Ասել եմ նաև, որ ուզում եմ կառուցել _x86_ պլատֆորմի _Release_ կոնֆիգուրացիան։

`clang-tidy` ծրագիրը կառուցելու (build) համար գործարկում ենք հետևյալը.

```bash
$ cmake --build build --target clang-tidy --config Release --parallel 4
```

Կախված կոմպյուտերի պրոցեսորի տեսակից `--parallel` պարամետրի արգումենտը կարելի է փոխել ու ստանալ կոմպիլյացիայի ու կապակցման ավելի կարճ ժամանակ։ Այնուամենայնիվ՝ սա երկար պրոցես է ու կարող է ժամեր տևել։

#### Օրինակ

Արվածը ստուգելու և ցուցադրելու համար պատրաստել եմ հետևյալ օրինակը.

```C++
struct String {
    unsigned int length;
    char* data;
};

struct Configuration {
    short int durationMs;  // 1
    long int intervalMs;   // 2
    int fromNowMs;         // 3
    short int count;       // 4
    String namesMs;        // 5
};
```

Ակնկալում եմ, որ այս օրինակի համար աշխատեցնելիս clang-tidy-ն բողոքելու է առաջին, երկրորդ և հինգերորդ փոփոխականների հայտարարությունների համար։ Փորձեմ.

```bash
$ clang-tidy --checks='-*,misc-variable-for-milliseconds' ex0.cxx --
3 warnings generated.
/Users/armenbadalian/Projects/a0/ex0.cxx:8:15: warning: member 'durationMs' is defined for milliseconds but it's size is not an int [misc-variable-for-milliseconds]
    short int durationMs;
              ^
/Users/armenbadalian/Projects/a0/ex0.cxx:9:14: warning: member 'intervalMs' is defined for milliseconds but it's size is not an int [misc-variable-for-milliseconds]
    long int intervalMs;
             ^
/Users/armenbadalian/Projects/a0/ex0.cxx:12:12: warning: member 'namesMs' is defined for milliseconds but it's size is not an int [misc-variable-for-milliseconds]
    String namesMs;
           ^
```

Կարծես թե վատ չէ։
