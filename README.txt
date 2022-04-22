### Zařízení pro vysílání Morseovky


## Použité programy
 - Visual Studio => Psaní kódu (Chyby v kodu nejsou chyby, jenom kompiler nedokáže správně najít hlavičky)
 - Arudino IDE => Serial Monitor


## Obsah obvodu
 - Raspberry Pi Pico => Mikrokontroler
 - 2x tlačítko => Výběr mezi módy
 - 4x led dioda
 - 1x Pasiní bzučák
 - 7x Odpor 330R


## Popis zařízení
Pomocí modrého a žlutého tlačítka se dá posouvat mezi módy DEBUG, VISUAL, AUDIO. Modré tlačítko Vás posuno o jednu pozici doleva a žluté zase o jednu pozici doprava. Zvolený mód poté signalizují 3 led diody (Zelená, Modrá a Červená). Zelená určuje DEBUG mód, modrá určuje VISUAL mód a červená zase určuje AUDIO mód.
V Základu je zařízení nastaveno na AUDIO mód.

Po zadání vstupu do Serial komunikace se provede akce podle určitého módu.
Serial pracuje přes UART rychlostí 9600 baudů za sekundu.


## Popis módů

# DEBUG
Po zadání textu se vypíše morseovka do výstupního okna.

# VISUAL
Po zadání textu se vybliká morseovka na žluté led diodě.

Intervaly:
 - Tečka: 200ms
 - Čárka: 500ms
 - Mezi tečky a čárky: 500ms
 - Mezi písmeny: 1000ms

# AUDIO
Po zadání textu se vypípá morseovka na bzučáku.

Intervaly:
 - Tečka: 200ms
 - Čárka: 500ms
 - Mezi tečky a čárky: 500ms
 - Mezi písmeny: 1000ms

## Zákmit tlačítek
Zákmit je řešen pomocí PullUp módu na pinu. Poté měřím čas po dobu tlačítka a musí být větší než 150ms.