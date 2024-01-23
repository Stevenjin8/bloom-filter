# Filters

Comparison of Tries, Bloom Filters, and Cuckoo Filters for words.
To run, you need a dictionary of words in `words_alpha.txt` a list of unique words
in `data/hp-tokenize-unique` and a list of words in `data/hp-tokenized`.
Run `make run` for the tests.
Run `make fig` for the graphs.
You will need `matplotlib` to make plots.

Written on FreeBSD but will probably compile on OSX.

* `https://en.wikipedia.org/wiki/Bloom_filter`
* `https://www.cs.cmu.edu/~dga/papers/cuckoo-conext2014.pdf` (avoid wikipedia for cuckoo filters)
* `https://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names`
* `http://www.isthe.com/chongo/tech/comp/fnv/index.html#google_vignette`