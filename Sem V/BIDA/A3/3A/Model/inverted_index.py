# Imports
import os
from nltk.tokenize import word_tokenize
import nltk
from nltk.corpus import stopwords
nltk.download('punkt')
nltk.download('stopwords')


# variable to store path of dataset
path = "A3\\3A\\Dataset\\"

# Class to create object having docName and freq


class TermIndexes:
    def __init__(self, doc):
        self.doc = doc
        self.freq = 1

    def __repr__(self):
        return str(self.__dict__)

    def get(self):
        return self.doc


# Function to create inverted index
def InvertedIndex(doc, f, inv):
    # Remove punctuations
    punc = '''!()-[]{};:'"\, <>./?@#$%^&*_~'''
    for elem in doc:
        if elem in punc:
            doc = doc.replace(elem, " ")
    print(doc)

    # Tokenise
    tokens = word_tokenize(doc)
    # Remove stopwords
    tokens_wot_sw = [word for word in tokens if not word in stopwords.words()]
    print(tokens_wot_sw)

    # Creating dictionary
    for terms in tokens_wot_sw:
        if terms not in inv:
            inv[terms] = []
            inv[terms].append(TermIndexes(f))
        elif inv[terms][-1].doc != f:
            inv[terms].append(TermIndexes(f))
        else:
            inv[terms][-1].freq = inv[terms][-1].freq + 1

    return inv


# Function to open files
def fileOpen(f):
    file = open(path+f, encoding='utf8')
    file.seek(0)
    return file.read()


# Function to search files
def wordSearch(word, inv):
    print("\nWord : ", word)
    word = word.lower()
    if word in inv:
        for obj in inv[word]:
            print("\nFile: ", obj.doc)
            print("Freq: ", obj.freq)
            print(fileOpen(obj.doc))
    else:
        print("\nNo document match found!")


# Driver function
def main():
    files = os.listdir(path)
    inv = {}
    for f in files:
        print("\n", f)
        doc = fileOpen(f)
        doc = doc.lower()
        inv = dict(InvertedIndex(doc, f, inv))

    print("\nThe inverted indexes are:\n")
    for key, value in inv.items():
        print(key, " -> ", value)

    word = input("Enter the word for searching: ")
    wordSearch(word, inv)


# Calling main
main()
