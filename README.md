# hw3
- Team names and x50
Daniel Peterson pet01704, Tseki Lhamo lhamo012

- How to compile the program
./prog #consumer filename [option] [#queue_size]
consumer is the number of consumers the program generates
options: -p: log print (creates log.txt file with producer and consumer logs),
         -b: bounded buffer (extra credit, specifies queue_size),
         -bp: both bounded buffer and log printing

- Your and your partner's individual contributions
Daniel: main, consumer, extra credit
Tseki: utils, header, producer, extra credit

- What exactly your program does
The program uses multithreading in order to tally the number of times each letter of the
alphabet occurs as the first letter of a word.
A producer adds packages to a shared queue. A consumer takes a package from the shared queue and calculates
the number of times a letter of the alphabet occurs as the first letter of a word.
Each package is a node that has a line, linenumber and a pointer to the next packages
in the queue (if any). The word count statistics are reported in a result.txt file.

- If you have attempted extra credit
We have attempted the extra credit
