************************************************************
* Panta Rei 0.1r117                                        *
* author: Cosimo Sacco <cosimosacco@gmail.com>             *
************************************************************

=========
Panta Rei
=========
Panta Rei è un simulatore di scheduling real-time.
La versione corrente permette un utilizzo interattivo,
mediante CLI, e batch, attraverso script. È possibile 
simulare la schedulazione di un set di task periodici
secondo gli algoritmi Rate Monotonic, Deadline Monotonic ed
Earliest Deadline First, con preemption attiva o disattiva.
Panta Rei permette la visualizzazione grafica della
schedulazione prodotta e consente di definire log di
simulazione e log d' errore.

=========
Requisiti
=========
Sistema: sviluppato e testato su sistemi GNU/Linux
Dipendenze: gnuplot

========
Utilizzo
========
È possibile visualizzare le opzioni di programma avviando
l' applicazione con l' opzione -h.
Per una descrizione del linguaggio utilizzato da
Panta Rei, digitare, dal prompt dell' applicazione, il
comando "syntax".

=======
Licenza
=======
Panta Rei - Real Time Scheduling Simulator
Copyright (C) 2011 Cosimo Sacco
    
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
                   
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
