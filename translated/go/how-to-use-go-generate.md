# Ինչպես օգտագործել `//go:generate`-ը

(Թարգմանված է. [How to Use //go:generate](https://blog.carlmjohnson.net/post/2016-11-27-how-to-use-go-generate/))

_Կիրակի, 27 նոյեմբերի, 2016_

`go generate` հրմանն ավելացվել է [Go 1.4](https://go.dev/doc/go1.4#gogenerate)-ում՝ «կոմպիլյացիայից առաջ կոդ գեներացնող գործիքների գործարկումն ավտոմատացնելու համար»։

Մինչև դրա օգտագործման տարբեր եղանակները բացատրելը, դիտարկենք `go:generate`-ի օգտագործման մի պարզ այլընտրանք, որը նույնպես ներդրված է Go գործիքում։

## `-ldflags`-ի օգտագործումը

Ենթադրենք գրել եք ծրագիր և ուզում եք որ այն արտածի իր տարբերակի համարը։ Ինչպե՞ս կարող եք տարբերակի համարը կարել կատարվող մոդուլի մեջ։ Ճանապարհներից մեկը կարող է լինել պարզապես հիշելը, որ տարբերկի համարը գրված է ծրագրի կոդի X-րդ տողում և պարբերաբար  այդ տողը թարմացնել ձեռքով, բայց դա [այնքան էլ ավտոմատացված չէ](https://blog.carlmjohnson.net/post/2016-06-17-automate-it/)։

Բարեբախտաբար, Go-ի գործիքակազմում կոնկրետ տեքստային արժեքները փոխելու հնարավորություն կա։ [`link` գործիքն](https://pkg.go.dev/cmd/link) ունի հրամանային տողի հետևյալ բանալին. `-X importpath.name=value`, որը «`importpath` փաթեթի `name` անունով տողային փոփոխականի արժեքը դարձնում է ՝value`»։ Իհարկե, Go-ով ծրագրավորելիս հիմնականում դուք `link` գործիքը ուղղակիորեն չեք օգտագործում։ Դրա փոխարեն աշխատեցնում եք `go run`, `go build` կամ `go install` հրամանները։ Բարեբախտաբար, բոլոր այդ հրամանները կարող են `-ldflag` բանալիով բանալի փոխանցել իրենց կողմից անուղակիորեն օգտագործվող Go-ի `link` գործիքին։ (Այո, բանալին օգտագործվում է բանալի փոխանցելու համար։)

Ահա մի կարճ օրինակ։ `$GOPATH/src/project/main.go` ֆայլում գրված է հետևյալը.

```Go
package main

import (
	"fmt"
)

var VersionString = "unset"

func main() {
	fmt.Println("Version:", VersionString)
}
```

`VersionString`-ի արժեքը փոխելու համար կորող ենք օգտագործել `-ldflags`-ը.

```bash
$ go run main.go
Version: unset

$ go run -ldflags '-X main.VersionString=1.0' main.go
Version: 1.0
```

Ավելին, որպես տարբերակի ավտոմատ համար, կարող ենք օգտագործել Git-ի commit-ի հեշը.

```bash
$ git rev-parse HEAD
db5c7db9fe3b632407e9f0da5f7982180c438929

$ go run -ldflags "-X main.VersionString=`git rev-parse HEAD`" main.go
Version: db5c7db9fe3b632407e9f0da5f7982180c438929
```

Նույն կերպ կարող եք օգտագործել Յունիքսի `date` հրամանը՝ ֆայլին ժամն ու ամսաթիվը փոխանցելու համար։ Մի շփոթեցնող բանն այն է, որ քանի որ բանալին փոխանցում ենք մի այլ բանալու համար, ապա եթե պետք է բացատներ պարունակող արգումենտ փոխանցվի՝ պետք է չակերտների մեջ չակերտներ օգտագործենք.

```bash
$ go run -ldflags "-X 'main.VersionString=1.0 (beta)'" main.go
Version: 1.0 (beta)
$ go run -ldflags "-X 'main.VersionString=`date`'" main.go
Version: Sun Nov 27 16:42:10 EST 2016
```

Ինչքան շատ `link`-ի բանալիներ ուզենանք փոխանցել, այնքան ավելի բարդ կդառնա Go-ի `build` հրամաները։ Հետևաբար այդ հրամանները պետք է ինչ-որ տեղ պահվեն՝ ծրագրի կառուցման ընթացքը ստանդարտացնելու համար, օրինակ, պարզագույն Bash ֆայլում կամ [Makefile](https://en.wikipedia.org/wiki/Make_(software)#Makefile)-ում։


## `go:generate`-ի հիմունքները

Makefile-երը և Bash սկրիպտները ժամանակի փորձություններն անցած ծրագրավորման գործիքներ են, բայց եթե դուք Գո ծրագրավորող եք, ապա դուք Գոի փորձագետ եք և հեչ էլ պարտադիր չէ, որ make-ի և Bash-ի փորձառություն ունենաք։ Լավ չէ՞ր լինի, եթե կարողանայինք ծրագրի կառուցման պրոցեսն ավտոմատացնել միայն Գոի գործիքների օգտագործմամբ։ Սա էր այն [խնդիրը, որի լուծման համար ստեղծվեց `go:generate`-ը](https://docs.google.com/document/d/1V03LUfjSADDooDMhe-_K59EgpTEm3V8uvQRuNMAEnjg/)։

Հետևյալը `go:generate`-ի համառոտ նկարագրությունն է։ Բանալիների և պարամետրերի լիարժեք սահմանմանը ծանոթանալու համար կարդացեք համապատասխան [փաստաթղթերը](https://pkg.go.dev/cmd/go#hdr-Generate_Go_files_by_processing_source)։ Երբ աշխատեցնում եք `go generate` հրամանը, ապա Go գործիքը դիտարկում է տվյալ փաթեթի բոլոր ֆայլերը և փնտրում է `//go:generate command arguments` տեսքի «մոգական մեկնաբանություններ» պարունակող տողերը։ Այս հրամանը ոչինչ չպետք է անի Գոի և կոդի գեներացիայի հետ կապված։

Օրինակ.

```C++
package project

//go:generate echo Hello, Go Generate!

func Add(x, y int) int {
	return x + y
}
```

```bash
$ go generate
Hello, Go Generate!
```

Նկատենք՝ չնայաց որ `!`-ը Bash-ի հատուկ նիշ է, Գոն պարզապես անտեսում է այն և նորմալ կատարում է հրամանը։

Եվս մի քանի գործիքներ կան, որոնք նախագծված են `go:generate` հրահանգի հետ աշխատելու համար. դրանցից են [stringer](https://pkg.go.dev/golang.org/x/tools/cmd/stringer)-ը, [jsonenums](https://github.com/campoy/jsonenums)-ը և [schematyper](https://github.com/idubinskiy/schematyper)-ը։


## Գո ծրագրի աշխատեցնելը `go:generate`-ով

Ինչպես նշվեց, `go:generate`-ի միջոցով աշխատեցվելիք հրամանը որևէ կոնկրետ պահանջների չպետք է բավարարի։ Սա կարող է բերել այնպիսի վիճակի, որ ինչ-որ Գո կոդ մշակելու համար կպահանջվի նախ աշխատեցնել `go generate` հրամանը, իսկ `go generate`-ի աշխատեցնելը պահանջում է որոշ կողմնակի կախվածություններ, որոնք տվյալ մեքենայի վրա տեղադրված չեն։ Մենք հավանաբար կարող ենք վստահ լինել, որ կոմպյուտերների վրա տեղադրված են `git`-ը կամ `date`-ը, բայց այլ գործիքներ բացակայում են, մասնավորապես երբ դիտարկվող գործիքը մեր գրածն է։ Սրանից խուսափելու համար Գոի թիմը խորհուրդ է տալիս ձեռագիր կոդի ֆայլերի հետ միասին տրամադրել նաև գեներացված կոդի ֆայլերը, բայց սա կարող է որոշ դեպքերում անընդունելի կամ ոչ պրակտիկ լինել։

Կախվածությունների այս խնդրի լուծումներից մեկը `go generate`-ի մեջ մեր ստեղծած Գո ծրագիրն աշխատեցնելու համար `go run`-ը օգտագործելն է։ Քանի որ գիտենք, որ Գո ծրագիր կառուցող ցանկացած քոմփյութերում պետք է Գո տեղադրված լինի, կարող ենք չանհանգստանալ նախապես կառուցված կախվածությունների համար։

Ահա կոնկրետ օրինակ։ Ենթադրենք ես ուզում եմ, որ իմ կատարվող մոդուլն արտածի Գո պրոյեկտի այն մասնակիցների ցուցակը, որոնց անունը պարունակում է Carl բառը։ Այդ բինար մոդուլի կառուցումն ավտոմատացնելու համար կարող եմ `go generate` ունենալ, որը GitHub-ից ներբեռնում է մասնակիցների ցուցակը և այն գրում է պրոյեկտի կասմի մեջ մտնող Գո ֆայլում։ Ահա, թե դա ինչ տեսք կարող է ունենալ։

```
$GOPATH
`-- src
    `-- project
        |-- cmd
        |   `-- carls
        |       `-- main.go
        |-- contributors.go
        |-- gen.go
        `-- project.go
```

`project/cmd/carls/main.go` ֆայլ առանձնացված է պարզապես օրինակն ավելի հստակ դարձնելու համար։ Դրա օգտագործած ամբոջ կոդը ներմուծվում է (imported).

```Go
package main

import (
	"project"
)

func main() {
	project.PrintContributors()
}
```

`//go:generate`-ը, ինչպես նաև այս պրոյեկտի ակտիվ կոդը, գրված է `project/project.go`-ում.

```Go
package project

import "fmt"

//go:generate go run gen.go

func PrintContributors() {
	for _, contributor := range Contributors {
		fmt.Println(contributor)
	}
}
```

Երբ կոդի գեներացիա եք օգտագործում, դուք վստահորեն ուզում եք առանձնացված պահել գեներացվող ու ձեռագիր կոդերը, որպեսզի կոդի փոփոխությունների պատմությունը հստակ լինի մյուսների համար։

`project/gen.go`-ն գործարկվում է `go generate`-ով՝ ներբեռնելով մասնակիցների անունները և դրանք գրելով Գո ֆայլի մեջ։ Քանի որ տրված պանակի բոլոր Գո ֆայլերը պետք է պատկանեն նույն փաթեթին, մենք անհրաժեշտություն կունենանք այդ գործարկվող ֆայլում ավելացնել [կառուցման գործողությունը սահմանափակող](https://pkg.go.dev/go/build#hdr-Build_Constraints) մոգական մեկնաբանություն, որպեսզի բացառենք դրա՝ փաթեթին պատկանելը։

```Go
// The following directive is necessary to make the package coherent:

// +build ignore

// This program generates contributors.go. It can be invoked by running
// go generate
package main

import (
	"bufio"
	"log"
	"net/http"
	"os"
	"strings"
	"text/template"
	"time"
)

func main() {
	const url = "https://github.com/golang/go/raw/master/CONTRIBUTORS"

	rsp, err := http.Get(url)
	die(err)
	defer rsp.Body.Close()

	sc := bufio.NewScanner(rsp.Body)
	carls := []string{}

	for sc.Scan() {
		if strings.Contains(sc.Text(), "Carl") {
			carls = append(carls, sc.Text())
		}
	}

	die(sc.Err())

	f, err := os.Create("contributors.go")
	die(err)
	defer f.Close()

	packageTemplate.Execute(f, struct {
		Timestamp time.Time
		URL       string
		Carls     []string
	}{
		Timestamp: time.Now(),
		URL:       url,
		Carls:     carls,
	})
}

func die(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

var packageTemplate = template.Must(template.New("").Parse(`// Code generated by go generate; DO NOT EDIT.
// This file was generated by robots at
// {{ .Timestamp }}
// using data from
// {{ .URL }}
package project

var Contributors = []string{
{{- range .Carls }}
	{{ printf "%q" . }},
{{- end }}
}
`))
```

`gen.go`-ի հատկություններից մեկն էլ այն է, որ դրանում օգտագործված է ժամանակի պահը (timestamp), որով հստակեցվում է, թե երբ է կոդն ավտոմատ գեներացվել։ Տեքստի կաղապարի օգտագործումը թույլ է տալիս հեշտությամբ ընդլայնել ֆայլը, երբ հետագայում դրա անհրաժեշտությունը կառաջանա։

Վերջապես `project/contributors.go`-ը ավտոմատ գեներացված ֆայլն է.

```Go
// Code generated by go generate; DO NOT EDIT.
// This file was generated by robots at
// 2016-11-27 17:59:50.90476568 -0500 EST
// using data from
// https://github.com/golang/go/raw/master/CONTRIBUTORS
package project

var Contributors = []string{
	"Carl Chatfield <carlchatfield@gmail.com>",
	"Carl Jackson <carl@stripe.com>",
	"Carl Johnson <me@carlmjohnson.net>",
	"Carl Mastrangelo <notcarl@google.com>",
	"Carl Shapiro <cshapiro@google.com> <cshapiro@golang.org>",
	"Carlos Castillo <cookieo9@gmail.com>",
	"Carlos Cirello <uldericofilho@gmail.com>",
	"Carlos Eduardo Seo <cseo@linux.vnet.ibm.com>",
	"Dustin Carlino <dcarlino@google.com>",
}
```
Գո 1.9-ից սկսած ավտոմատ գեներացված ֆայլերը նշելու համար սահմանված է մեկնաբանությունների [ստանդարտ ձևաչափ](https://github.com/golang/go/issues/13560): Գեներացված ֆայլը պետք է ունենա `^// Code generated .* DO NOT EDIT.$` կանոնավոր արտահայտությանը բավարարող մեկնաբանություն։ Որպեսզի ձեր գեներացնող կոդը չշփոթվի գեներացված կոդի հետ, համոզվեք որ մոգական մեկնաբանությունը տողի սկզբում չէ։

Հիմա կարող ենք ամեն ինչ հավաքել իրար վրա ու գործարկել.

```bash
$ go generate

$ go run cmd/carls/main.go
Carl Chatfield <carlchatfield@gmail.com>
Carl Jackson <carl@stripe.com>
Carl Johnson <me@carlmjohnson.net>
Carl Mastrangelo <notcarl@google.com>
Carl Shapiro <cshapiro@google.com> <cshapiro@golang.org>
Carlos Castillo <cookieo9@gmail.com>
Carlos Cirello <uldericofilho@gmail.com>
Carlos Eduardo Seo <cseo@linux.vnet.ibm.com>
Dustin Carlino <dcarlino@google.com>
```

Հույս ունեմ՝ կարողացա բացատրել `go:generate`-ի որոշ հիմունքները։ Այլ օրինակների համար կարդացեք [Gopher Academy-ի այս հոդվածը](https://blog.gopheracademy.com/advent-2015/reducing-boilerplate-with-go-generate/) կամ [Էլի Բենդերսկիի ծավալուն բացատրությունները](https://eli.thegreenplace.net/2021/a-comprehensive-guide-to-go-generate/)։ Հաջողակ Go-ing!
