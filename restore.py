import simplejson as json
import dateutil.parser
import os
class FileRestore(object):


    def __init__(self, filename, store):
        self.filename = os.path.expanduser(filename)
        self.store = store

    def run(self):
        """
        Reads the file and stores the data into new store
        """
        if os.stat(self.filename).st_size == 0:
            return 0

        fp = open(self.filename, 'r+')

        for pos,l in enumerate(fp.readlines()):
            data = json.loads(l)
            data['_ts'] = dateutil.parser.parse( data['_ts'] )
            self.store.save(data)
        fp.truncate()
        fp.close()
        return pos


