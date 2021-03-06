#if !defined(CETTY_HANDLER_CODEC_PROTOBUF_PROTOBUFDECODER_H)
#define CETTY_HANDLER_CODEC_PROTOBUF_PROTOBUFDECODER_H

/*
 * Copyright 2009 Red Hat, Inc.
 *
 * Red Hat licenses this file to you under the Apache License, version 2.0
 * (the "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at:
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
/*
 * Copyright (c) 2010-2011 frankee zhou (frankee.zhou at gmail dot com)
 * Distributed under under the Apache License, version 2.0 (the "License").
 */

#include "cetty/handler/codec/oneone/OneToOneDecoder.h"

namespace google { namespace protobuf {
class MessageLite;
}}

namespace cetty { namespace handler { namespace codec { namespace protobuf { 

using namespace cetty::handler::codec::oneone;
using namespace google::protobuf;

/**
 * Decodes a received {@link ChannelBuffer} into a
 * <a href="http://code.google.com/p/protobuf/">Google Protocol Buffers</a>
 * {@link Message} and {@link MessageLite}.  Please note that this decoder must
 * be used with a proper {@link FrameDecoder} such as {@link ProtobufVarint32FrameDecoder}
 * or {@link LengthFieldBasedFrameDecoder} if you are using a stream-based
 * transport such as TCP/IP.  A typical setup for TCP/IP would be:
 * <pre>
 * {@link ChannelPipeline} pipeline = ...;
 *
 * // Decoders
 * pipeline.addLast("frameDecoder",
 *                  new {@link LengthFieldBasedFrameDecoder}(1048576, 0, 4, 0, 4));
 * pipeline.addLast("protobufDecoder",
 *                  new {@link ProtobufDecoder}(MyMessage.getDefaultInstance()));
 *
 * // Encoder
 * pipeline.addLast("frameEncoder", new {@link LengthFieldPrepender}(4));
 * pipeline.addLast("protobufEncoder", new {@link ProtobufEncoder}());
 * </pre>
 * and then you can use a <tt>MyMessage</tt> instead of a {@link ChannelBuffer}
 * as a message:
 * <pre>
 * void messageReceived({@link ChannelHandlerContext} ctx, {@link MessageEvent} e) {
 *     MyMessage req = (MyMessage) e.getMessage();
 *     MyMessage res = MyMessage.newBuilder().setText(
 *                               "Did you say '" + req.getText() + "'?").build();
 *     ch.write(res);
 * }
 * </pre>
 *
 * 
 * @author <a href="http://gleamynode.net/">Trustin Lee</a>
 *
 */

class ProtobufDecoder : public cetty::handler::codec::oneone::OneToOneDecoder {
public:
    /**
     * Creates a new instance.
     */
    ProtobufDecoder(MessageLite* prototype);
    virtual ~ProtobufDecoder() {}

    virtual ChannelHandlerPtr clone();
    virtual std::string toString() const;

protected:
    virtual ChannelMessage decode(ChannelHandlerContext& ctx,
                                  Channel& channel,
                                  const ChannelMessage& msg);

private:
    MessageLite* prototype;
};


}}}}

#endif //#if !defined(CETTY_HANDLER_CODEC_PROTOBUF_PROTOBUFDECODER_H)
