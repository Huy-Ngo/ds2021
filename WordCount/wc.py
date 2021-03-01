from mrjob.job import MRJob
import re

word_regex = re.compile(r"[\w']+")


class WordCount(MRJob):

    def mapper(self, _, line):
        for word in word_regex.findall(line):
            yield (word.lower(), 1)

    def reducer(self, word, counts):
        yield (word, sum(counts))


if __name__ == '__main__':
     WordCount.run()
