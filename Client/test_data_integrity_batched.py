__author__ = 'Aviv Greenberg'
import queueservice.client as client

"""
Data integrity test

This test generates batches of random messages (random size, random data) -
it then enqueue them, dequeues them (in a batch) - and compares the data.
"""
import sys
import getopt
import os
import random
import string

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

    id = qsc.create_queue("myqueue-%d" % (os.getpid(),))
    count = 0
    bcount = 0
    while True:
        # send a batch of random enqueues
        rbatch = random.randint(5,200)
        bdata = rbatch * [None]
        for i in range(0, rbatch):
            rlen = random.randint(1,1000)
            bdata[i] = ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(rlen))
            qsc.enqueue(id, bdata[i])

        # Read batch and verify
        for i in range(0, rbatch):
            queueid, data, queueentitiyid = qsc.read(id, 10)
            if data != bdata[i]:
                print "Fail!!!!"
                print "Sent: %s" % (rdata,)
                print "Got: %s" % (data,)
                assert(False)
            assert(id == queueid)
            qsc.dequeue(id, queueentitiyid)
        count = count + rbatch
        bcount = bcount + 1
        if bcount % 10 == 0:
            print "Exchanged %d messages." % (count,)

if __name__ == "__main__":
    main()
