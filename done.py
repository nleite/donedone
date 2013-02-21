#!/usr/bin/python
import os, ConfigParser
from pymongo import Connection
from logging.handlers import SysLogHandler as log
import simplejson as json
from datetime import datetime
import logging
import logging.handlers
from restore import FileRestore
"""
Let's build a small CLI tool to mark all my done tasks of the day
"""
config={}
logger = logging.getLogger('donedone')

class FileStore(object):

    def __init__(self, filename):
        self.fp = open( os.path.expanduser(filename), "a")

    def save(self, data, **kwargs):
        data['_ts']=data['_ts'].isoformat()
        self.fp.write( json.dumps(data))
        self.fp.write('\n')
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
        col.ensure_index( '_ts', unique=True)
        for key, value in kwargs.items():
            setattr(self, key, value)
        _id = col.save( data, self.j, self.w )
        #log the storage of the task
        logger.info( 'Store done task with _id:%s' % _id)
        return _id != None


def save(store, data):
    """
    Saves the data into the datastore
    """
    data['_ts'] = datetime.now()

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
        logger.warning( "Online storage not available, using local file store" )
        return None


def get_store():
    """
    Let's load a datastore to do save the dones
    """
    store = get_online_store()
    if store is None:
        #log offline mode on
        logger.info( "Using local storage" )
        store = get_ofline_store()
    return store

def restore():
    """
    Get all the offline store tasks
    """
    try:
        store = get_online_store()
        if store is not None:
            fr = FileRestore( config['offline'], get_online_store() )
            nrestored = fr.run()
            logger.warn('Restored %s tasks' % nrestored )
    except Exception,e:
        logger.error('Cannot restore right now. Try latter %s' % e)

def init_logging():
    """
    Initialize the logger for this execution
    """
    global logger
    logger.addHandler( logging.handlers.SysLogHandler())


def init(conf_file='~/.done.cfg'):
    """
    Intialize the configuration object
    """
    global config
    conf = ConfigParser.ConfigParser()
    conf.readfp(open( os.path.expanduser(conf_file) ))
    config = dict( conf._sections['BASE'])
    init_logging()
    restore()

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
