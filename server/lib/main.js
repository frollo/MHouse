var express, app, expressWs, inspect, things, clients, sendMessage, reportError, handleClientMessage, handleThingMessage, handleMessage, _$0, _$1, _$2;
_$0: {
    _$1: {
    }
    _$2: {
        express = require('express');
        app = express();
        expressWs = require('express-ws')(app);
        inspect = require('util').inspect;
    }
    things = {};
    clients = {};
    sendMessage = function (ws, msg) {
        var _$3, _$4;
        _$4: {
            console.log('Sending message: ' + inspect(msg));
            _$3 = ws.send(JSON.stringify(msg));
            break _$4;
        }
        return _$3;
    };
    reportError = function (ws, error) {
        var _$3, _$4;
        _$4: {
            console.log('Reporting error: ' + error);
            _$3 = sendMessage(ws, { 'error': error });
            break _$4;
        }
        return _$3;
    };
    handleClientMessage = function (ws, msg) {
        var clientId, e, thingId, thing, _$3, _$4, _$5, _$6, _$7;
        _$4: {
            clientId = msg['client-id'];
            if (clients[clientId] === undefined) {
                _$5: {
                    console.log('Client connected: ' + clientId);
                    clients[clientId] = ws;
                }
            } else {
                if (clients[clientId] !== ws) {
                    _$6: {
                        console.log('Client reconnected: ' + clientId);
                        try {
                            clients[clientId].close();
                        } catch (e) {
                            console.log('Error closing old ws for client ' + clientId);
                        }
                        clients[clientId] = ws;
                    }
                }
            }
            thingId = msg['thing-id'];
            if (thingId !== undefined) {
                _$7: {
                    thing = things[thingId];
                    if (thing === undefined) {
                        reportError(ws, 'Thing disconnected: ' + thingId);
                    } else {
                        sendMessage(thing, msg);
                    }
                }
            }
            _$3 = undefined;
            break _$4;
        }
        return _$3;
    };
    handleThingMessage = function (ws, msg) {
        var thingId, e, _$3, _$4, _$5, _$6, _$7;
        _$4: {
            thingId = msg['thing-id'];
            if (thingId === undefined) {
                _$5: {
                    reportError(ws, 'thing-id undefned');
                    return;
                }
            }
            if (things[thingId] === undefined) {
                _$6: {
                    console.log('Thing connected: ' + thingId);
                    things[thingId] = ws;
                }
            } else {
                if (things[thingId] !== ws) {
                    _$7: {
                        console.log('Thing reconnected: ' + thingId);
                        try {
                            things[thingId].close();
                        } catch (e) {
                            console.log('Error closing old ws for thing ' + thingId);
                        }
                        things[thingId] = ws;
                    }
                }
            }
            Object.keys(clients).forEach(function (__$arg$1) {
                return sendMessage(clients[__$arg$1], msg);
            });
            _$3 = undefined;
            break _$4;
        }
        return _$3;
    };
    handleMessage = function (ws, msgText) {
        var msg, clientId, e, _$3, _$4, _$5, _$6, _$7;
        _$4: {
            console.log('Received message: ' + inspect(msgText));
            try {
                _$5: {
                    _$6: {
                        msg = JSON.parse(msgText);
                        clientId = msg['client-id'];
                    }
                    if (clientId !== undefined) {
                        handleClientMessage(ws, msg);
                    } else {
                        handleThingMessage(ws, msg);
                    }
                }
            } catch (e) {
                _$7: {
                    reportError(ws, e.toString());
                    console.log('Stack trace: ' + e.stack);
                }
            }
            _$3 = undefined;
            break _$4;
        }
        return _$3;
    };
    module.exports = function () {
        var server, _$3, _$4;
        _$4: {
            app.get('/', function (req, res, next) {
                var _$5, _$6;
                _$6: {
                    console.log('Served front page', req.testing);
                    _$5 = res.sendFile(__dirname + '/front-page.html');
                    break _$6;
                }
                return _$5;
            });
            app.ws('/', function (ws, req) {
                var _$5, _$6;
                _$6: {
                    ws.on('message', function (msg) {
                        return handleMessage(ws, msg);
                    });
                    _$5 = console.log('Web socket connected');
                    break _$6;
                }
                return _$5;
            });
            _$3 = server = app.listen(3000, function () {
                var host, port, _$5, _$6, _$7;
                _$6: {
                    _$7: {
                        host = server.address().address;
                        port = server.address().port;
                    }
                    _$5 = console.log('Server listening at http://%s:%s', host, port);
                    break _$6;
                }
                return _$5;
            });
            break _$4;
        }
        return _$3;
    };
}
//# sourceMappingURL=main.js.map