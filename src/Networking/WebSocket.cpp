/*
GroupContextNetworking by wladi0097

Licensed under the MIT License <http://opensource.org/licenses/MIT>.
SPDX-License-Identifier: MIT
Copyright (c) 2019 Wladislaw Koschemako.
Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#include "WebSocket.h"
#include "../../deps/uWebSockets/src/App.h"

struct us_listen_socket_t *listen_socket;

void WebSocket::init() {
    struct PerSocketData {

    };

    uWS::App().ws<PerSocketData>("/*", {
            .compression = uWS::SHARED_COMPRESSOR,
            .maxPayloadLength = 16 * 1024 * 1024,
            .idleTimeout = 100,
            .maxBackpressure = 1 * 1024 * 1204,
            .open = [](auto* ws, auto* req) {
                ws->subscribe("broadcast");
                std::basic_string_view<char> a = req->getUrl();

                if (a.compare("/new")) {

                }

                if(a.compare("/join")) {

                }
                int avs = 2;
            },
            .message = [](auto *ws, std::string_view message, uWS::OpCode opCode) {
                /* Exit gracefully if we get a closedown message (ASAN debug) */
                if (message == "closedown") {
                    /* Bye bye */
                    us_listen_socket_close(0, listen_socket);
                    ws->close();
                }

                /* Simply broadcast every single message we get */
                ws->publish("broadcast", message, opCode, true);
            },
    }).listen(9001, [](auto *token) {
        listen_socket = token;
        if (token) {
            std::cout << "Listening on port " << 9001 << std::endl;
        }
    }).run();
}