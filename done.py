#!/usr/bin/python
import os, ConfigParser
from pymongo import Connection
from logging.handlers import SysLogHandler as log
import simplejson as json
from datetime import datetime
"""
Let's build a small CLI tool to mark all my done tasks of the day
"""
config={}

class FileStore(object):

    def __init__(self, filename):
        self.fp = open( os.path.expanduser(filename), "a")

    def save(self, data, **kwargs):
        self.fp.write( json.dumps(data))
        self.fp.flush()
        self.fp.close()
        return True

class MongoStore(object):

    def __init__(self, host, dbname, collectionname, j=1, w=1):
        self.host = host
        self.dbname = dbname
        self.collectionname = collectionname
        self.conn = Connection( host )
        self.j = j
        self.w = w

    def save(self, data, **kwargs ):
        col = self.conn[self.dbname][self.collectionname]
        for key, value in kwargs.items():
            setattr(self, key, value)
        _id = col.save( data, self.j, self.w )
        #log the storage of the task
        return _id != None


def save(store, data):
    """
    Saves the data into the datastore
    """
    data['_ts'] = datetime.now().isoformat()

    return None != store.save( data, j=config.get('j',False ))

def get_ofline_store():
    """
    Store everything on a file to be then synchronized back to the server
    """
    #import ipdb;ipdb.set_trace()
    store = FileStore(config['offline'])
    return store

def get_online_store():
    """
    Establish a connection to the online mode.
    Means that we can connect to repo online
    """
    try:
        #log the config
        #import ipdb; ipdb.set_trace()
        return MongoStore( config['host'], config['dbname'], config['collname'])
    except Exception,e :
        #log message and return null
        print('WHAT THE HELL! %s' % e)
        return None


def get_store():
    """
    Let's load a datastore to do save the dones
    """
    store = get_online_store()
    if store is None:
        #log offline mode on
        store = get_ofline_store()

    return store

def restore():
    """
    Get all the offline store tasks
    """
    pass


def init(conf_file='~/.done.cfg'):
    """
    Intialize the configuration object
    """
    global config
    conf = ConfigParser.ConfigParser()
    conf.readfp(open( os.path.expanduser(conf_file) ))
    config = dict( conf._sections['BASE'])

def main():
    """
    Collect all the tasks details that we want to mark as done.
    """
    init()
    store = get_store()
    ok = save(store, {"hello":"world"})
    print("Hello World of Done Things %s" % ok)


if __name__ == '__main__':
    main()
