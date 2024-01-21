import sys
from nltk.tokenize import word_tokenize

text = sys.stdin.read()

tokenized = (x.strip().lower() for x in word_tokenize(text) if x.isalpha() and x)
print(*tokenized, sep="\n")
