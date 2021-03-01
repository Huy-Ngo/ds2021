import re
from subprocess import run

from mrjob.job import MRJob


class LongPath(MRJob):

    def mapper(self, _, line):
        yield (None, (len(line), line))

    def reducer(self, _, lengthpath):
        yield max(lengthpath)


if __name__ == '__main__':
     # Run: find / | py long_path.py
     LongPath.run()
