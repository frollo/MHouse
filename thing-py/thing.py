#!/usr/bin/python

from autobahn.twisted.websocket import WebSocketClientProtocol, \
    WebSocketClientFactory
#import json

class MyClientProtocol(WebSocketClientProtocol):

#    def JTest():
#        m = { path      :'/api/v1/actor/perform/device/lighting',
#                        requestID :'1',
#                        perform   :'on',
#                        parameter :JSON.stringify({ brightness: 100, color: { model: 'rgb', rgb: { r: 255, g: 255, b: 255 }}}) }
#        n = json.dumps(m)
#        self.sendMessage(m.encode('utf8'))

    def onConnect(self, response):
    #    JTest()
        print("Server connected: {0}".format(response.peer))
        hello(self)

    def onOpen(self):
        print("WebSocket connection open.")

    def hello(self):
        print("Hello starting")
        m = "{ path : '/api/v1/actor/perform/device/lighting',requestID :'1', perform :'on', parameter : { brightness: 100, color: { model: 'rgb', rgb: { r: 255, g: 255, b: 255 }}} }"
        self.sendMessage(m.encode('utf8'))
        #self.sendMessage(b"\x00\x01\x03\x04", isBinary=True)
        self.factory.reactor.callLater(1, hello)

    # start sending messages every second ..
    #hello(self)

    def onMessage(self, payload, isBinary):
        if isBinary:
            print("Binary message received: {0} bytes".format(len(payload)))
        else:
            if isString:
                readCommand(payload.decode('utf8'))
            else:
                print("Text message received: {0}".format(payload.decode('utf8')))

    def onClose(self, wasClean, code, reason):
        print("WebSocket connection closed: {0}".format(reason))

class ThingJSON:
    def readCommand(jn):
        obj = json.loads(payload.decode('utf8'))
        print(obj)

if __name__ == '__main__':
    import sys
    from twisted.python import log
    from twisted.internet import reactor
    log.startLogging(sys.stdout)
    factory = WebSocketClientFactory("ws://10.2.1.58:8888/manage", debug=False)
    print("Reached line 56")
    factory.protocol = MyClientProtocol
    reactor.connectTCP("10.2.1.58", 8888, factory)
    print("Reached line 58")
    reactor.run()
