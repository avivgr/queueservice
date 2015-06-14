__author__ = 'Aviv Greenberg'
import QueueService_pb2 as qs
import socket
import struct

class QueueServiceClient:
    def __init__(self, server_addess, port):
        self.server_address = server_addess
        self.port = port
        self.s = None

    def connect(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.s.connect((self.server_address, self.port))

    def _send_req(self, message):
        s = message.SerializeToString()
        packed_len = struct.pack('>H', len(s))
        self.s.sendall(packed_len + s)

    def _socket_read_n(self, n):
        """ Read exactly n bytes from the socket.
            Raise RuntimeError if the connection closed before
            n bytes were read.
        """
        buf = ''
        while n > 0:
            data = self.s.recv(n)
            if data == '':
                raise RuntimeError('unexpected connection close')
            buf += data
            n -= len(data)

        return buf

    def _get_resp(self):
        mlen = self._socket_read_n(2)
        resp_len = struct.unpack('>H', mlen)[0]
        resp_buf = self._socket_read_n(resp_len)
        r = qs.Response()
        r.ParseFromString(resp_buf)
        return r

    def _perform(self, message):
        """ Send a serialized message (protobuf Message interface)
        to a socket, prepended by its length packed in 4
        bytes (big endian).
        """
        self._send_req(message)
        return self._get_resp()

    # Create a queue with the given name (if the name is unique) and return its QueueId.
    def create_queue(self, name):
        r = qs.Request()
        r.type = r.CREATE_QUEUE
        r.createQueue.name = name
        resp = self._perform(r)
        return resp.createQueue.queueid

    # Return the QueueId of the queue with the given name.
    def get_queue(self, name):
        r = qs.Request()
        r.type = r.GET_QUEUE
        r.getQueue.name = name
        resp = self._perform(r)
        return resp.getQueue.queueid

    # Delete the given queue.
    def delete_queue(self, queueId):
        r = qs.Request()
        r.type = r.DEL_QUEUE
        r.delQueue.queueid = queueId
        return self._perform(r)

    # Enqueue the object into the queue with the given id.
    def enqueue(self, queueId, data):
        r = qs.Request()
        r.type = r.ENQUEUE
        r.enqueue.queueid = queueId
        r.enqueue.data = data
        resp = self._perform(r)
        return resp.enqueue.status

    """Read an object from the queue.
    This object will not be returned as a response to
    another read until the given timeout has expired.
    Once dequeue is called then the object will not be
    returned by a subsequent read."""
    def read(self, queueId, timeout):
        r = qs.Request()
        r.type = r.READ
        r.read.queueid = queueId
        r.read.timeout = timeout
        resp = self._perform(r)
        return resp.read.queueid, resp.read.data, resp.read.queueentitiyid

    """ Dequeue the object with the given QueueEntityId.
        A dequeue permanently removes the object from the queue."""
    def dequeue(self, queueId, queueEntityId):
        r = qs.Request()
        r.type = r.DEQUEUE
        r.dequeue.queueid = queueId
        r.dequeue.queueentitiyid = queueEntityId
        resp = self._perform(r)
        return resp.dequeue.status
