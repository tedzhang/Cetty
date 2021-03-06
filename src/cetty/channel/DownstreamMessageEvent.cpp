/*
 * Copyright (c) 2010-2011 frankee zhou (frankee.zhou at gmail dot com)
 *
 * Distributed under under the Apache License, version 2.0 (the "License").
 * you may not use this file except in compliance with the License.  
 * You may obtain a copy of the License at:
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#include "cetty/channel/DownstreamMessageEvent.h"
#include "cetty/channel/Channel.h"
#include "cetty/channel/SocketAddress.h"
#include "cetty/channel/ChannelFuture.h"
#include "cetty/channel/ChannelMessage.h"

namespace cetty { namespace channel {

std::string DownstreamMessageEvent::toString() const {
    std::string buf = this->channel.toString();
    buf.append(" WRITE: ");
    buf.append(message.toString());

    if (this->remoteAddress != this->channel.getRemoteAddress()) {
        buf.append(" to ");
        buf.append(getRemoteAddress().toString());
    }

    return buf;
}

}}