# Documentație Proiect SO
# 1. Cuvânt înainte
## 1.1 Ce este acest proiect
Acest proiect este unul personal, dorind prin acesta să învăț modul prin care funcționează sistemele de operare. Nu doresc să ating standardele moderne (infinit de complexe) ale unui sistem de operare actual.

Proiectul se va baza pe o arhitectură mai veche, folosind BIOS-ul și nu EFI/UEFI.
## 1.2 De ce un SO?
Deoarece este distractiv. Scrierea de la zero al unui sistem de operare implică confruntarea unor probleme de programare low-level noi și interesante. În decursul realizării acestui proiect m-am lovit de concepte total necunoscute, care m-au făcut să înțeleg mult mai bine ce se întâmplă cu adevărat în spatele monitorului.

# 2. Resurse necesare
## 2.1 Cunoștințe
Din start, cunoașterea limbajului de asamblare este total necesară, împreună cu detalii despre modul de funcționare al unui procesor. De asemenea, familiaritate cu limbajul C.
## 2.2 Programe
Pentru început, sunt necesare utilitare pentru asamblare/compilare/editare de legături. În cadrul proiectului am folosit asamblorul NASM, compilatorul GCC si editorul de legături GNU, LD.
De asemenea, am folosit QEMU, un emulator care permite încărcarea unui sistem de operare și rularea lui, oferind o platformă identică cu un calculator fizic. Sistemul de operare este desigur rulabil și pe un calculator real, dar acesta trebuie să utilizeze BIOS-ul, căci EFI/UEFI nu este momentan inclus in cod.

# 3. Procesul de boot
La pornirea calculatorului, primul lucru care se execută este POST-ul (Power On Self Test). Acesta rulează teste de verificare pentru diverse componente ale calculatorului. La sfârsit, controlul este dat BIOS-ului (Basic Input Output System), care va rula și el anumite teste, iar după toate acestea va căuta un mediu de stocare pe care se află un sistem de operare. BIOS-ul va lua pe rând fiecare mediu de stocare și va încărca primii 512 octeți în memorie, iar apoi va verifica ultimii doi octeți (adresele 510, 511). Dacă găsește valoarea 0x55AA la această adresă, va considera că pe acel disc se află un sistem de operare și va ceda controlul. Codul care se află în primii 512 octeți de pe disc se numește **bootloader**, iar scopul lui este să încarce în memorie adevăratul sistem de operare.
