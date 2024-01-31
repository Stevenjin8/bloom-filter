# Filters

Comparison of Tries, Bloom Filters, and Cuckoo Filters for words.
Written on FreeBSD but will probably compile on OSX.

## Running

You will need `nltk` and `matplotlib` installed.

Download necessary files using `make setup`.
Compile with `make`.
Run experiments with `make run`.
Create figures with `make fig`.
These will appear under `fig/`.

## Resources

* `https://stackoverflow.com/questions/12468179/unicodedecodeerror-utf8-codec-cant-decode-byte-0x9c`
* `https://en.wikipedia.org/wiki/Bloom_filter`
* `https://www.cs.cmu.edu/~dga/papers/cuckoo-conext2014.pdf` (avoid Wikipedia for cuckoo filters)
* `https://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names`
* `http://www.isthe.com/chongo/tech/comp/fnv/index.html#google_vignette`
