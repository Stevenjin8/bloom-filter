default: hp-tokenized hp-tokenized-unique
hp-raw.txt: hp-1.txt hp-2.txt hp-3.txt hp-4.txt
	cat hp-1.txt hp-2.txt hp-3.txt hp-4.txt > hp-raw.txt

hp-tokenized: hp-raw.txt
	python process.py < hp-raw.txt > hp-tokenized

hp-tokenized-unique: hp-raw.txt
	python process.py 1 < hp-raw.txt > hp-tokenized-unique
