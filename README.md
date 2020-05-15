## Dekoder funkcji DCC ##

Dekoder funkcji DCC z przeznaczeniem do sterowania oświetleniem wagonów.
Część sprzętowa w przygotowaniu.

### Elementy projektu ###

**funcdec_proto3208.X**  
Prototypowe oprogramowanie dla ATMega3208 (0-series). Odebrane pakiety DCC są dodatkowo dekodowane do HEX i wysyłane na port szeregowy.  
**funcdec_mk1.X**  
Oprogramowanie dla ATTiny 1614 (1-series).  

Tryby pracy: tylko DCC.  
Tryby programowania: tryb serwisowy na torze programującym.  
Adresowanie: długie (domyślnie) i krótkie.  
Wyjścia funkcyjne: zależnie od implementacji sprzętowej.

### Wersje sprzętowe ###

**Dekoder uniwersalny.**  
6 wyjść funkcyjnych z indywidualnym ściemnianiem.

### Kompilacja oprogramowania ###

Projekt MPLABX (wersja 5.35) z kompilatorem gcc dołączonym do pakietu XC8 (wersja 2.10). Użyto pakietów definicji dostarczonych wraz z MPLABX.

### Obsługa dekodera ###


| CV   | Przeznaczenie                                    | Zakres | Wart. |
|------|--------------------------------------------------|--------|-------|
| 1    | Adres pojazdu, krótki                            |        |       |
| 7    | Wersja dekodera, tylko do odczytu                | n/d    | n/d   |
| 8    | Kod producenta, tylko do odczytu                 | n/d    | n/d   |
| 17   | Adres pojazdu, długi                             |        |       |
| 18   |                                                  |        |       |
| 29   | Konfiguracja dekodera                            |        |       |
| 33   | Mapowanie funkcji dla wyjścia A.                 |        |       |
| 34   | Mapowanie funkcji dla wyjścia A.                 |        |       |
| 45   | Deaktywacja wyjść dla kierunku ruchu: do przodu. |        |       |
| 47   | Deaktywacja wyjść dla kierunku ruchu: do tyłu.   |        |       |
| 49   | Jasność dla wyjścia A.                           | 0-63   | 63    |
