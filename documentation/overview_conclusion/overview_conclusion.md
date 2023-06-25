# M242-Project Phineas Berdelis

## Programmübersicht
### Tasks
- DefaultTask           -> handles the main tasks of the program
- Taster_Treiber_Task   -> Handles the button inputs
- StartDisplayTask      -> Handles displaying the digits on the display

### Methods
- void beep(int time)   -> Performs a beep with the length of the passed miliseconds
- void countDownTimer() -> Coutns down the timer by 1 if hes running and activates the buzzer if the timer is on 0
- void countUpStopuhr() -> Counts up the stopuhr by 1 if its running
- void stopuhrRunning() -> Basically just refactored code since i didn't wanna put everything in the default task
- void switchMode()     -> Checks for long pressing of the TASTER_3 so it can perform a switch of modes


## Fazit
### Was wurde erreicht?
* state_machine diagramm
* Funktionalität timer und stopuhr

Im grossen und ganzen wurden alle Schlüsselfunktionen des Timers und der Stopuhr erreicht.
Beide funktionieren auch parallel, wobei man in jedem Zustand den modus wechseln kann.
Auch der Buzzer verhält sich korrekt nach den vorgaben.
### Wo waren die Probleme?
Ich habe zuerst den Timer und die Stopuhr einzeln programmiert von der Logik her.
Ich wollte dann mit Tasks arbeiten aber bei mir funktionierte es nicht was mein ganzes Programm immer zu Error's brachte.
Als ich dann merkte das mir nicht mehr viel Zeit bleibt, musste ich alles mit einer eigenen Logik implementieren was eine
nicht so schöne Lösung zur Folge hatte.
### Was könnte besser gelöst werden?
Ich hätte definitiv mit Tasks arbeiten könnten was die ganze paralleliesierung viel schöner gemacht hätte.
Ich hätte noch mehr code in verschiedene Funktionen refaktorisieren können um eine bessere Code struktur zu erreichen.