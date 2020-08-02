Text Number Formatting
===================

This Project is aimed to the transcription of word-written numbers into numeric numbers

You shall take the following considerations:

1.- The design of this code isinspired in flex/bison design. Actually, a proper choice for general scanners should be flex/bison or whatever other
	syntax/grammar analyzer. I decided to implement a small scanner just because was totally overkill to use flex/bison in such an small problem
	
2.- This scanner is designed only for the english language. In case you want to implement it in a different language, just consider implementing
	a new acceptor for this other language.
	
3.- The code is single threaded. Indeed, althought there are some places in which a multi thread solution could be interesting (such as fragmenting
	text to analyze into "sentence" and scan them in separated threads) I decided was perfectly acceptable to do it single threaded.
	
4.- The design of the scannner has been done in such a way that accepts multiple acceptors just like bison accepts multiple rules (token scanner
	will select the one with the highest match degree)
	
5.- The system only understand up to billion keywords. As a possible enhacement, we could have a collection of reserved keywords used by the scanner.


For the proper execution, take into account the following steps:

1.- Download perl interpreter (strawberry for windows for instance)

2.- Execute genPrj-Windows.pl in a command line and check that everything was ok (there is no genPrj-Linux.pl, but it is straightforward to create it)

3.- Open visual studio (default version hardcoded in genPrj.pl for windows is 2015 17, change it if you want)

4.- Open soution generated in build folder (shoud be called Verbio.sln)

5.- Build it in Debug or Release (Release_Debug is some sort of Release with symbols version)

6.- Once compilation was ok, go to project properties and add as command line argument the maximum 10th power accepted by the acceptor (for instance,
	if you want to have at max one million scanned numbers put 6, for one billion put 9, etc)

7.- The system is done in a way that it will prompt for the next sentence to be analyzed. There is no max number of words to be analyzed. Every time
	you press enter, the system will display right after the formatted text.