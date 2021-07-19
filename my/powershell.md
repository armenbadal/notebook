# Խառը գրառումներ PowerShell-ի հրամանների մասին

## Երկու JSON-ների միավորումը

Ինձ պետք էր կարդալ ծրագրի կարգավորումների երկու JSON ֆայլերը: Դրանցից առաջինը պարունակում է հիմնական կարգավորումները, իսկ երկրորդը՝ օգտագործողի կարգավորումները։ Ես ուզում եմ կարդալ դրանք, միավորել, ապա նոր կարգավորումները կիրառել ծրագրում։ Օրինակ, թող որ հիմնական ֆայլում գրված է.

```json
{
    "mode": "production",
    "url": "https://github.com/armenbadal",

    "windows": {
        "place": "C:\\Program Files\\Analyzer"
    },

    "macos": {
        "place": "/Applications/Analyzer"
    }
}
```

Իսկ օգտագործողի ֆայլում գրված է.

```json
{
    "mode": "development",
    "local-data": "$ProjectDir\data"
}
```

Եվ այս երկու ֆայլերը կարդալուց ու միավորելուց հետո ուզում եմ ստանալ հետևյալ JSON օբյեկտները։ Windows-ի համար.

```json
{
    "mode": "development",
    "url": "https://github.com/armenbadal",
    "local-data": "$ProjectDir\data",
    "place": "C:\\Program Files\\Analyzer"
}
```

Իսկ macOS-ի համար.

```json
{
    "mode": "development",
    "url": "https://github.com/armenbadal",
    "local-data": "$ProjectDir\data",
    "place": "/Applications/Analyzer"
}
```


## Հրամանների պատմությունը

Հատկապես Լինուքս/Յունիքս աշխարհից եկած մարդկանց համար շատ կարևոր է `history` հրամանը, որը հնարավորություն է տալիս թվարկել ու նորից աշխատեցնել _shell_-ի հրամանները։ Այդ նույն նպատակի համար PowerShell-ը առաջարկում է `Get-History` հրամանը։ Սակայն վերջինս «հիշում» է միայն տվյալ սեսիայի (session) հրամանները։

Հրամանների պատմությունից որևէ հրաման կատարելու համար պետք է օգտագործել `Invoke-History` հրամանը՝ արգումենտում տալով `Get-History` հրամանի արտածած ցուցակի հրամանի ինդեքսը։

Հրամանների պատմությունը մաքրվում է `Clear-History` հրամանով։

## Ֆայլեր

Ֆայլ ստեղծելու և դրա մեջ ինչ-որ տեքստ գրելու համար օգտագործում եմ `Set-Content` հրամանը։ Օրինակ, ուզում եմ ստեղծել `parmeters.json` ֆայլը հետևյալ պարունակությամբ.

```json
{
    "host": "https://example.com",
    "count": 125,
    "path": "C:\\Projects\\example.txt"
}
```

Գրում եմ.

```PowerShell
Set-Content -Path 'parameters.json' -Value @"
{
    "host": "https://example.com",
    "count": 125,
    "path": "C:\\Projects\\example.txt"
}
"@
```

Ֆայլի պարունակությունը կարդալու համար օգտագործում եմ `Set-Content`-ի հակառակորդ `Get-Content` հրամանը։ Օրինակ, ինձ պետք է կարդալ `parameters.json` ֆայլի պարունակությունը ու դրանից կառուցել PowerShell-ի օբյեկտ։ Այսպես.

```PowerShell
$Parameters = Get-Content -Path 'paramewters.json' | ConvertFrom-Json
```

Օգտագործված `ConvertFrom-Json` հրամանն է հենց, որ JSON-ի տեքստային ներկայացումից կառուցում է PowerShell օբյեկտը։ Համոզվելու համար կարող եմ առանձին-առանձին արտածել դրա դաշտերը.

```PowerShell
Write-Host $Parameters.host
Write-Host $Parameters.count
Write-Host $Parameters.path
```

Կա նաև `ConvertFrom-Json` հրամանի հակառակը՝ `ConvertTo-Json`-ը, որը, բնականաբար, PowerShell օբյեկտից կառուցում է դրա JSON ներկայացումը։ Օրինակ, ասենք թե ուզում եմ կառուցել ամսաթվի օբյեկտը և դրանից ստանալ JSON տեքստը։ Տարբերակներից մեկը հետևյալն է.

```PowerShell
$Today = '' | Select-Object year, month, day
$Today.year = 2021
$Today.month = 'Մայիս'
$Today.day = 2
Write-Host (ConvertTo-Json -InputObject $Today)
```

Կատարման արդյունքում կարտածվի հետևյալը.

```json
{
    "year":  2021,
    "month":  "Մայիս",
    "day":  2
}
```

Ֆայլի մեջ գրելու համար երբեմն օգտագործում եմ նաև `Out-File` հրամանը։ Օրինակ, նախորդ քայլում սարքած JSON-ը `Out-File`-ի օգնությամն ֆայլում գրառելու համար կարելի է գրել.

```PowerShell
ConvertTo-Json -InputObject $Today | Out-File -FilePath 'today.json' -Encoding UTF8
```

Այստեղ `-Encoding` պարամետրով պահանջել եմ, որ ստեղծվող ֆայլն ունենա `UTF-8` կոդավորում։


## Ուղիներ

_Ուղիների_ (path) հետ աշխատելիս ես առավել հաճախ օգտագործում եմ հետևյալ `Join-Path`, `Split-Path` և `Test-Path` հրամանները։ 

`Join-Path`-ը նոր ուղի է կառուցում՝ տրվածին կցելով մի նոր բաղադրիչ։ Օրինակ, եթե ուզում եմ ստանալ `C:\ProgramData\MyApp\settings.ini` ուղին, ապա պետք է գրեմ.

```PowerShell
$SettingsPath = Join-Path -Path $Env:ProgramData -ChildPath 'MyApp\settings.ini'
```

`Test-Path`-ը ստուգում է տրված ուղու գոյություն ունենալը։ Օրինակ, եթե պետք է ստուգեմ, թե արդյոք գոյություն ունի՞ `$SettingsFile`-ը, ապա կգրեմ.

```PowerShell
If( Test-Path -Path $SettingsPath -PathType Leaf ) {
    Write-Host "$SettingsPath ֆայլն առկա է։"
}
Else {
    Write-Host "$SettingsPath ֆայլը բացակայում է։"
}
```

Այս օրինակում `-PathType` պարամետրով նշել եմ, որ `$SettingsPath` փոփոխականում գրված ուղին ինձ հետաքրքրում է որպես ֆայլի ուղի (`Leaf` — տերև, այն իմաստով, որ ֆայլերի ու պանակների ծառում ֆայլը _տերև_ է)։ Եթե, օրինակ, պետք է ճշտել հենց  `C:\ProgramData` պանակի գոյությունը, ապա `-PathType` պարամետրին տալիս եմ `Container` արժեքը։ Այսպես.

```PowerShell
If( Test-Path -Path $Env:ProgramData -PathType Container ) {
    Write-Host ('{0} պանակը գոյություն ունի։' -f $Env:ProgramData)
}
```

`Split-Path`-ը `Join-Path`-ի «հակադարձն» է։ Այն տրոհում է տրված ուղին և վերադարձնում է դրա աբաղադրիչները։ Օրինակ, եթե տրված է `$SettingsPath` ուղին, իսկ ես պետք է դրանով որոշվող ֆայլը պատճենեմ `old-settings.ini` անունով, ապա կարող եմ գրել.

```PowerShell
# առանձնացնել ֆայլի անունը
$FileName = Split-Path -Path $SettingsPath -Leaf
# առանձնացնել ֆայլի պանակի ուղին
$SettingsDir = Split-Path -Path $SettingsPath -Parent
# կառուցել նոր ուղի
$OldSettingsPath = Join-Path -Path $SettingsDir -ChildPath "old-$FileName"
# պատճենել ֆայլը
Copy-Item -Path $SettingsPath -Destination $OldSettingsPath
```

Օգտագործված `Copy-Path` հրամանը, տվյալ դեպքում, իր `-Path` պարամետրով տրված ֆայլը պատճենում է `-Destination` պարամետրով տրված անունով։ Եթե ինձ պատճենելու փոխարեն պետք լիեր տեղափոխել (անվանափոխել), ապա կօգտագործեի `Move-Path` հրամանը՝ նույն պարամետրերով։

Ֆայլը կամ պանակը ջնջելու (հեռացնելու) համար օգտագործում եմ `Remove-Item` հրամանը։ Օրինակ, եթե պիտի ջնջեմ նախորդ քայլում ստեղծված `old-settings.ini` ֆայլը, ապա գրում եմ.

```PowerShell
Remove-Item -Path $OldSettingsPath
```

Երբ `Remove-Item` հրամանի `-Path` պարամետրով տրված ֆայլը գոյություն չունի, գեներացվում է սխալ։ Այդ դեպքում կարելի է նախապես ստուգել ֆայլի առկայությունը, ապա ջնջել այն.

```PowerShell
If( Test-Path -Path $OldSettingsPath -PathType Leaf ) {
    Remove-Item -Path $oldSettingsPath
}
```

Ես սովորաբար ալարում եմ գրել այս երեք տողն ու դրա փոխարեն օգտագործում եմ `-ErrorAction` պարամետրը։ Սրանով `Remove-Item`--ին ասում եմ, թե ինչ անի սխալի դեպքում. իսկ ավելի կոնկրետ՝ «սուսուփուս շարունակել».

```PowerShell
Remove-Item -Path $OldSettingsPath -ErrorAction SilentlyContinue
```

Պանակի ենթապանակներն ու դրանցում գտնվող ֆայլերն էլ մի հրամանով ջնջելու համար պետք է օգտագործել `-Recurse` պարամետրը.

```PowerShell
Remove-Item -Path $SettingsDir -Recurse -ErrorAction SilentlyContinue
```

## Հաստատուններ

Մի անգամ ինձ պետք էր սահմանել մի օբյեկտ՝ `$ProjectPath` անունով, և արգելել դրա արժեքը փոխել։ Պարզվեց, որ այդ արդյունքը կարելի է ստանալ `New-Variable` հրամանով՝ լրացնելով այն `-Option` պարամետրի `ReadOnly` արժեքով։ Այսպես.

```PowerShell
New-Variable -Name Settings -Option ReadOnly `
             -Value (Split-Path -Path $PSScriptRoot -Parent)
```

Այստեղ `$PSScriptRoot` փոփոխականը PowerShell-ի ավտոմատ փոփոխականներից է, որը միշտ ցույց է տալիս այն պանակը, որտեղից աշխատեցվել է սկրիպտը։


## Պանակի ֆայլերի թվարկում

Մի անգամ էլ ինձ պետք էր ստանալ տրված պանակի բոլոր ֆայլերի անունների ցուցակը և կառուցել URL-ների ցուցակ `url=https://127.0.0.1:1024/<filename>` ֆորմատով։ Գրեցի հետևյալը.

```PowerShell
Get-ChildItem -Path $ProjectDir -Name -File | `
    ForEach-Object { 'url=https://127.0.0.1:2024/{0}' -f $_ } | `
    Out-File -FilePath 'all-files.txt' -Encoding ascii
```

Այստեղ `Get-ChildItem` հրամանի `-Name` պարամետրով ասում եմ, որ ես հետաքրքրված եմ միայն ֆայլերի անուններով, իսկ `-File` պարամետրով էլ ասում եմ, որ հետաքրքրված եմ միայն ֆայլերով (բայց ոչ պանակներով)։

`ForEach-Object` հրամանը իտերացիա է կատարում `Get-ChildItem`-ի կառուցած օբյեկտների ցուցակով և ամեն մի օբյեկտի համար կիրառում է տրված _բլոկը_։ Տվյալ դեպքում՝ տեքստի ֆորմատավորման միջոցով ամեն մի ֆայլի անունի համար գեներացնում է URL-ի տող։ `ForEach-Object`-ի բլոկում (ինչպես նաև նմանատիպ այլ բլոկներում) `$_` գրառմամբ նշվում է իտերատորը (արժեքը)։


## Ժամանակի միջակայք

Ժամանակի միջակայքը չափում եմ `New-TimeSpan` հրամանով։ Այն `-Start` և `-End` պարամետրերով ստանում է `DateTime` տիպի օբյեկտներ և վերադարձնում է օբյեկտ, որն արտացոլում է ժամանակի երկու պահերի տարբերությունը։ Օրինակ.

```PowerShell
$Begin = Get-Date
Start-Sleep -Seconds 5
$Interval = New-TimeSpan -Start $Begin -End (Get-Date)
Write-Host $Interval
```

Արտածվում է `00:00:05.0017708` արժեքը, որը ցույց է տալիս, թե ինչքան ժամանակ է անցել `$Begin`-ը արժեքավորելուց մինչև `New-TimeSpan`-ի կատարվելը։ `TimeSpan` օբյեկտի բոլոր հատկությունները տեսնելու համար կարելի է օգտագործել `Select-Object` հրամանը։

```PowerShell
$Interval | Select-Object -Property *
```


## Ֆայլի հեշ կոդը

Հաճախ ինձ պետք է լինում հաշվել ներբեռնված ֆայլի հեշ կոդը՝ ֆայլի ամբողջականության մեջ համոզվելու համար։ Սովորաբար օգտագործում ենք `SHA-512` ալգորիթմով հաշված հեշը։ `Get-FileHash` հրամանը հենց այդ նպատակի համար է։ 

```PowerShell
$Hash = (Get-FileHash -Path 'my-installer.exe' -Algorithm SHA256).Hash
```


## Սցենարի (script) պարամետրերը

`Param` կառուցվածքով սցենարների ֆայլերում սահմանում եմ հրամանային տողի պարամետրերը։ Օրինակ, կա մի սցենար, որը նախատեսված է ամբողջ պրոյեկտը կառուցելու (build) համար։ Այդ սցենարին պետք է տալ Visual Studio-ի solution-ի ֆայլի անունը, կոնֆիգուրացիան և պլատֆորմը։ `Solution`, `Configuration` և `Platform` պարամետրերը սահմանել եմ հետևյալ կերպ.

```PowerShell
Param(
    [ValidateSet('our-app.sln', 'out-app-with-tests.sln')]
    [String]$Solution      = 'our-app-with-tests.sln',

    [ValidateSet('Debug', 'Release')]
    [String]$Configuration = 'Release',

    [ValidateSet('x64', 'x32')]
    [String]$Platform      = 'x64'
)
```

Այստեղ պարամետրին նախորդող `ValidateSet` ատրիբուտով թվարկված են տվյալ պարամետրի թույլատրելի արժեքները։ `[String]` ատրիբուտով սահմանված է պարամետրի տիպը։ Տիպը կարող է լինել նաև, օրինակ, `[Int]`, `[Uri]`, `[Boolean]` և այլն։ Օգտակար տիպ է `[Switch]`-ը. այս տիպի պարամետրերը եթե տրված է հրամանային տողում, ապա `$true` է, իսկ եթե բացակայում է, ապա դրա արժեքը `$false` է։ Պարամետրի հայտարարության մեջ դրան վերագրված արժեքով որոշվում է _լռելության_ (default) արժեքը, որն օգտագործվում է այն դեպքում, եթե հրամանային տողից այլ արժեք նշված չէ։ 


## Ֆունկցիա

PowerShell սցենարներում ֆունկցիաները սահմանվում են `Function` բառով, որին հետևում են ֆունկցիայի անունը և մարմինը։ Թեև PowerShell-ը թույլ է տալիս ֆունկցիայի պարամետրերը սահմանել անունից հետո՝ `()` փակագծերում, ինձ մոտ սովորություն է դարձել դրանք սահմանել մարմնի ամենասկզբում՝ `Param` կառուցվածքով։ Ֆունկցիայի պարամետրերի սահմանումը նույն իմաստն ու տեսքն ունի, ինչ որ սցենարներինը։

Պետք է ուշադիր լինել ֆունկցիայի վերադարձվող արժեքի հետ աշխատելիս։ Բանն այն է, որ `Return` հրամանը ոչ թե վերադարձնում է միայն իր արգումենտում տրված արժեքը, այլև այն ամենը, ինչը մինչև `Return`-ի կատարվել հավաքվել է այսպես կոչված _վերադարձվող տվյալների հոսքի մեջ_ (return stream): Օրինակ, թվում է տրամաբանական կլիներ, որ հետևյալ ֆունկցիան վերադարձներ `a text` արժեքը.

```PowerShell
function f
{
    write-output 'I'
    write-output 'am'
    return 'a text'
}
```

Բայց `$e = f` կանչից հետո, երբ արտածում եմ `$e` փոփոխականի արժեքը, տեսնում եմ, որ այն `I`, `am` և `a text` տողերը պարունակող զանգված (`[Array]`) է։ (Դրանում կարելի է համոզվել `$e -is [Array]` արտահայտությունը հաշվարկելով։) Այս էֆեկտից խուսափելու համար ես աշխատում եմ ֆունկցիայի մարմնի բոլոր արտածումներն ուղարկել `Write-Host` հրամանին, կամ, եթե դրանք պետք է անտեսել, `Out-Null`-ին։


## Տողի տրոհում և միավորում

Տողը որևէ բաժանիչով տրոհելու համար կամ պետք է գիրառել դրա `Split` մեթոդը, որի արգումենտում բաժանիչն է, կամ էլ օգտագործել `-split` գործողությունը։ Օրինակ.

```PowerShell
$s0 = 'a,b,c,d,e'.Split(',')
$s1 = 'a,b,c,d,e' -split ','
```

Տրոհման արդյունքում ստացվում է տողերի զանգված։ 

Տողերի զանգվածը միվորելու համար կարելի է օգտագործել `-join` գործողությունը։ Օրինակ, հետևյալ արտահայտությունը ստորակետերը փոխարինում է գծիկներով.

```PowerShell
$s = 'a,b,c,d,e'
$s = ($s -split ',') -join '-'
```
