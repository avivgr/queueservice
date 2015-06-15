__author__ = 'Aviv Greenberg'
import queueservice.client as client

"""
test enqueue

This is a very simple test - creates a queue, enqueue and dequeue one item.
"""
import sys
import getopt
import socket

def main():
    address = "127.0.0.1"
    port = 7001

    # parse command line options
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ha:p:", ["help"])
    except getopt.error, msg:
        print msg
        print "for help use --help"
        sys.exit(2)
    # process options
    for o, a in opts:
        if o in ("-h", "--help"):
            print __doc__
            sys.exit(0)
        elif o in ("-a",):
            address = socket.gethostbyname(a)
        elif o in ("-p",):
            port = int(a)

    qsc = client.QueueServiceClient(address, port)
    qsc.connect()

    # Create a queue
    id = qsc.create_queue("myqueue")
    # Enqueue one item
    qsc.enqueue(id, "test123")
    queueid, data, queueentitiyid = qsc.read(id, 10)
    print data
    qsc.dequeue(id, queueentitiyid)

if __name__ == "__main__":
    main()
