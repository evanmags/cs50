from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""
    # use set because no duplicate elements
    # turn back into list because that is what the spec calls for
    return list(set(line for line in a.split("\n") if line in b.split("\n")))


def sentences(a, b):
    """Return sentences in both a and b"""
    return list(set(line for line in sent_tokenize(a) if line in sent_tokenize(b)))


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    print(get_substrings(a, n))
    print(get_substrings(b, n))
    return list(set(string for string in get_substrings(a, n) if string in get_substrings(b, n)))

def get_substrings(string, n):
    results = []
    i = 0
    while i < len(string) - n + 1:
        results.append(string[i:(i+n)])
        i += 1
    return results